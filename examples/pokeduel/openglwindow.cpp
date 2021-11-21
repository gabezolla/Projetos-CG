#include "openglwindow.hpp"

#include <fmt/core.h>
#include <imgui.h>
#include <tiny_obj_loader.h>

#include <cppitertools/itertools.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/hash.hpp>
#include <unordered_map>


void OpenGLWindow::handleEvent(SDL_Event& ev) {
  if (ev.type == SDL_KEYDOWN) {
    if (ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w)
      m_dollySpeed = 1.0f;
    if (ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s)
      m_dollySpeed = -1.0f;
    if (ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a)
      m_panSpeed = -1.0f;
    if (ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d)
      m_panSpeed = 1.0f;
    if (ev.key.keysym.sym == SDLK_q) m_truckSpeed = -1.0f;
    if (ev.key.keysym.sym == SDLK_e) m_truckSpeed = 1.0f;
  }
  if (ev.type == SDL_KEYUP) {
    if ((ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w) &&
        m_dollySpeed > 0)
      m_dollySpeed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s) &&
        m_dollySpeed < 0)
      m_dollySpeed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a) &&
        m_panSpeed < 0)
      m_panSpeed = 0.0f;
    if ((ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d) &&
        m_panSpeed > 0)
      m_panSpeed = 0.0f;
    if (ev.key.keysym.sym == SDLK_q && m_truckSpeed < 0) m_truckSpeed = 0.0f;
    if (ev.key.keysym.sym == SDLK_e && m_truckSpeed > 0) m_truckSpeed = 0.0f;
  }
}

void OpenGLWindow::initializeGL() {
  abcg::glClearColor(0.196078f, 0.6f, 0.8f, 0); 

  // Enable depth buffering
  abcg::glEnable(GL_DEPTH_TEST);

  // Create program
  m_program = createProgramFromFile(getAssetsPath() + "lookat.vert",
                                    getAssetsPath() + "lookat.frag");                              

  m_ground.initializeGL(m_program);


  m_modelSecondSkill.loadObj(getAssetsPath() + "secondskill.obj");
  m_modelCube.loadObj(getAssetsPath() + "cube.obj");
  m_modelPokeTrainerWoman.loadObj(getAssetsPath() + "poketrainerwoman.obj");
  m_modelLucario.loadObj(getAssetsPath() + "lucario.obj");
  m_modelMewtwo.loadObj(getAssetsPath() + "mewtwo.obj");
  m_modelPokeTrainerMan.loadObj(getAssetsPath() + "poketrainerman.obj");  
  m_modelVenuasaur.loadObj(getAssetsPath() + "venuasaur.obj");
  m_modelEeve.loadObj(getAssetsPath() + "eeve.obj");


  m_modelSecondSkill.setupVAO(m_program);
  m_modelCube.setupVAO(m_program);
  m_modelPokeTrainerWoman.setupVAO(m_program);
  m_modelLucario.setupVAO(m_program);
  m_modelMewtwo.setupVAO(m_program);
  m_modelPokeTrainerMan.setupVAO(m_program); 
  m_modelVenuasaur.setupVAO(m_program); 
  m_modelEeve.setupVAO(m_program); 

  resizeGL(getWindowSettings().width, getWindowSettings().height);
  
}

void OpenGLWindow::paintGL() {
  update();

  // Clear color buffer and depth buffer
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  abcg::glViewport(0, 0, m_viewportWidth, m_viewportHeight);

  abcg::glUseProgram(m_program);

  // Get location of uniform variables (could be precomputed)
  const GLint viewMatrixLoc{
      abcg::glGetUniformLocation(m_program, "viewMatrix")};
  const GLint projMatrixLoc{
      abcg::glGetUniformLocation(m_program, "projMatrix")};
  const GLint modelMatrixLoc{
      abcg::glGetUniformLocation(m_program, "modelMatrix")};
  const GLint colorLoc{abcg::glGetUniformLocation(m_program, "color")};  

  // Set uniform variables for viewMatrix and projMatrix
  // These matrices are used for every scene object
  abcg::glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE,
                           &m_camera.m_viewMatrix[0][0]);
  abcg::glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE,
                           &m_camera.m_projMatrix[0][0]);
  

  // Render Lucario
  drawLucario(m_modelLucario, modelMatrixLoc, colorLoc);

  // Render Venusaur
  drawVenuasaur(m_modelVenuasaur, modelMatrixLoc, colorLoc);

  // Render Eeve
  drawEeve(m_modelEeve, modelMatrixLoc, colorLoc);
                 
  // Render Mewtwo
  drawMewtwo(m_modelMewtwo, modelMatrixLoc, colorLoc);

  // Render Trainer 1
  drawTrainerOne(m_modelPokeTrainerMan, modelMatrixLoc, colorLoc);

  // Render Trainer 2
  drawTrainerTwo(m_modelPokeTrainerMan, modelMatrixLoc, colorLoc);

  // Render Trainer 3
  drawTrainerThree(m_modelPokeTrainerWoman, modelMatrixLoc, colorLoc);

  // Render Trainer 4
  drawTrainerFour(m_modelPokeTrainerWoman, modelMatrixLoc, colorLoc);

  // Shadow Ball (Mewtwo Skill) 
  drawCube(m_modelCube, modelMatrixLoc, colorLoc);

  // Sand Attack (Eeve skill)
  drawSecondSkill(m_modelSecondSkill, modelMatrixLoc, colorLoc);

  // Draw ground
  m_ground.paintGL();

  abcg::glUseProgram(0);

}

 void OpenGLWindow::drawTrainerOne(Model m_modelPokeTrainerMan, const GLint modelMatrixLoc, const GLint colorLoc){
  glm::mat4 model{1.0f};
  model = glm::translate(model, glm::vec3(-2.5f, 0.80f, 0.0f));  
  model = glm::scale(model, glm::vec3(1.0f));
  model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)

  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(colorLoc, 0.0f, 0.8f, 1.0f, 1.0f); //azul
  
  m_modelPokeTrainerMan.render();      
  }
  

void OpenGLWindow::drawTrainerTwo(Model m_modelPokeTrainerMan, const GLint modelMatrixLoc, const GLint colorLoc){
  glm::mat4 model{1.0f};
  model = glm::translate(model, glm::vec3(-2.5f, 0.80f, 2.0f));  
  model = glm::scale(model, glm::vec3(1.0f));
  model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)

  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(colorLoc, 0.0f, 0.8f, 1.0f, 1.0f); //azul
  m_modelPokeTrainerMan.render();   

}

void OpenGLWindow::drawTrainerThree(Model m_modelPokeTrainerWoman, const GLint modelMatrixLoc, const GLint colorLoc){
  glm::mat4 model{1.0f};
  model = glm::translate(model, glm::vec3(2.5f, 0.5f, 0.0f));  
  model = glm::scale(model, glm::vec3(1.0f));
  model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)


  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(colorLoc, 1.0f, 0.25f, 0.25f, 1.0f); //vermelho
  m_modelPokeTrainerWoman.render(); 

}

void OpenGLWindow::drawTrainerFour(Model m_modelPokeTrainerWoman, const GLint modelMatrixLoc, const GLint colorLoc){
  glm::mat4 model{1.0f};
  model = glm::translate(model, glm::vec3(2.5f, 0.5f, 2.0f));  
  model = glm::scale(model, glm::vec3(1.0f));
  model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)


  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(colorLoc, 1.0f, 0.25f, 0.25f, 1.0f); //vermelho
  m_modelPokeTrainerWoman.render(); 

}
  void OpenGLWindow::drawCube(Model m_modelCube, const GLint modelMatrixLoc, const GLint colorLoc){
  glm::mat4 model{1.0f};
  model = glm::translate(model, glm::vec3(0.25f, 0.5f, 0.0f));
  model = glm::scale(model, glm::vec3(0.35f));

  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(colorLoc, 0.074f, 0.0f, 0.380f, 1.0f);
  m_modelCube.render();

  }

void OpenGLWindow::drawSecondSkill(Model m_modelSecondSkill, const GLint modelMatrixLoc, const GLint colorLoc){
  glm::mat4 model{1.0f};
  model = glm::translate(model, glm::vec3(0.0f, 0.15f, 1.0f));
  model = glm::scale(model, glm::vec3(0.70f));
  model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)


  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(colorLoc, 0.917, 0.929, 0.631, 1.0f);
  m_modelSecondSkill.render();

}

void OpenGLWindow::drawEeve(Model m_modelEeve, const GLint modelMatrixLoc, const GLint colorLoc){
  glm::mat4 model{1.0f};
  model = glm::translate(model, glm::vec3(1.5f, 0.27f, 1.0f));  
  model = glm::scale(model, glm::vec3(0.6f));
  model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)


  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(colorLoc, 0.5f, 0.35f, 0.05f, 1.0f);

  m_modelEeve.render();       

}

void OpenGLWindow::drawMewtwo(Model m_modelMewtwo, const GLint modelMatrixLoc, const GLint colorLoc){
  glm::mat4 model{1.0f};
  model = glm::translate(model, glm::vec3(1.5f, 0.5f, 0.0f));  
  model = glm::scale(model, glm::vec3(0.8f));
  model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)


  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(colorLoc, 0.737255f, 0.560784f, 0.560784f, 1.0f);
  m_modelMewtwo.render(); 
}

void OpenGLWindow::drawVenuasaur(Model m_modelVenuasaur, const GLint modelMatrixLoc, const GLint colorLoc){

  glm::mat4 model{1.0f};
  model = glm::translate(model, glm::vec3(-1.5f, 0.40f, 1.0f));  
  model = glm::scale(model, glm::vec3(1.0f));
  model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)


  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(colorLoc, 0.196078f, 0.8f, 0.196078f, 1.0f);
  m_modelVenuasaur.render();  
}

void OpenGLWindow::drawLucario(Model m_modelLucario, const GLint modelMatrixLoc, const GLint colorLoc){
  glm::mat4 model{1.0f};
  model = glm::translate(model, glm::vec3(-1.5f, 0.5f, 0.0f));  
  model = glm::scale(model, glm::vec3(0.8f));
  model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // where x, y, z is axis of rotation (e.g. 0 1 0)
  
  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model[0][0]);
  abcg::glUniform4f(colorLoc, 0.0f, 0.8f, 1.0f, 1.0f);  
  m_modelLucario.render();  
} 


void OpenGLWindow::paintUI() { abcg::OpenGLWindow::paintUI(); }

void OpenGLWindow::resizeGL(int width, int height) {
  m_viewportWidth = width;
  m_viewportHeight = height;

  m_camera.computeProjectionMatrix(width, height);
}

void OpenGLWindow::terminateGL() {
  m_modelLucario.terminateGL();
  m_modelMewtwo.terminateGL();
  m_modelPokeTrainerMan.terminateGL();
  m_ground.terminateGL();

  abcg::glDeleteProgram(m_program);  
}

void OpenGLWindow::update() {
  const float deltaTime{static_cast<float>(getDeltaTime())};

  // Update LookAt camera
  m_camera.dolly(m_dollySpeed * deltaTime);
  m_camera.truck(m_truckSpeed * deltaTime);
  m_camera.pan(m_panSpeed * deltaTime);
}
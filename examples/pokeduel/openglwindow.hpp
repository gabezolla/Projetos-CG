#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <vector>

#include "abcg.hpp"
#include "camera.hpp"
#include "ground.hpp"
#include "model.hpp"


class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void handleEvent(SDL_Event& ev) override;
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;
  void terminateGL() override;

 private:  
  GLuint m_program{};

  int m_viewportWidth{};
  int m_viewportHeight{};

  Model m_modelSecondSkill;
  Model m_modelCube;
  Model m_modelPokeTrainerWoman;
  Model m_modelMewtwo;
  Model m_modelAviao;
  Model m_modelLucario;
  Model m_modelPokeTrainerMan;
  Model m_modelVenuasaur;
  Model m_modelEeve;

  int m_trianglesToDraw{};

  Camera m_camera;
  float m_dollySpeed{0.0f};
  float m_truckSpeed{0.0f};
  float m_panSpeed{0.0f};

  Ground m_ground;

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;   

  void loadModelFromFile(std::string_view path);  
  void update();
  void drawLucario(Model m_modelLucario, const GLint modelMatrixLoc, const GLint colorLoc);
  void drawVenuasaur(Model m_modelVenuasaur, const GLint modelMatrixLoc, const GLint colorLoc);
  void drawMewtwo(Model m_modelMewtwo, const GLint modelMatrixLoc, const GLint colorLoc);
  void drawEeve(Model m_modelEeve, const GLint modelMatrixLoc, const GLint colorLoc);
  void drawSecondSkill(Model m_modelSecondSkill, const GLint modelMatrixLoc, const GLint colorLoc);
  void drawCube(Model m_modelCube, const GLint modelMatrixLoc, const GLint colorLoc);
  void drawTrainerFour(Model m_modelPokeTrainerWoman, const GLint modelMatrixLoc, const GLint colorLoc);
  void drawTrainerThree(Model m_modelPokeTrainerWoman, const GLint modelMatrixLoc, const GLint colorLoc);
  void drawTrainerTwo(Model m_modelPokeTrainerMan, const GLint modelMatrixLoc, const GLint colorLoc);
  void drawTrainerOne(Model m_modelPokeTrainerMan, const GLint modelMatrixLoc, const GLint colorLoc);

};

#endif
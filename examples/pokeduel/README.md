# Pokemon Battle
### Projeto 2 - Computação Gráfica

Autores: **Gabriel Zolla Juarez - RA: 11201721446**

**Pedro Henrique Batistela Lopes - RA: 11201722043**

**Link do repositório do código-fonte:** https://github.com/gabezolla/Projetos-CG/tree/main/examples/pokeduel

**Link para o vídeo demonstrativo:** https://youtu.be/PAA6el45YL8

Este repositório contém o código-fonte do Pokemon Duel, projeto desenvolvido para a disciplina de Computação Gráfica, ministrada pelo Prof. Bruno Dorta. Como referência, utilizou-se conceitos de matrizes, câmera LookAt, e espaços vetoriais, visto durante as aulas, bem como as bibliotecas **abcg** e o **ImGui**, aliadas ao OpenGL.

<hr style="border:1px solid gray"> </hr>

### :detective: **Descrição** :detective:

A implementação consiste em uma cena de batalha de duplas entre Pokemons e seus respectivos treinadores em um ginásio Pokemon. Para tal, utilizar-se-á modelos (arquivos .obj) retirados de fontes da internet e aplicamos conceitos iniciais de renderização visto nas aulas anteriores, bem como manipulação do modelo e atributos como translation, rotation e scale. Os modelos, por sua vez, foram criados por seus autores baseado no pipeline gráfico do OpenGL, a partir de arranjos de vértices. 
Tendo em vista que para utilizar os modelos são necessárias variáveis de matrizes, alguns conceitos como escala e translação foram necessários para posicionar de forma adequada os personagens na tela.

Por fim, destaca-se a criação de uma câmera LookAt, tal como visto em aula, que basicamente contém três propriedades: m_eye, m_at e m_up. A primeira corresponde à posição da câmera no mundo, m_at a posição onde a câmera está olhando, e m_up a direção que aponta para cima. Vale ressaltar que a direção do sistema respeita a regra da mão direita, conceito que foi importante principalmente para aplicar rotações.

Na função handleEvent, ter-se-á condicionais que fazem a movimentação da câmera LookAt a partir do input de tecla do usuário. Em initializeGL, por sua vez, inicializam-se todos os models a partir dos arquivos .obj, bem como configuram-se os VAOs dos modelos com o programa de shader utilizado. Na função paintGL, por sua vez, criam-se as variáveis necessárias para o processo de renderização, e, além disso, tem o intuito de invocar as funções que correspondem à renderização de cada objeto, que, por sua vez, têm propriedades de scale, translate, que são armazenadas na matriz de model. Em updateGL tem-se a atualização da câmera ao longo do tempo, enquanto em terminateGL esvaziam-se os buffers utilizados para a renderização no pipeline gráfico. A interface (paintUI) não tem nada de especial, pois não vimos necessidade de criar menus e botões para o cenário em questão.

<hr style="border:1px solid gray"> </hr>

### :joystick: **Controles** :joystick:

Os controles são simples: o usuário pode se movimentar no ginásio Pokemon utilizando as teclas 'W' 'A' 'S' 'D', que representam a direção para cima, direita, baixo e esquerda, respectivamente, ou as setas do teclado.

<hr style="border:1px solid gray"> </hr>


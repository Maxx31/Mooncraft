#include "Scene.h"

#include "../Application/Application.h"
#include "../AssetManager/AssetManager.h"
#include "../Rendering/MCraftVertex.h"

Scene::Scene() 
{
  onResized(Application::instance().getWindowWidth(), Application::instance().getWindowHeight());
}

Scene::Scene(std::vector<Entity> entities) : entities(std::move(entities))
{
  onResized(Application::instance().getWindowWidth(), Application::instance().getWindowHeight());
}

void Scene::init() {
  if (initialized) throw std::exception("The scene has been already initialized");
  initialized = true;

  for (auto &entity: entities) { entity.init(); }

  std::vector<MCraftVertex> vertices = 
  {
     //+y axis
     {{-1, 1, 1}, {1, 0}},
     {{1, 1, 1}, {1, 1}},
     {{-1, 1, -1}, {0, 0}},
     {{1, 1, 1}, {1, 1}},
     {{1, 1, -1}, {0, 1}},
     {{-1, 1, -1}, {0, 0}},
     // +x axis
     {{1, 1, -1}, {0, 0}},
     {{1, -1, 1}, {1, 1}},
     {{1, -1, -1}, {0, 1}},
     {{1, -1, 1}, {1, 1}},
     {{1, 1, -1}, {0, 0}},
     {{1, 1, 1}, {1, 0}},
     //-x axis
     {{-1, -1, -1}, {1, 1}},
     {{-1, 1, 1}, {0, 0}},
     {{-1, 1, -1}, {1, 0}},
     {{-1, 1, 1}, {0, 0}},
     {{-1, -1, -1}, {1, 1}},
     {{-1, -1, 1}, {0, 1}},
     //-z axis
     {{1, -1, -1}, {1, 1}},
     {{-1, -1, -1}, {0, 1}},
     {{1, 1, -1}, {1, 0}},
     {{-1, -1, -1}, {0, 1}},
     {{-1, 1, -1}, {0, 0}},
     {{1, 1, -1}, {1, 0}},
     // +z axis
     {{-1, 1, 1}, {1, 0}},
     {{-1, -1, 1}, {1, 1}},
     {{1, 1, 1}, {0, 0}},
     {{1, -1, 1}, {0, 1}},
     {{1, 1, 1}, {0, 0}},
     {{-1, -1, 1}, {1, 1}},
     //-y axis
     {{1, -1, -1}, {0, 0}},
     {{1, -1, 1}, {1, 0}},
     {{-1, -1, 1}, {1, 1}},
     {{-1, -1, -1}, {0, 1}},
     {{1, -1, -1}, {0, 0}},
     {{-1, -1, 1}, {1, 1}},
  };

  vao = std::make_shared<VertexArray>(vertices, MCraftVertex::vertexAttributes());

  defaultShader = AssetManager::instance().loadShaderProgram("assets/default");
  textureAtlas = AssetManager::instance().loadTexture("assets/default_texture.png");
  defaultShader->setTexture("atlas", textureAtlas, 0);
}

void Scene::update(float deltaTime) 
{
  static float animationProgress = 0;
  animationProgress += deltaTime * 2;

  for (auto &entity: entities) { entity.update(deltaTime); }

  camera.setPosition({glm::sin(animationProgress) * 5, glm::sin(animationProgress / 2) * 2, glm::cos(animationProgress) * 5});
}

void Scene::render() 
{
  glm::mat4 camMatrix = projectionMatrix * camera.getViewMatrix();
  defaultShader->bind();
  defaultShader->setMat4("CamMatrix", camMatrix);
  vao->renderVertexStream();
}

void Scene::renderGui() 
{
  ImGui::ShowDemoWindow();
}

void Scene::onResized(int32_t width, int32_t height)
{
  float aspectRatio = width == 0 || height == 0 ? 0 : static_cast<float>(width) / static_cast<float>(height);
  projectionMatrix = glm::perspective<float>(glm::half_pi<float>(), aspectRatio, .1f, 100.0f);
}

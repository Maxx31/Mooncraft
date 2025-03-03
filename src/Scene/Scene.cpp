#include "Scene.h"

#include "../Application/Application.h"
#include "../AssetManager/AssetManager.h"

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

    std::vector<glm::vec3> vertices = {
     {1, 1, 1},   
     {1, 1, -1},   
     {1, -1, 1},  
     {1, -1, -1},   
     {-1, 1, 1},   
     {-1, 1, -1},   
     {-1, -1, 1},  
     {-1, -1, -1}, 
  };

  std::vector<VertexAttribute> vertexAttributes = {VertexAttribute(3, VertexAttribute::Float, 0)};

    std::vector<uint32_t> indices = {
       // +y axis
       0, 1, 5,  
       4, 0, 5,  
       // +x axis
       2, 1, 0,  
       1, 2, 3,  
       // -x axis
       7, 4, 5,  
       4, 7, 6,  
       // -z axis
       1, 3, 7,  
       1, 7, 5,  
       // +z axis
       4, 6, 0,  
       2, 0, 6,  
       // -y axis
       3, 2, 6,  
       7, 3, 6   
    };

  vao = std::make_shared<VertexArray>(vertices, vertexAttributes, indices);
  defaultShader = AssetManager::instance().loadShaderProgram("assets/default");
}

void Scene::update(float deltaTime) 
{
  static float animationProgress = 0;
  animationProgress += deltaTime * 2;

  for (auto &entity: entities) { entity.update(deltaTime); }

  camera.setPosition({sin(animationProgress) * 5, sin(animationProgress / 2) * 3, cos(animationProgress) * 5});
}

void Scene::render() 
{
  glm::mat4 camMatrix = projectionMatrix * camera.getViewMatrix();
  defaultShader->bind();
  defaultShader->setMat4("CamMatrix", camMatrix);
  vao->render();
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

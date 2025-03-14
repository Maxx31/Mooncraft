#include "Scene.h"

#include "../Application/Application.h"
#include "../World/BlockName.h"
#include "../World/RayCasting/Ray.h"

Scene::Scene()
{
  onResized(Application::instance().getWindowWidth(), Application::instance().getWindowHeight());
}

void Scene::init()
{
  assert(!initialized && "The scene has already been initialized");
  initialized = true;

  updateMouse();

  outlinedBlockShader = AssetManager::instance().loadShaderProgram("assets/shaders/outline");

  std::vector<BlockVertex> vertices;

  vertices.resize(6 * 6);
  int vertexCount = 0;
  for (const auto& face: BlockMesh::vertices) {
    for (const auto& vertex: face) {
      vertices.at(vertexCount) = vertex;
      vertexCount++;
    }
  }
  outlinedBlockVertexArray = std::make_shared<VertexArray>(vertices, BlockVertex::vertexAttributes());
}

void Scene::update(float deltaTime) 
{
  player.update(deltaTime);
  world->update(player.getPosition());
  skybox.update(projectionMatrix, player.getViewMatrix(), deltaTime);
}

void Scene::toggleMenu() 
{
  isMenuOpen = !isMenuOpen;
  updateMouse();
}

void Scene::updateMouse() 
{
  if (isMenuOpen) {
    player.resetMousePosition();
    Window::instance().unlockMouse();
  } else {
    Window::instance().lockMouse();
  }
}

void Scene::render() {
  skybox.render();

  glm::mat4 mvp = projectionMatrix * player.getViewMatrix();
  world->render(player.getPosition(), mvp);


  // render the block outline
  if (Ray ray{player.getPosition(), player.getLookDirection(), *world, Player::reach}) {
    auto blockHit = ray.getHitTarget().position;

    outlinedBlockShader->setMat4("CamMatrix", mvp * glm::translate(blockHit));
    outlinedBlockShader->bind();
    outlinedBlockVertexArray->renderVertexStream();
  }

  crosshair.render();
}

void Scene::renderGui() {
  if (!isMenuOpen) {
    return;
  }

  if (ImGui::Begin("Menu")) {
    glm::vec3 position = player.getPosition();
    ImGui::Text("Player position: x:%f, y:%f, z:%f", position.x, position.y, position.z);
    glm::vec3 lookDirection = player.getLookDirection();
    ImGui::Text("Player direction: x:%f, y:%f, z:%f", lookDirection.x, lookDirection.y, lookDirection.z);

    ImGui::Spacing();
    ImGui::Spacing();

    BlockData::BlockType blockToPlace = player.getBlockToPlace();
    ImGui::Text("Selected Block: %s", BlockName::blockTypeToName(blockToPlace));

    ImGui::Spacing();
    ImGui::Spacing();

    BlockName::NameArray names = BlockName::getBlockNames();
    int32_t selected = BlockName::blockTypeToIndex(blockToPlace);
    if (ImGui::ListBox("Select a block to place: ", &selected, &names[0], names.size())) {
      player.setBlockToPlace(BlockName::BlockNames[selected].first);
    }

    ImGui::Spacing();

    float speed = skybox.getRotationSpeed();
    if (ImGui::SliderFloat("Night/Day cycle speed", &speed, 0.1, 10))
    {
      skybox.setRotationSpeed(speed);
    }

    ImGui::Spacing();
    ImGui::Spacing();

    static char textureAtlasPath[256] = "";
    ImGui::InputText("Custom texture atlas path", textureAtlasPath, 256);
    if (ImGui::Button("Load texture atlas")) 
    {
      SharedRef<const Texture> atlas = AssetManager::instance().loadTexture(textureAtlasPath);
      if (atlas != nullptr) 
      {
        world->setTextureAtlas(atlas);
      }
    }
  }
  ImGui::End();
}

void Scene::onResized(int32_t width, int32_t height) 
{
  float aspectRatio = width == 0 || height == 0 ? 0 : static_cast<float>(width) / static_cast<float>(height);
  projectionMatrix = glm::perspective<float>(glm::half_pi<float>(), aspectRatio, .1f, 250.0f);
  crosshair.update(aspectRatio);
}

void Scene::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) 
{
  if (key == 256) {
    if (action == 1) {
      toggleMenu();
    }
    return;
  }
  player.onKeyEvent(key, scancode, action, mode);
}

void Scene::onMouseButtonEvent(int32_t button, int32_t action, int32_t mods) 
{
  if (!isMenuOpen) {
    player.onMouseButtonEvent(button, action, mods);
  }
}

void Scene::onCursorPositionEvent(double x, double y) 
{
  if (!isMenuOpen) {
    player.onCursorPositionEvent(x, y);
  }
}
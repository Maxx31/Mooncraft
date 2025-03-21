#include "Texture.h"

#include "../AssetManager/AssetManager.h"
#include "Image.h"

Texture::Texture(uint32_t image_type, int32_t maxLod) : type(image_type) 
{
  assert(type == GL_TEXTURE_2D || type == GL_TEXTURE_2D_ARRAY || type == GL_TEXTURE_CUBE_MAP);
  glGenTextures(1, &id);
  bind();

  glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  if (type == GL_TEXTURE_CUBE_MAP) {
    glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
  }

  glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(type, GL_TEXTURE_MAX_LOD, maxLod);

  unbind();
}

Texture::~Texture() 
{
  if (isValid()) {
    glDeleteTextures(1, &id);
  }
}

void Texture::buffer2DRGBAData(const Image& image) 
{
  assert(type == GL_TEXTURE_2D);
  bind();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int32_t>(image.width), static_cast<int32_t>(image.height), 0,
               GL_RGBA, GL_UNSIGNED_BYTE, &image.data[0]);
  glGenerateMipmap(type);
  unbind();
}

void Texture::buffer2DArrayRGBAData(std::span<const Image> images) 
{
  assert(type == GL_TEXTURE_2D_ARRAY);
  assert(images.size() > 0);
  bind();

  glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, static_cast<int32_t>(images[0].width),
               static_cast<int32_t>(images[0].height), images.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

  for (size_t i = 0; i < images.size(); i++) {
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, static_cast<int32_t>(images[i].width),
                    static_cast<int32_t>(images[i].height), 1, GL_RGBA, GL_UNSIGNED_BYTE, images[i].data.data());
  }
  glGenerateMipmap(type);

  unbind();
}

void Texture::bufferCubeMapRGBAData(std::span<SharedRef<const Image>, 6> images) 
{
  assert(type == GL_TEXTURE_CUBE_MAP);
  bind();

  for (size_t i = 0; i < images.size(); i++) {
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, static_cast<int32_t>(images[i]->width),
                 static_cast<int32_t>(images[i]->height), 0, GL_RGBA, GL_UNSIGNED_BYTE, &images[i]->data[0]);
  }
  glGenerateMipmap(type);

  unbind();
}

void Texture::bind() const 
{
  glBindTexture(type, id);
}

void Texture::bindToSlot(uint32_t slot) const 
{
  glActiveTexture(GL_TEXTURE0 + slot);
  bind();
}

void Texture::unbind() const
{
  glBindTexture(type, 0);
}

SharedRef<const Texture> Texture::loadTexture2D(const std::string& name)
{
  SharedRef<const Image> image = AssetManager::instance().loadImage(name);
  if (image == nullptr) {
    return nullptr;
  }

  SharedRef<Texture> texture = std::make_shared<Texture>(GL_TEXTURE_2D, 4);
  texture->buffer2DRGBAData(*image);
  return texture;
}

SharedRef<const Texture> Texture::loadTexture2DArray(const std::string& name) {
  SharedRef<const Image> image = AssetManager::instance().loadImage(name);
  if (image == nullptr) {
    return nullptr;
  }

  // Split up image
  // Assume 16x16 splits
  const uint8_t tileWidth = 16;
  const uint8_t tileHeight = 16;
  std::vector<Image> subImages;
  for (uint32_t tileY = 0; tileY < image->height / tileHeight; ++tileY) {
    for (uint32_t tileX = 0; tileX < image->width / tileWidth; ++tileX) {
      subImages.emplace_back(image->subImage({tileX * tileWidth, tileY * tileHeight}, {tileWidth, tileHeight}));
    }
  }

  SharedRef<Texture> texture = std::make_shared<Texture>(GL_TEXTURE_2D_ARRAY, 4);
  texture->buffer2DArrayRGBAData(subImages);
  return texture;
}

SharedRef<const Texture> Texture::loadCubeMapTexture(const std::string& name) {
  std::stringstream parts(name);

  std::array<SharedRef<const Image>, 6> images{};
  std::string imageName;
  AssetManager& assetManager = AssetManager::instance();
  for (int32_t i = 0; i < 6; i++) {
    if (!std::getline(parts, imageName, ';')) {
      std::cerr << "Invalid cube map name format" << std::endl;
      return nullptr;
    }
    images[i] = assetManager.loadImage(imageName);

    if (images[i] == nullptr) {
      return nullptr;
    }
  }

  SharedRef<Texture> texture = std::make_shared<Texture>(GL_TEXTURE_CUBE_MAP);
  texture->bufferCubeMapRGBAData(images);
  return texture;
}
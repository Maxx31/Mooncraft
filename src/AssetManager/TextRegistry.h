#pragma once

#include "../Util/Util.h"
#include "AssetRegistry.h"

class TextRegistry : public AssetRegistry<std::string> 
{
   SharedRef<const std::string> loadAsset(const std::string &name) override { return Util::readBinaryFile(name); }
};
#ifndef GAME_TEXTURES_H
#define GAME_TEXTURES_H

#include "animation.h"          // TexturePack

namespace textures {
  extern std::vector<TexturePack> texVector;
  TexturePack* get(int n);
  void initialize();
}

#endif

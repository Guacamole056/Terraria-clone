#include "blocks.h"
#include "declarations.h"
#include "entities.h"
#include "enum.h"
#include <SFML/Graphics.hpp>

#ifndef Gameheight
#define Gameheight 80
#endif
#ifndef Gamelenght
#define Gamelenght 160
#endif

extern bl::blocks world[Gamelenght][Gameheight];
extern float deltatime;

void handl(entities &entity) {}

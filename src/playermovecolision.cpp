#include "declarations.h"
#include <SFML/Graphics.hpp>
#define gravity 9.81
#ifndef Gameheight
#define Gameheight 320
#endif
#ifndef Gamelenght
#define Gamelenght 840
#endif
#include "blocks.h"
#include "entities.h"
#include "enum.h"
#include <cmath>

extern float deltatime;
extern playerentity player;
extern bl::blocks world[Gamelenght][Gameheight];

void moveplayer() {
  // Player movement logic implementation
  player.velocity.x *= 0.1f;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.canjump) {
    player.velocity.y = -sqrtf(2.0f * GRAVITY * 32 * 150);
    player.canjump = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    player.velocity.x = -300;
    player.movingright = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    player.velocity.x = 300;
    player.movingright = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    player.velocity.y = 300;
  }

  player.velocity.y += GRAVITY * 32 * deltatime * 2;
  player.velocity.y = std::min(player.velocity.y, (float)GRAVITY * 32);
  player.x += player.velocity.x * deltatime;
  player.y += player.velocity.y * deltatime;
}

void checkcollision() {
  int deltax, deltay, intersectx, intersecty;
  player.canjump = false;

  for (int x = 0; x < Gamelenght; x++) {
    for (int y = 0; y < Gameheight; y++) {
      if (world[x][y].family() == bl::blocy) {
        deltax = x * 32 + 16 - player.getcenterx();
        deltay = y * 32 + 16 - player.getcentery();
        intersectx = std::abs(deltax) - (16 + player.sizeofentity.x / 2);
        intersecty = std::abs(deltay) - (16 + player.sizeofentity.y / 2);

        if (intersectx < 0.0f && intersecty < 0.0f) {
          if (abs(intersectx) <= abs(intersecty)) {
            // Move on x
            if (deltax < 0) {
              player.x = x * 32 + 32;
            } else {
              player.x = x * 32 - player.sizeofentity.x;
            }
          } else {
            // Move on y
            if (deltay < 0) {
              player.y = y * 32 + 32;
            } else {
              player.y = y * 32 - player.sizeofentity.y;
              player.canjump = true;
            }
          }
        }
      }
    }
  }
}

void fixplayerscreen() {
  if (player.x < 0) {
    player.x = 0;
  }
  if (player.x + player.sizeofentity.x > 32 * Gamelenght) {
    player.x = 32 * Gamelenght - player.sizeofentity.x;
  }
  if (player.y < -2) {
    player.y = -2;
  }
  if (player.y + player.sizeofentity.y > 32 * Gameheight) {
    player.y = 32 * Gameheight - player.sizeofentity.y;
    player.canjump = true;
  }

  // Update last position
  player.lastpos.x = player.x;
  player.lastpos.y = player.y;
}

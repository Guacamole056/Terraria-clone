#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED
#include "Craftingrecepies.h"
#include "entities.h"
#include "enum.h"
#include "items.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

using namespace std;

#ifndef GRAVITY
#define GRAVITY 9.81
#endif
#ifndef GAMEHEIGHT_DEFINED
#define GAMEHEIGHT_DEFINED
#define Gameheight 320 /// height of the game
#endif
#ifndef GAMELENGHT_DEFINED
#define GAMELENGHT_DEFINED
#define Gamelenght 840 /// lenght of the game
#endif
#define INVENTORY_SIZE 30
#define CHEST_SIZE 20

// Add missing constants
#define moveplayer()      /* Forward declaration */
#define checkcollision()  /* Forward declaration */
#define fixplayerscreen() /* Forward declaration */

using std::string;
sf::Texture loadfiles(string name);
void handleevents(sf::RenderWindow &window);
void loadmap(int index);
void savemap(int index);
void settextures();
void changetexture(sf::Sprite &sprite, int blocktype, int blockvaration = 0,
                   bool revers = 0);
// void moveplayer();
// void checkcollision();
// void fixplayerscreen();
// void setplayerlastposition();
void growtreee(uint8_t lenght, int xpos, int ypos);
int randomrange(int min_val, int max_val);
bool randompercent(float chance);
void handleentity(entities &entity, float gravity);
void makemove(slimeentity &ent, entities other);
void makemove(humanlikeenemy &ent, entities other);
void inttostring(string &str, int a);
string inttostring(int a);
int putere(int a, int b);
void resetnumberofitemslots();
void handleitemslots();
int getminx(entities &entity);
int getminy(entities &entity);
int getmaxx(entities &entity);
int getmaxy(entities &entity);
void inventorystate();
droppeditem getdroppeditem(int type);
int getfamilya(int type);
void crafting();
void timehandle();
void showhearts();
void checkstations();
void handle_background();
void spawnmonster();
void drawitem();
void drawitemstats(Craftebleitem rec, items *item);
bool isconsumable(int type);
void handleview(sf::View &view, entities ent, float speed);
void mainmenuf();
// void setbuttons();
// void setbuttons();

void placechest(int x, int y);
void breakchest(int x, int y);
void loadchest(int x, int y);
void deletechest();

void updatemap();

void dosave();

void drawplayer();
int getarmour(int type);
int getfalldamagerezistance(int type);

void returnToMainMenu();

namespace et {
slimeentity getslime(uint8_t type);
humanlikeenemy gethumanlikeenemy(uint8_t type);

} // namespace et

#endif // DECLARATIONS_H_INCLUDED

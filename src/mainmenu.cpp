#include "buttonclass.h"
#include "declarations.h"

extern int WIDE;
extern int HEIGHT;
extern bool leftreleased;
extern sf::RenderWindow window;
extern sf::Text text;
extern sf::View view;
#define XVIEW (view.getCenter().x - WIDE / 2)
#define YVIEW (view.getCenter().y - HEIGHT / 2)
extern int curentbiome;
extern playerentity player;
extern uint8_t states;
// sf::Vector2i pl;
extern float deltatime;
extern int maploaded;

static void load1f() {
  states = gamestates::game;
  maploaded = 1;
  loadmap(1); /// loads the map
}

static void load2f() {
  states = gamestates::game;
  maploaded = 2;
  loadmap(2); /// loads the map
}

static void load3f() {
  states = gamestates::game;
  maploaded = 3;
  loadmap(3); /// loads the map
}

static void programulLuiDavid() {}

void mainmenuf() {
  // pl={player.x,player.y};

  player.x = 1000;
  player.y = 1000;

  buttonclass loadworld1; ////////////////
  buttonclass loadworld2; ////////////////
  buttonclass loadworld3; ////////////////
  buttonclass newworld;   ////////////////
  buttonclass exitb;      ////////////////

  handle_background();
  view.setCenter(1000, 1000);

  loadworld1.scale = 2;
  loadworld2.scale = 2;
  loadworld3.scale = 2;
  newworld.scale = 2;
  exitb.scale = 2;

  loadworld1.seposrelevanttothecenter(0, 150);
  loadworld2.seposrelevanttothecenter(0, 250);
  loadworld3.seposrelevanttothecenter(0, 350);
  newworld.seposrelevanttothecenter(0, 50);
  exitb.position = {0, 0};

  loadworld1.nroftiles = 4;
  loadworld2.nroftiles = 4;
  loadworld3.nroftiles = 4;
  newworld.nroftiles = 4;
  exitb.nroftiles = 1;

  loadworld1.title = "Load world 1";
  loadworld2.title = "Load world 2";
  loadworld3.title = "Load world 3";
  newworld.title = "New world...";
  exitb.title = "X";

  loadworld1.onclick = load1f;
  loadworld2.onclick = load2f;
  loadworld3.onclick = load3f;
  newworld.onclick = programulLuiDavid;
  exitb.onclick = []() { exit(0); };

  loadworld1.update();
  loadworld2.update();
  loadworld3.update();
  newworld.update();
  exitb.update();

  window.setView(view);
  window.display();
  window.clear(sf::Color(11, 107, 237));

  // player.x=pl.x;
  // player.y=pl.y;
}

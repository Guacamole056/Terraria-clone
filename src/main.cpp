#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <signal.h>
#include <vector>
#include <windows.h>

// Fix byte type ambiguity
#define byte win_byte_override
#include <windows.h>
#undef byte

// ImGui includes
#pragma region imgui
#include "imgui-SFML.h"
#include "imgui.h"
#include "imguiThemes.h"
#pragma endregion

// Game includes
#include "Craftingrecepies.h"
#include "blocks.h"
#include "buttonclass.h"
#include "declarations.h"
#include "entities.h"
#include "enum.h"
#include "items.h"
#include "memory_manager.h"

using namespace std;

HWND wind;

extern int displayed;
extern int moves;

sf::Sprite blocks_sprite;

extern int numberofitemslots;
extern items *inventory[INVENTORY_SIZE];
extern int slot;

uint8_t states = gamestates::mainmenu;

sf::Sprite mouse_sprite;
sf::Sprite player_sprite;
sf::Sprite tree_sprite;
sf::Sprite items_sprite;
sf::Sprite heart_sprite;

sf::Texture treetextures;
sf::Texture textures;
sf::Texture playertexture;

sf::Texture player_head_texture;
sf::Texture player_feet_texture;
sf::Texture player_back_texture;
sf::Texture player_front_texture;

sf::Texture slimetxture;
sf::Texture blueslimetxture;
sf::Texture itemstexture;
sf::Texture hearttexture;
sf::Texture sandslimetexture;
sf::Texture iceslimetexture;
sf::Texture smallblueslimetexture;
sf::Texture zombietexture;
sf::Texture mumytexture;
sf::Texture eschimotexture;

sf::Text text;

extern bool rightreleased;
extern bool leftreleased;
bool Tpressed;

bool zoomed = 0;
bool focused = 1;

int difficulty = 1;

int maploaded;
sf::Font font;

extern sf::Vector2i currentchest;

sf::Vector2u pointingto; // the block that the player is pointing;

int WIDE = 1100;
int HEIGHT = 650; /// pixeli

bl::blocks world[Gamelenght][Gameheight];
bl::blocks walls[Gamelenght][Gameheight];

sf::Clock breakblocktime;
sf::Clock attacktime;

playerentity player;

bool touchesentities;

int curentbiome = 0;
int lastbiome = 0;

extern float whaittime;
extern float spawnwaittime;

sf::View view(sf::FloatRect(0, 0, WIDE, HEIGHT));

extern Craftingrecepies recepies[100];
float deltatime;

std::vector<slimeentity> enemies;
std::vector<humanlikeenemy> humanlike_enemies;
std::vector<droppeditem> droppedi;

extern items *tempitems;

sf::RenderWindow window;
uint8_t curentblock = bl::type::gold;

int main() {
  srand(time(0));

  difficulty = 1;
  string mesage;

  // Initialize tempitems
  tempitems = new nonplaceble(0, 1);

  // Initialize inventory
  for (int i = 0; i < INVENTORY_SIZE; i++) {
    inventory[i] = new nonplaceble(0, 0);
  }

  resetnumberofitemslots();

  text.setOutlineColor(sf::Color::White);
  text.setOutlineThickness(1);

  sf::ContextSettings setting;
  window.create(sf::VideoMode(WIDE, HEIGHT), "Canvas Adventures!",
                sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

  // Initialize ImGui
  ImGui::SFML::Init(window);
  imguiThemes::green();

  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.FontGlobalScale = 2.f;
  ImGuiStyle &style = ImGui::GetStyle();
  style.Colors[ImGuiCol_WindowBg].w = 0.5f;

  WIDE = window.getSize().x;
  HEIGHT = window.getSize().y;
  view.setSize(sf::Vector2f(WIDE, HEIGHT));

  player.frametime = 1.0 / 20.0;
  player.sizeofentity.x = 32;
  player.sizeofentity.y = 64;

  text.setColor(sf::Color::Black);
  text.setCharacterSize(24);
  text.setFont(font);

  settextures(); // Sets all the textures
  lastbiome = curentbiome;

  sf::Clock myclock;
  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      // Process ImGui events
      ImGui::SFML::ProcessEvent(window, event);

      if (event.type == sf::Event::Closed)
        window.close();
      else if (event.type == sf::Event::Resized) {
        // Adjust the viewport when the window is resized
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
        WIDE = event.size.width;
        HEIGHT = event.size.height;
        view.setSize(sf::Vector2f(WIDE, HEIGHT));
      }

      // Process game events
      handleevents(window);
    }

    // Calculate the delta time
    sf::Time dt = myclock.restart();
    deltatime = dt.asSeconds();

    // Ensure delta time stays within normal bounds
    deltatime = std::min(deltatime, 1.f);
    deltatime = std::max(deltatime, 0.f);

    // ImGui update
    ImGui::SFML::Update(window, clock.restart());

    ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
    ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    ImGui::PopStyleColor(2);

    // Game UI with ImGui
    ImGui::Begin("Game Controls");
    ImGui::Text("Canvas Adventures Game");

    if (ImGui::Button("Return to Main Menu")) {
      returnToMainMenu();
    }

    ImGui::Text("FPS: %.1f", 1.0f / deltatime);
    ImGui::End();

    // Game state handling
    switch (states) {
    case mainmenu:
      mainmenuf();
      break;
    case game:
      // Game update logic
      moveplayer();
      checkcollision();

      // Update enemies
      for (size_t i = 0; i < enemies.size(); i++) {
        handleentity(enemies[i], GRAVITY);
        makemove(enemies[i], player);
      }

      for (size_t i = 0; i < humanlike_enemies.size(); i++) {
        handleentity(humanlike_enemies[i], GRAVITY);
        makemove(humanlike_enemies[i], player);
      }

      // Handle items
      for (size_t i = 0; i < droppedi.size(); i++) {
        if (!droppedi[i].handlegravity()) {
          droppedi.erase(droppedi.begin() + i);
          i--;
        }
      }

      // Clean up dead entities
      memory::cleanupDeadEntities();

      handle_background();
      timehandle();
      spawnmonster();
      fixplayerscreen();

      // Update view
      handleview(view, player, 15);
      window.setView(view);
      break;

    case invent:
      inventorystate();
      break;

    case crafting_state:
      crafting();
      break;

    case chest_state:
      loadchest(currentchest.x, currentchest.y);
      break;
    }

    // Clear window and draw game
    window.clear();

    // Draw game elements based on state
    if (states == mainmenu) {
      // Draw main menu
    } else if (states == game) {
      // Draw game
      handle_background();
      drawplayer();
      showhearts();
      drawitem();
    } else if (states == invent || states == crafting_state ||
               states == chest_state) {
      // Draw inventory/crafting UI
    }

    // Render ImGui
    ImGui::SFML::Render(window);

    window.display();
  }

  // Shutdown ImGui
  ImGui::SFML::Shutdown();

  // Clean up all allocated resources using our memory manager
  memory::cleanupAll();

  return 0;
}

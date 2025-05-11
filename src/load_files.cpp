#include "declarations.h"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <windows.h>

using std::string;

extern sf::RenderWindow window;
extern int maploaded;

sf::Texture loadfiles(string name) {
  sf::Texture texture;
  if (!texture.loadFromFile(name)) {
    char message[100] = "Can't load the ";
    strcat(message, name.c_str());
    strcat(message, " file");

    ::MessageBoxA(HWND_DESKTOP, message, "Error", MB_ICONWARNING | MB_OK);
    texture.loadFromFile("default.png");
  };
  return texture;
}

void dosave() {
  if (maploaded)
    savemap(maploaded);
  window.close();
}

#include "declarations.h"
#include <fstream>
#include <stdio.h>

extern int maploaded;
extern std::vector<droppeditem> droppedi;
extern sf::Vector2i currentchest;

items *chestbuffer[CHEST_SIZE];

void loadchest(int x, int y) {
  char a[50];

  // First, clear existing chest buffer to prevent memory leaks
  for (int i = 0; i < CHEST_SIZE; i++) {
    delete chestbuffer[i];
    chestbuffer[i] = nullptr;
  }

  if (maploaded == 1) {
    sprintf(a, "map1\\chests\\%d %d.txt", x, y);
  } else if (maploaded == 2) {
    sprintf(a, "map2\\chests\\%d %d.txt", x, y);
  } else if (maploaded == 3) {
    sprintf(a, "map3\\chests\\%d %d.txt", x, y);
  }

  ifstream infile(a);
  if (infile.is_open()) {
    int a, b, c;
    int i = 0;
    while (!infile.eof() && i < CHEST_SIZE) {
      infile >> a >> b >> c;
      if (a == 1) {
        chestbuffer[i] = new normalitems(b, c);
      } else if (a == 0) {
        chestbuffer[i] = new nonplaceble(b, c);
      }

      i++;
    }
    infile.close();

    // Initialize any remaining slots with empty items
    for (; i < CHEST_SIZE; i++) {
      chestbuffer[i] = new nonplaceble(0, 0);
    }

  } else {
    ofstream file(a);
    for (int i = 0; i < CHEST_SIZE; i++) {
      file << "0 0 0\n";
      chestbuffer[i] = new nonplaceble(0, 0);
    }
    file.close();
  }
}

void deletechest() {
  char a[50];

  if (maploaded == 1) {
    sprintf(a, "map1\\chests\\%d %d.txt", currentchest.x, currentchest.y);
  } else if (maploaded == 2) {
    sprintf(a, "map2\\chests\\%d %d.txt", currentchest.x, currentchest.y);
  } else if (maploaded == 3) {
    sprintf(a, "map3\\chests\\%d %d.txt", currentchest.x, currentchest.y);
  }

  std::ofstream file(a);

  for (int i = 0; i < CHEST_SIZE; i++) {
    if (chestbuffer[i]) {
      file << chestbuffer[i]->placeble() << " " << chestbuffer[i]->type << " "
           << (int)chestbuffer[i]->number << std::endl;
      delete chestbuffer[i];
      chestbuffer[i] = nullptr; // Set to null to prevent dangling pointer
    } else {
      file << "0 0 0" << std::endl;
    }
  }
  file.close();

  // Initialize chest buffer with empty items
  for (int i = 0; i < CHEST_SIZE; i++) {
    chestbuffer[i] = new nonplaceble(0, 0);
  }
}

void placechest(int x, int y) {

  char a[50];

  if (maploaded == 1) {
    sprintf(a, "map1\\chests\\%d %d.txt", x, y);
  } else if (maploaded == 2) {
    sprintf(a, "map2\\chests\\%d %d.txt", x, y);
  } else if (maploaded == 3) {
    sprintf(a, "map3\\chests\\%d %d.txt", x, y);
  }

  std::ofstream chest(a);
  for (int i = 0; i < CHEST_SIZE; i++) {
    chest << 0 << " " << 0 << " " << 0 << std::endl;
  }

  chest.close();
}

void breakchest(int x, int y) {
  char name[50];

  if (maploaded == 1) {
    sprintf(name, "map1\\chests\\%d %d.txt", x, y);
  } else if (maploaded == 2) {
    sprintf(name, "map2\\chests\\%d %d.txt", x, y);
  } else if (maploaded == 3) {
    sprintf(name, "map3\\chests\\%d %d.txt", x, y);
  }

  std::ifstream chest(name);
  if (chest.is_open()) {
    int a, b, c;

    while (!chest.eof()) {
      chest >> a >> b >> c;
      droppedi.push_back(droppeditem(a, b, x * 32, y * 32, c));
    }

    chest.close();
    remove(name);
  }
}

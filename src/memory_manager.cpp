#include "memory_manager.h"
#include "declarations.h"

// External global variables
extern std::vector<slimeentity> enemies;
extern std::vector<humanlikeenemy> humanlike_enemies;
extern std::vector<droppeditem> droppedi;
extern items *inventory[INVENTORY_SIZE];
extern items *chestbuffer[CHEST_SIZE];
extern items *tempitems;

namespace memory {

void clearEnemies(std::vector<slimeentity> &enemies,
                  std::vector<humanlikeenemy> &humanlike_enemies) {
  // std::vector handles memory deallocation automatically
  enemies.clear();
  humanlike_enemies.clear();
}

void clearDroppedItems(std::vector<droppeditem> &items) {
  // Since droppeditem has a proper destructor now, this will clean up properly
  items.clear();
}

void clearInventory(items **inventory, int size) {
  for (int i = 0; i < size; i++) {
    if (inventory[i]) {
      delete inventory[i];
      inventory[i] = nullptr;
    }
  }
}

void clearChestBuffer(items **chestBuffer, int size) {
  for (int i = 0; i < size; i++) {
    if (chestBuffer[i]) {
      delete chestBuffer[i];
      chestBuffer[i] = nullptr;
    }
  }
}

void cleanupAll() {
  // Clean up temporary items
  delete tempitems;
  tempitems = nullptr;

  // Clean up inventory
  clearInventory(inventory, INVENTORY_SIZE);

  // Clean up chest buffer
  clearChestBuffer(chestbuffer, CHEST_SIZE);

  // Clean up enemies and dropped items
  clearEnemies(enemies, humanlike_enemies);
  clearDroppedItems(droppedi);
}

void cleanupDeadEntities() {
  // Remove dead enemies
  for (size_t i = 0; i < enemies.size(); i++) {
    if (enemies[i].life <= 0 || !enemies[i].checktime()) {
      enemies.erase(enemies.begin() + i);
      i--; // Adjust index after removal
    }
  }

  // Remove dead humanlike enemies
  for (size_t i = 0; i < humanlike_enemies.size(); i++) {
    if (humanlike_enemies[i].life <= 0 || !humanlike_enemies[i].checktime()) {
      humanlike_enemies.erase(humanlike_enemies.begin() + i);
      i--; // Adjust index after removal
    }
  }
}

} // namespace memory
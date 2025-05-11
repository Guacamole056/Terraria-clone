#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "entities.h"
#include "items.h"
#include <vector>

// Memory management utilities
namespace memory {
// Function to clean up enemy vectors
void clearEnemies(std::vector<slimeentity> &enemies,
                  std::vector<humanlikeenemy> &humanlike_enemies);

// Function to clean up dropped items
void clearDroppedItems(std::vector<droppeditem> &items);

// Function to clean up inventory
void clearInventory(items **inventory, int size);

// Function to clean up chest buffer
void clearChestBuffer(items **chestBuffer, int size);

// Main cleanup function to call at program termination
void cleanupAll();

// Function to clean up dead entities during gameplay
void cleanupDeadEntities();
} // namespace memory

#endif // MEMORY_MANAGER_H
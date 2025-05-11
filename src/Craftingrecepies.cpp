#include "Craftingrecepies.h"

Craftingrecepies::Craftingrecepies(Craftebleitem result, Craftebleitem a,
                                   Craftebleitem b, Craftebleitem c,
                                   Craftebleitem d, int craftingstation_)
    : itemcreated(result), craftingstation(craftingstation_) {
  materials[0] = a;
  materials[1] = b;
  materials[2] = c;
  materials[3] = d;
}

void Craftingrecepies::create(Craftebleitem result, Craftebleitem a,
                              Craftebleitem b, Craftebleitem c, Craftebleitem d,
                              int craftingstation_) {
  itemcreated = result;
  materials[0] = a;
  materials[1] = b;
  materials[2] = c;
  materials[3] = d;
  craftingstation = craftingstation_;
};

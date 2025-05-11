#ifndef CRAFTINGRECEPIES_H
#define CRAFTINGRECEPIES_H
#include "items.h"

class Craftebleitem {
public:
  bool placeble;
  int type;
  int number;
  Craftebleitem() : placeble(false), type(0), number(0) {};
  Craftebleitem(bool placeble, int type, int number)
      : placeble(placeble), type(type), number(number) {};
};

class Craftingrecepies {
public:
  Craftingrecepies() : itemcreated(), materials(), craftingstation(0) {}
  Craftingrecepies(Craftebleitem result, Craftebleitem a, Craftebleitem b,
                   Craftebleitem c, Craftebleitem d, int craftingstation_);
  void create(Craftebleitem result, Craftebleitem a, Craftebleitem b,
              Craftebleitem c, Craftebleitem d, int craftingstation_);

  Craftebleitem itemcreated;
  Craftebleitem materials[4];
  int craftingstation;
};

#endif // CRAFTINGRECEPIES_H

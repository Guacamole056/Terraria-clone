#include "declarations.h"
#include "enum.h"
#include "items.h"
#include <SFML/Graphics.hpp>

droppeditem getdroppeditem(int type) {
  switch (type) {
  case bl::type::sand_ruby:
    return droppeditem(0, items::name::ruby);
  case bl::type::wood:
    return droppeditem(1, bl::type::woodenplank);
  case bl::type::leafs: {
    if (randompercent(10)) {
      return droppeditem(1, bl::type::sappling);
    } else {
      if (randompercent(10))
        return droppeditem(0, items::apple);
      else
        return droppeditem(1, 0);
    }
  };
  case bl::type::plants: {
    if (randompercent(5)) {
      return droppeditem(0, items::misseltoe);
    } else {
      return droppeditem(1, 0);
    }
  }

  default:
    return droppeditem(1, type);
  }
}

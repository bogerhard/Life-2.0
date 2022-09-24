#include <string>
#include "Item.h"

Item::Item(std::string n, std::string desc) {
  name = n;
  description = desc;
}

Item::~Item() {}

std::string Item::getName() {
  return name;
}

std::string Item::getDescription() {
  return description;
}

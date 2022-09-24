/**
* @author Kurt Clarke <kurt.clarke@uleth.ca>
* @date 2021-11-11
*/
#include <iostream>
#include <map>
#include <string>
#include "Inventory.h"


Inventory::Inventory() {
}

Inventory::Inventory(std::map<std::string, Item*> i) {
  items = i;
}

Inventory::~Inventory() {
  std::map<std::string, Item*>::iterator it;
  for (it = items.begin(); it != items.end(); ++it) {
    if (it->second) delete it->second;
  }
}

bool Inventory::findItem(std::string s) {
  return (items.find(s) != items.end());
}

void Inventory::addItem(std::string s, Item* item) {
  items[s] = item;
}

void Inventory::removeItem(std::string s) {
  items.erase(s);
}

Item* Inventory::getItem(std::string s) {
  return items[s];
}

void Inventory::showInventory() {
  std::map<std::string, Item*>::iterator it;
  std::cout << "Your Inventory: " << std::endl;
  for (it = items.begin(); it != items.end(); ++it) {
    std::cout << it->first << std::endl;
  }
}

std::map<std::string, Item*> Inventory::getInventory() {
  return items;
}

int Inventory::size() {
  return items.size();
}

bool Inventory::isEmpty() {
  if (items.size() == 0) {
    return true;
  } else {
    return false;
  }
}

/**
* @author Albert Arrieta <@albert.arrieta>
* @date 2021-11-11
*/
#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#include <map>
#include <string>
#include "Item.h"

class Inventory {
 public:
  /**
  * Default constructor initializes and empty Inventory
  **/
  Inventory();
  /**
  * Constructor
  */
  Inventory(std::map<std::string, Item*> items);

  /**
  * Destructor.
  */
  virtual ~Inventory();

  /**
  * Checks if an item is in an inventory or not.
  * @param s, the key of the item being searched for in the inventory map.
  */
  bool findItem(std::string s);

  /**
  * Adds item to a list of items the inventory is linked to in the room.
  * @param s, the key of the item in the inventory map
  * @param Item*, the Item being added.
  */
  void addItem(std::string s, Item* item);

  /**
  * Removes item from the list of items in the inventory that is linked
  * to the room.
  * @param s, the key of the item to be removed from the inventory map.
  */
  void removeItem(std::string s);

  /**
  * Returns the item the inventory is linked to.
  * @param s, the key of the item in the map to be retrieved.
  * @return the item to be returned.
  */
  Item* getItem(std::string s);

  /**
  * Displays the items listed in the inventory map.
  */
  void showInventory();

  /**
  * Returns the inventory.
  * @return the map that represents the inventory.
  */
  std::map<std::string, Item*> getInventory();

  /**
  * Returns the amount of items inside Inventory
  * @return the number of items in inventory
  */
  int size();

  /**
  * Returns true is inventory is empty. False otherwise.
  */
  bool isEmpty();

 private:
  std::map<std::string, Item*> items;
};

#endif

#include <map>
#include <string>
#include "Exceptions.h"
#include "Inventory.h"
#include "Item.h"
#include "gtest/gtest.h"


TEST(TestInventory, DefaultConstructorTest) {
  Inventory* i = new Inventory();

  std::map<std::string, Item*> inv = i->getInventory();
  bool isEmpty = inv.empty();
  EXPECT_TRUE(isEmpty);//change to true

  delete i;
}

TEST(TestInventory, ConstructorTest) {
  Item* apple = new Item("Apple", "A big red Apple");
  std::map<std::string, Item*> items;
  items["apple"] = apple;
  Inventory* i = new Inventory(items);
  EXPECT_EQ(i->getItem("apple"), apple);

  delete i, apple;
}

TEST(TestInventory, findTest) {
  Item* apple = new Item("Apple", "A big red Apple");
  std::map<std::string, Item*> items;
  items["apple"] = apple;
  Inventory* i = new Inventory(items);
  EXPECT_TRUE(i->findItem("apple"));
  EXPECT_FALSE(i->findItem("orange"));

  delete i, apple;
}

TEST(TestInventory, addItemTestSuccess) {
  Item* apple = new Item("Apple", "A big red Apple");
  Inventory* inv = new Inventory();
  inv->addItem("apple", apple);
  EXPECT_EQ(inv->getItem("apple"), apple);

  delete inv;
}

TEST(TestInventory, showInventoryTest) {
  Item* apple = new Item("Apple", "A big red Apple");
  Inventory* inv = new Inventory();
  inv->addItem("apple", apple);
  inv->showInventory();

  delete inv;
}

TEST(TestInventory, removeItemTestSuccess) {
  Item* apple = new Item("Apple", "A big red Apple");
  Inventory* inv = new Inventory();
  inv->addItem("apple", apple);
  inv->removeItem("apple");
  EXPECT_TRUE(inv->isEmpty());

  delete inv;
  delete apple;
}

// TEST(TestInventory, removeItemTestItemNonExistant) {
// //comment out for now until exceptions is implemented
// }

TEST(TestInventory, getItemTestSuccess) {
  Item* apple = new Item("Apple", "A big red Apple");
  Inventory* inv = new Inventory();
  inv->addItem("Apple", apple);
  EXPECT_EQ(inv->getItem("Apple"), apple);

  delete inv;
}

// TEST(TestInventory, getItemTestNonExistant) {
// //comment out for now until exceptions is implemented
// }

TEST(TestInventory, getInventoryTestSuccess) {
  Item* apple = new Item("Apple", "A big red Apple");
  Inventory* inv = new Inventory();
  inv->addItem("apple", apple);

  std::map<std::string, Item*> items = inv->getInventory();
  Item* itemFromInv = items["apple"];
  EXPECT_EQ(itemFromInv, apple);

  delete inv;
}

TEST(TestInventory, sizeTestSuccess) {
  Item* apple = new Item("Apple", "A big red Apple");
  Inventory* inv = new Inventory();
  inv->addItem("apple", apple);
  EXPECT_EQ(inv->size(), 1);

  delete inv;
}

TEST(TestInventory, isEmptyTestSuccess) {
  Item* apple = new Item("Apple", "A big red Apple");
  Inventory* inv = new Inventory();
  EXPECT_TRUE(inv->isEmpty());

  inv->addItem("apple", apple);
  EXPECT_FALSE(inv->isEmpty());
  delete inv;
}

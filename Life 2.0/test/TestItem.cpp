#include <string>
#include "Exceptions.h"
#include "Item.h"
#include "gtest/gtest.h"

TEST(TestItem, ConstructorTest) {
  Item* i = new Item("Apple", "A big red apple");
  std::string name = i->getName();
  std::string desc = i->getDescription();
  std::cout << name << " " << desc << std::endl;
  EXPECT_EQ(name, "Apple");
  EXPECT_EQ(desc, "A big red apple");

  delete i;
}

TEST(TestItem, getNameTest) {
  Item* i = new Item("Apple", "A big red apple");
  EXPECT_EQ(i->getName(), "Apple");

  delete i;
}

TEST(TestItem, getDescriptionTest) {
  Item* i = new Item("Apple", "A big red apple");
  EXPECT_EQ(i->getDescription(), "A big red apple");

  delete i;
}

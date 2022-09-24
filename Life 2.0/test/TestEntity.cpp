#include <string>
#include "Entity.h"
#include "Inventory.h"
#include "Item.h"
#include "gtest/gtest.h"


TEST(TestEntity, defaultConstructorTest) {
  Entity a;

  EXPECT_EQ("It's enigmatic...", a.getDescription());
}

TEST(TestEntity, constructorTest) {
  Inventory *inv1 = new Inventory;
  std::string desc = "It's the end of the world!!!";

  Entity *a = new Entity(inv1, desc);
  EXPECT_EQ("It's the end of the world!!!", a->getDescription());

  delete a;
}

TEST(TestEntity, getCheckItemTest) {
  Item *knife = new Item("knife", "for butter");
  Inventory *inv1 = new Inventory;
  std::string desc = "It's the end of the world!!!";
  inv1->addItem(knife->getName(), knife);

  Entity *a = new Entity(inv1, desc);

  EXPECT_FALSE(a->checkItem("sword"));
  EXPECT_TRUE(a->checkItem("knife"));

  delete a;
}


TEST(TestEntity, getDescriptionTest) {
  Entity a;
  EXPECT_EQ("It's enigmatic...", a.getDescription());

  std::string s = "It's becoming clearer...";

  a.setDescription(s);
  EXPECT_EQ("It's becoming clearer...", a.getDescription());

  a.displayDescription();
}

TEST(TestEntity, setDescriptionTest) {
  Inventory *inv1 = new Inventory;
  std::string desc = "It's the end of the world!!!";
  Entity *a = new Entity(inv1, desc);

  EXPECT_EQ("It's the end of the world!!!", a->getDescription());

  std::string s = "Maybe I overreacted";
  a->setDescription(s);
  EXPECT_EQ("Maybe I overreacted", a->getDescription());

  delete a;
}

TEST(TestEntity, displayDescriptionTest) {
  //
}
/* OBSOLETE DELEGATED TO SUB CLASSES
TEST(TestEntity, getActionListTest) {
  Inventory *inv1 = new Inventory;
  Interactions *al1 = new Interactions;
  string desc = "It's the end of the world!!!";
  Entity a;

  a.setActionList(al1);
  EXPECT_EQ(al1, a.getActionList());

  delete inv1;
}
*/
/* OBSOLETE DELEGATE TO SUB CLASSES
TEST(TestEntity, setActionListTest) {
  Inventory *inv1 = new Inventory;
  Interactions *al1 = new Interactions;
  string desc = "It's the end of the world!!!";
  Entity a;

  a.setActionList(al1);
  EXPECT_EQ(al1, a.getActionList());

  delete inv1;
}
/*
TEST(TestEntity, getInventoryTest) {
  Inventory *inv1 = new Inventory;
  Interactions *al1 = new Interactions;
  string desc = "It's the end of the world!!!";
  Entity a;

  a.setInventory(inv1);
  EXPECT_EQ(inv1, a.getInventory());
  //delete inv1, al1;
} */

TEST(TestEntity, setInventoryTest) {
  Inventory *inv1 = new Inventory;
  std::string desc = "It's the end of the world!!!";
  Entity a;

  a.setInventory(inv1);
  EXPECT_EQ(inv1, a.getInventory());
  //delete inv1;
}

TEST(TestEntity, checkItemTest) {
  Inventory *inv1 = new Inventory;
  std::string desc = "It's the end of the world!!!";
  Item* heroSword = new Item("sword",
  "A true hero's sword. It's kind of underwhelming...");
  Entity a;

  inv1->addItem("sword", heroSword);

  a.setInventory(inv1);
  EXPECT_EQ(inv1, a.getInventory());
  //delete heroSword;
  //delete inv1;
}

/* VOID DELEGATED TO SUB CLASSES
 TEST(TestEntity, checkInteractionTest) {
   Inventory *inv1 = new Inventory;
   string desc = "It's the end of the world!!!";
   RoomInteraction *boxJump = new RoomInteraction;
   Entity a;

   a->

   EXPECT_EQ(a, "jump"); // This needs to be modified.
   EXPECT_EQ(a, "grovel"); // This needs to be modified.
 } */

/* VOID DELEGATED TO SUB CLASSES
TEST(TestEntity, callInteractionTest) {
  // unsure of how to test.
} */

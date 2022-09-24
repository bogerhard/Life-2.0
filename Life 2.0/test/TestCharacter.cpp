#include <map>
#include <string>
#include "Entity.h"
#include "Inventory.h"
#include "Item.h"
#include "gtest/gtest.h"

TEST(TestCharacter, defaultConstructorTest) {
    Character* c = new Character("Jess");
    c->setDescription("Female Fighter");
    std::string name = c->getName();
    std::string desc = c->getDescription();
    std::cout << name << " " << desc << std::endl;
    EXPECT_EQ(name, "Jess");
    EXPECT_EQ(desc, "Female Fighter");

    delete c;
}

TEST(TestCharacter, addItemTest) {
  Character* c = new Character();
  Inventory* cInv = c->getInventory();
  Item* apple = new Item("Apple", "A big fat red apple");
  cInv->addItem("apple", apple);
  EXPECT_TRUE(c->checkForItem("apple", apple));

  delete c;
}

TEST(TestCharacter, checkForItemTest) {
  Character* c = new Character();
  Inventory* cInv = c->getInventory();
  std::map<std::string, Item*> items = cInv->getInventory();
  Item* apple = new Item("Apple", "A big fat red apple");
  cInv->addItem("apple", apple);
  EXPECT_TRUE(c->checkForItem("apple", apple));

  delete c;
}

TEST(TestCharacter, setActionList) {
  Character* r1 = new Character();
  CharacterInteractions * newRint = new CharacterInteractions;
  ActionResultList * lookHere = new ActionResultList(1);
  newRint->setActionResult(lookHere);
  lookHere->setActionResult("speak", "you have spoken");

  r1->setActionList(newRint);

  EXPECT_EQ(r1->getCharacterActionList(), newRint);

  delete r1;
}


TEST(TestCharacter, setRoomTest) {
  Character* c = new Character("Jess");
  Room* r = new Room();
  c->setRoom(r);
  Room* actualRoom = c->getRoom();
  EXPECT_EQ(actualRoom, r);

  r->removeCharacter(c);
  delete c;
  delete r;
}

TEST(TestCharacter, checkMoveValidTrueTest) {
  Character* c =  new Character();
  Room* r1 = new Room();
  c->setRoom(r1);
  Room* r2 = new Room();
  r1->addAdjacentRoom("top", r2);
  EXPECT_TRUE(c->checkMoveValid("top"));
  EXPECT_FALSE(c->checkMoveValid("bottom"));


  delete c;
  delete r1;
  delete r2;
}

// TEST(TestCharacter, checkMoveValidFalseTest) {
//   Character* c =  new Character;
//   Room* r = new Room;
//   c->setRoom(r);
//   EXPECT_FALSE(c->checkMoveValid("bottom"));
//
//  delete c;
//  delete r;
// }
//COMMENTED BECAUSE MIGHT NEED EXCEPTIONS

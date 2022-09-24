#include <map>
#include <string>
#include <list>
#include "Exceptions.h"
#include "Entity.h"
#include "gtest/gtest.h"


TEST(TestRoom, ConstructorTestSuccess) {
  Room* r = new Room();
  delete r;
}

TEST(TestRoom, getAdjacentRoomsTestSuccess) {
  Room* r1 = new Room();
  Room* r2 = new Room();
  Room* r3 = new Room();

  r1->addAdjacentRoom("top", r2);
  r1->addAdjacentRoom("left", r3);

  std::map<std::string, Room*> r1Rooms = r1->getAdjacentRooms();
  Room* topRoom = r1Rooms["top"];
  Room* leftRoom = r1Rooms["left"];

  EXPECT_EQ(topRoom, r2);
  EXPECT_EQ(leftRoom, r3);

  delete r1;
  delete r2;
  delete r3;
}

TEST(TestRoom, setActionList) {
  Room* r1 = new Room();
  RoomInteractions * newRint = new RoomInteractions;
  ActionResultList * lookHere = new ActionResultList(2);
  newRint->setActionResult(lookHere);
  lookHere->setActionResult("look", "It works!!!");

  r1->setActionList(newRint);

  EXPECT_EQ(r1->getRoomActionList(), newRint);

  delete r1;
}

TEST(TestRoom, findAdjacentRoomTestSuccess) {
  Room* r1 = new Room();
  Room* r2 = new Room();
  r1->addAdjacentRoom("top", r2);

  EXPECT_EQ(r1->findAdjacentRoom("top"), r2);

  delete r1;
  delete r2;
}

TEST(TestRoom, addAdjacentRoomTestSuccess) {
  Room* r1 = new Room();
  Room* r2 = new Room();
  Room* r3 = new Room();
  Room* r4 = new Room();
  Room* r5 = new Room();
  r1->addAdjacentRoom("top", r2);
  r1->addAdjacentRoom("left", r3);
  r1->addAdjacentRoom("bottom", r4);
  r1->addAdjacentRoom("right", r5);

  std::map<std::string, Room*> r1Adj = r1->getAdjacentRooms();

  EXPECT_EQ(r1Adj["top"], r2);
  EXPECT_EQ(r1Adj["left"], r3);
  EXPECT_EQ(r1Adj["bottom"], r4);
  EXPECT_EQ(r1Adj["right"], r5);

  delete r5;
  delete r4;
  delete r3;
  delete r2;
  delete r1;
}

TEST(TestRoom, removeAdjacentRoomTestSuccess) {
  Room* r1 = new Room();
  Room* r2 = new Room();
  Room* r3 = new Room();
  Room* r4 = new Room();
  Room* r5 = new Room();
  r1->addAdjacentRoom("top", r2);
  r1->addAdjacentRoom("left", r3);
  r1->addAdjacentRoom("bottom", r4);
  r1->addAdjacentRoom("right", r5);

  r1->removeAdjacentRoom("top");
  std::map<std::string, Room*> r1Adj = r1->getAdjacentRooms();

  EXPECT_NE(r1Adj["top"], r2);
  EXPECT_EQ(r1Adj["left"], r3);
  EXPECT_EQ(r1Adj["bottom"], r4);
  EXPECT_EQ(r1Adj["right"], r5);

  delete r5;
  delete r4;
  delete r3;
  delete r2;
  delete r1;
}

TEST(TestRoom, addCharacterTestSuccess) {
  Room* r1 = new Room();
  Character* Bobby = new Character("Bobby");
  r1->addCharacter(Bobby);
  std::list<Character*> characterList = r1->getRoomEntities();

  EXPECT_TRUE(r1->findCharacter(Bobby)); // this is broken.

  delete r1;
}

TEST(TestRoom, removeCharacterTestSuccess) { //This induces a seg fault TF?
  Room* r1 = new Room();
  Character* Bobby = new Character("Bobby");

  r1->addCharacter(Bobby);
  r1->removeCharacter(Bobby);
  EXPECT_FALSE(r1->findCharacter(Bobby));

  delete r1;
  delete Bobby;
}

TEST(TestRoom, findCharacterTestSuccess) {
  Room* r1 = new Room();
  Character* Bobby = new Character("Bobby");
  Character* Brie = new Character("Brie");

  r1->addCharacter(Bobby);
  EXPECT_TRUE(r1->findCharacter(Bobby));
  EXPECT_FALSE(r1->findCharacter(Brie));
  r1->removeCharacter(Bobby);
  r1->removeCharacter(Brie);

  delete Bobby;
  delete Brie;
  delete r1;
}

TEST(TestRoom, findCharacterNameTestSuccess) {
  Room* r1 = new Room();
  Character* Bobby = new Character("Bobby");
  r1->addCharacter(Bobby);
  EXPECT_TRUE(r1->findCharacterName("Bobby"));
  EXPECT_FALSE(r1->findCharacterName("Brie"));

  delete r1;
}

TEST(TestRoom, getRoomEntitiesTestSuccess) {
  Room* r1 = new Room();
  Character* Bobby = new Character("Bobby");
  Character* Becca = new Character("Becca");
  Character* Ella = new Character("Ella");
  Character* Nathan = new Character("Nathan");
  Character* Gary = new Character("Gary");

  r1->addCharacter(Bobby);
  r1->addCharacter(Becca);
  r1->addCharacter(Ella);
  r1->addCharacter(Nathan);
  r1->addCharacter(Gary);

  EXPECT_EQ(r1->getRoomEntities().size(), 5);

  delete r1;
}

TEST(TestRoom, getRoomEntitiesTestEmpty) {
  Room* r1 = new Room();
  EXPECT_TRUE(r1->getRoomEntities().empty());
  delete r1;
}

TEST(TestRoom, getCharacterTestSuccess) {
  Room* r1 = new Room();
  Character* Bobby = new Character("Bobby");
  Character* Becca = new Character("Becca");
  Character* Ella = new Character("Ella");
  Character* Nathan = new Character("Nathan");
  Character* Gary = new Character("Gary");

  r1->addCharacter(Bobby);
  r1->addCharacter(Becca);
  r1->addCharacter(Ella);
  r1->addCharacter(Nathan);
  r1->addCharacter(Gary);

  EXPECT_EQ(r1->getCharacter("Bobby"), Bobby);
  EXPECT_EQ(r1->getCharacter("Becca"), Becca);
  EXPECT_EQ(r1->getCharacter("Ella"), Ella);
  EXPECT_EQ(r1->getCharacter("Nathan"), Nathan);
  EXPECT_EQ(r1->getCharacter("Gary"), Gary);

  EXPECT_THROW(r1->getCharacter("SirMeowsAlot"), invalid_parameter_error);

  delete r1;
}

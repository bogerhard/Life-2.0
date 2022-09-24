#include "Interactions.h"
#include "Entity.h"
#include "gtest/gtest.h"

TEST(TestInteractions, defaultConstructorTest) {
}

TEST(TestInteractions, getActionResultTest) {
  RoomInteractions* in = new RoomInteractions();
  ActionResultList * actRlist = new ActionResultList();
  actRlist->addActionResult("sleep", "Dream Deeply");

  in->setActionResult(actRlist);

  EXPECT_EQ("Dream Deeply", in->getActionResult()->getActionResult("sleep"));

  delete in;
}

TEST(TestInteractions, setActionResultTest) {
  RoomInteractions* in = new RoomInteractions();

  delete in;
}

TEST(TestInteractions, setRoomTest2) {
  RoomInteractions* in = new RoomInteractions();
  Room* room1 = new Room();
  Character * chara1 = new Character("Amelia");

  in->setRoom(room1);
  room1->addCharacter(chara1);

  EXPECT_EQ(100, (in->getRoom()->getCharacter("Amelia")->getStat("health")));

  room1->removeCharacter(chara1);
  delete chara1;
  delete room1;
  delete in;
}

TEST(TestInteractions, changingAPlayersStatsTest4) {
  RoomInteractions* in = new RoomInteractions();
  Room* room1 = new Room();
  Character * chara1 = new Character("Amelia");

  in->setRoom(room1);
  room1->addCharacter(chara1);

  EXPECT_EQ(100, (in->getRoom()->getCharacter("Amelia")->getStat("health")));

  room1->removeCharacter(chara1);
  delete chara1;
  delete room1;
  delete in;
}

TEST(TestInteractions, setActionResultTest1) {
  RoomInteractions* in = new RoomInteractions();

  delete in;
}

TEST(TestInteractions, setRoomTest1) {
  RoomInteractions* in = new RoomInteractions();
  Room* r = new Room();

  in->setRoom(r);

  EXPECT_EQ(in->getRoom(), r);

  delete in;
  delete r;
}

TEST(TestInteractions, changingAPlayersStatsTest3) {
  RoomInteractions* in = new RoomInteractions();
  Room* room1 = new Room();
  Character * chara1 = new Character("Amelia");

  in->setRoom(room1);
  room1->addCharacter(chara1);

  EXPECT_EQ(100, (in->getRoom()->getCharacter("Amelia")->getStat("health")));

  room1->removeCharacter(chara1);
  delete chara1;
  delete room1;
  delete in;
}

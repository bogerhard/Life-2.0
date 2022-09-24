#include <string>
#include <list>
#include "Entity.h"
#include "Inventory.h"
#include "Item.h"
#include "gtest/gtest.h"

TEST(TestActionResultList, DefaultConstructorTest) {
  ActionResultList* i = new ActionResultList();

  EXPECT_TRUE(i->isEmpty());//change to true

  delete i;
}

TEST(TestActionResultList, intConstructorTest) {
  ActionResultList* empty = new ActionResultList(0);
  ActionResultList* chara = new ActionResultList(1);
  ActionResultList* roomba = new ActionResultList(2);

  EXPECT_TRUE(empty->isEmpty());//change to true
  EXPECT_FALSE(chara->isEmpty());//change to true
  EXPECT_FALSE(roomba->isEmpty());//change to true

  EXPECT_EQ(empty->getActionResult(""), "");
  EXPECT_EQ(chara->getActionResult("meow"), "");
  EXPECT_EQ(roomba->getActionResult("growl"), "");
  EXPECT_EQ(chara->getActionResult("speak"), "Hello....");
  EXPECT_EQ(chara->getActionResult("touch"), "\"Please don't\"");
  EXPECT_EQ(chara->getActionResult("kiss"), "Let's not");
  EXPECT_EQ(roomba->getActionResult("look"), "nothing");
  EXPECT_EQ(roomba->getActionResult("interact"), "With what?");
  EXPECT_EQ(roomba->getActionResult("examine"), "nothing stands out.");

  delete empty;
  delete chara;
  delete roomba;
}


TEST(TestActionResultList, removeActionResultTest) {
  ActionResultList* chara = new ActionResultList(1);
  ActionResultList* roomba = new ActionResultList(2);

  EXPECT_EQ(chara->getActionResult("kiss"), "Let's not");
  EXPECT_EQ(roomba->getActionResult("look"), "nothing");

  chara->removeActionResult("kiss");
  roomba->removeActionResult("look");

  EXPECT_EQ(chara->getActionResult("kiss"), "");
  EXPECT_EQ(roomba->getActionResult("look"), "");

  delete chara;
  delete roomba;
}

TEST(TestActionResultList, addActionResultTest) {
  ActionResultList* empty = new ActionResultList(0);

  EXPECT_TRUE(empty->isEmpty());//change to true

  empty->addActionResult("Meow", "I'm a talking cat...jerk.");
  EXPECT_FALSE(empty->isEmpty());
  EXPECT_EQ(empty->getActionResult("Meow"), "I'm a talking cat...jerk.");

  delete empty;
}

TEST(TestActionResultList, getActionResultsTest) {
  ActionResultList* chara = new ActionResultList(1);
  ActionResultList* roomba = new ActionResultList(2);

  std::list<std::string> temp = chara->getActionResults();

  EXPECT_EQ("kiss", temp.front());

  delete chara;
  delete roomba;
}

TEST(TestActionResultList, isEmptyTestSuccess) {
  ActionResultList* empty = new ActionResultList(0);
  EXPECT_TRUE(empty->isEmpty());

  delete empty;
}

TEST(TestActionResultList, displayActionResultsTestSuccess) {
  ActionResultList* empty = new ActionResultList(1);

  empty->displayActionResults("kiss");

  delete empty;
}

TEST(TestActionResultList, setActionResultTest) {
  ActionResultList* empty = new ActionResultList(0);

  EXPECT_TRUE(empty->isEmpty());//change to true

  empty->addActionResult("Meow", "I'm a talking cat...jerk.");
  EXPECT_FALSE(empty->isEmpty());
  EXPECT_EQ(empty->getActionResult("Meow"), "I'm a talking cat...jerk.");
  empty->setActionResult("Meow", "Meow Meow");
  EXPECT_EQ(empty->getActionResult("Meow"), "Meow Meow");

  delete empty;
}

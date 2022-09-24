#include "Entity.h"
#include "Inventory.h"
#include "Item.h"
#include "gtest/gtest.h"


TEST(TestStats, DefaultConstructorTest) {
  Stats* i = new Stats();

  EXPECT_EQ(i->getStat("health"), 100);
  EXPECT_EQ(i->getStat("morality"), 0);
  EXPECT_EQ(i->getStat("humanity"), 0);
  EXPECT_EQ(i->getStat("puzzles"), 0);


  i->removeStat("health");
  i->removeStat("morality");
  i->removeStat("humanity");
  i->removeStat("puzzles");


  EXPECT_TRUE(i->isEmpty());//change to true

  delete i;
}

TEST(TestStats, setStatTest) {
  Stats* i = new Stats();
  i->addStat("Health", 100);

  i->setStat("Health", 10);
  EXPECT_EQ(i->getStat("Health"), 10);
  i->setStat("Health", -300);
  EXPECT_EQ(i->getStat("Health"), -300);

  delete i;
}

TEST(TestStats, modifyStatTest) {
  Stats* i = new Stats();
  i->addStat("Health", 100);

  i->modifyStat("Health", 100);
  EXPECT_EQ(i->getStat("Health"), 200);
  i->modifyStat("Health", -300);
  EXPECT_EQ(i->getStat("Health"), -100);

  delete i;
}

TEST(TestStats, addStatTest) {
  Stats* i = new Stats();
  i->addStat("Health", 100);
  EXPECT_EQ(i->getStat("Health"), 100);

  i->addStat("Mana", 10);
  EXPECT_EQ(i->getStat("Mana"), 10);

  delete i;
}

TEST(TestStats, removeStatTestSuccess) {
  Stats* s = new Stats();
  s->addStat("Health", 10);
  s->removeStat("Health");
  s->removeStat("health");
  s->removeStat("morality");
  s->removeStat("humanity");
  s->removeStat("puzzles");

  EXPECT_TRUE(s->isEmpty());

  delete s;
}

TEST(TestStats, getStatTestSuccess) { // error here
  Stats* s = new Stats();
  s->addStat("Mana", 100);
  EXPECT_EQ(s->getStat("Mana"), 100);

  delete s;
}

TEST(TestStats, isEmptyTestSuccess) {
  Stats* s = new Stats();
  EXPECT_FALSE(s->isEmpty());

  s->removeStat("health");
  s->removeStat("morality");
  s->removeStat("humanity");
  s->removeStat("puzzles");

  EXPECT_TRUE(s->isEmpty());

  delete s;
}

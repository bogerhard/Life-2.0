#include "Entity.h"
#include "Inventory.h"
#include "Item.h"
#include "gtest/gtest.h"


TEST(TestPlayer, defaultConstructorTest) {
    Player* c = new Player();
    Room* room1 = new Room();

    c->setRoom(room1);
    EXPECT_EQ(c->getName(), "Player");
    EXPECT_EQ(c->getRoom(), room1);
    EXPECT_EQ(c->getStat("health"), 100);
    EXPECT_EQ(c->getStat("humanity"), 0);
    EXPECT_EQ(c->getStat("morality"), 0);

    delete c;
    delete room1;
}

TEST(TestPlayer, DISABLED_playerMoveTest) {
    Player* c = new Player();
    Room* room1 = new Room();
    Room* room2 = new Room();
    room1->addAdjacentRoom("north", room2);

    c->setRoom(room1);
    EXPECT_EQ(c->getRoom(), room1);

    c->playerMove("south");
    EXPECT_EQ(c->getRoom(), room1);

    c->playerMove("north");
    EXPECT_EQ(c->getRoom(), room2);
    delete room1;
    delete room2;
}

TEST(TestPlayer, interactRoomObjectTest) {
    Player* c = new Player();
    Room* room1 = new Room();
    Item* mrMeow = new Item("cat", "Sir MeowsaLot");
    room1->getInventory()->addItem(mrMeow->getName(), mrMeow);

    c->setRoom(room1);

    c->playerPickUpItem("item");
    EXPECT_EQ(c->getInventory()->size(), 0);
    EXPECT_EQ(c->getRoom()->getInventory()->size(), 1);

    c->playerPickUpItem("cat");
    EXPECT_EQ(c->getInventory()->size(), 1);
    EXPECT_EQ(c->getRoom()->getInventory()->size(), 0);

    c->playerDropItem("item");
    EXPECT_EQ(c->getInventory()->size(), 1);
    EXPECT_EQ(c->getRoom()->getInventory()->size(), 0);

    c->playerDropItem("cat");
    EXPECT_EQ(c->getInventory()->size(), 0);
    EXPECT_EQ(c->getRoom()->getInventory()->size(), 1);

    room1->removeCharacter(c);
    delete c;
    delete room1;
}

TEST(TestPlayer, useItemtest) {
    Player* c = new Player();
    Room* room1 = new Room();
    Item* potion = new Item("potion", "mmm delicious");
    Item* monkeyPaw = new Item("monkeyPaw", "Let's not use this...");

    c->getStats()->setStat("health", 50);
    EXPECT_EQ(c->getStats()->getStat("health"), 50);
    c->getInventory()->addItem(potion->getName(), potion);
    c->playerUseItem("potion");
    EXPECT_EQ(c->getStats()->getStat("health"), 100);

    room1->removeCharacter(c);
    delete c;

    delete potion;
    delete monkeyPaw;
    delete room1;
}

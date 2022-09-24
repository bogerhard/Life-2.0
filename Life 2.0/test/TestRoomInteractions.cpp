#include "Interactions.h"
#include "Entity.h"
#include "gtest/gtest.h"


TEST(TestRoomInteractions, defaultConstructorTest) {
  // What should we test?
}

TEST(TestRoomInteractions, testoutputFunctions) {
  Room* in = new Room();

    in->getRoomActionList()->roomLook();
    in->getRoomActionList()->roomInteract();
    in->getRoomActionList()->roomExamine();
    in->getRoomActionList()->roomHelp();
    in->getRoomActionList()->roomTouch();
    in->getRoomActionList()->roomUse();

  delete in;
}

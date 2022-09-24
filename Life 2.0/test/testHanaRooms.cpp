#include <sstream>
#include <iostream>
#include "Interactions.h"
#include "Entity.h"
#include "gtest/gtest.h"


TEST(testHanaRooms, KindessRoom) {
  KindessRoomInts * kindness = new KindessRoomInts;
  RightOrWrongRoomInts* rowInt = new RightOrWrongRoomInts();
  PatienceRoomInts* patInt = new PatienceRoomInts();
  HonestyRoomInts* honInt = new HonestyRoomInts();

  kindness->roomHelp();
  rowInt->roomHelp();
  patInt->roomHelp();
  honInt->roomHelp();

  delete kindness;
  delete rowInt;
  delete patInt;
  delete honInt;
}

TEST(AlbertsRooms, DogKeyRoom) {
  Room* keyRoom = new Room();
  Room* lockedDoorRoom = new Room();
  DogKeyRoomInts* dkrInts = new DogKeyRoomInts(keyRoom);
  DogLockedDoorRoomInts* ldrInts = new DogLockedDoorRoomInts(lockedDoorRoom);

  dkrInts->roomHelp();
  dkrInts->roomExamine();
  dkrInts->roomLook();

  ldrInts->roomHelp();
  ldrInts->roomExamine();
  ldrInts->roomLook();

  delete keyRoom;
  delete lockedDoorRoom;
  delete dkrInts;
  delete ldrInts;
}

TEST(KurtsRooms, JesterRooms) {
  DrAvikInteractions * avikInts = new DrAvikInteractions();
  JesterInteractions * newJester = new JesterInteractions();
  VaguenessRoomInts * vagueRoomInts = new VaguenessRoomInts();
  DecisionTheoryRoomInts * decTheoryInts = new DecisionTheoryRoomInts();

  vagueRoomInts->roomHelp();
  vagueRoomInts->roomExamine();
  vagueRoomInts->roomHelp();

  decTheoryInts->roomLook();
  decTheoryInts->roomHelp();
  decTheoryInts->roomHelp();

  delete avikInts;
  delete newJester;
  delete vagueRoomInts;
  delete decTheoryInts;
}

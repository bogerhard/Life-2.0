#include "Interactions.h"
#include "Entity.h"
#include "gtest/gtest.h"

TEST(TestCharacterInteractions, defaultConstructorTest) {
  // What should we test?
}

TEST(TestCharacterInteractions, validActionTest) {
  Character* in = new Character();

    in->getCharacterActionList()->characterSpeak();
    in->getCharacterActionList()->characterKiss();
    in->getCharacterActionList()->characterTouch();
    in->getCharacterActionList()->characterInteract();

  delete in;
}

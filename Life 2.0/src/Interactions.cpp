#include "Interactions.h"
#include "Entity.h"
#include "Game.h"
#include "Input.h"
#include <algorithm>
#include <string>
#include <list>
#include <iostream>


Interactions::Interactions() {
}

Interactions::~Interactions() {
  delete action;
}

ActionResultList* Interactions::getActionResult() {
  return action;
}

void Interactions::setActionResult(ActionResultList* alist) {
  if (action) delete action; // This is broken fix later.
  action = alist;
}

/**
Room Interactions
**/
Room* Interactions::getRoom() {
  return room;
}

void Interactions::setRoom(Room* r) {
  room = r;
}

RoomInteractions::RoomInteractions() {
  action = new ActionResultList(2);
}

RoomInteractions::~RoomInteractions() {
}

void RoomInteractions::roomLook() {
  std::cout << getRoom()->getDescription() << std::endl << std::endl;
}

void RoomInteractions::roomInteract() {
  std::cout << action->getActionResult("interact") << std::endl << std::endl;
}

void RoomInteractions::roomExamine() {
  std::cout << action->getActionResult("examine") << std::endl << std::endl;
}

void RoomInteractions::roomHelp() {
  std::cout << "There's not much here. Try interacting with characters"
    << " or moving to another room" << std::endl;
}

void RoomInteractions::roomTouch() {
  std::cout << action->getActionResult("touch") << std::endl << std::endl;
}

void RoomInteractions::roomUse() {
  std::cout << action->getActionResult("use") << std::endl << std::endl;
}

/**
Character Interactions;
**/
CharacterInteractions::CharacterInteractions() {
  action = new ActionResultList(1);
}

CharacterInteractions::~CharacterInteractions() {
}

Character* CharacterInteractions::getCharacter() {
  return character;
}

void CharacterInteractions::setCharacter(Character* c) {
  character = c;
}

void CharacterInteractions::characterSpeak() {
  std::cout << action->getActionResult("speak") << std::endl;
}

void CharacterInteractions::characterUseItem(std::string s) {
  if (s == "potion" && getCharacter()->checkItem(s)) {
    std::cout << "Delicious..." << std::endl;
    getCharacter()->getInventory()->removeItem(s);
    if ((getCharacter()->getStats()->getStat("health")) < 50) {
      getCharacter()->getStats()-> modifyStat("health", 50);
    } else {
      getCharacter()->getStats()-> setStat("health", 100);
    }
  } else if (s == "key" && getCharacter()->checkItem(s)
    && room->getDescription() ==
    "The room with a locked door. On the south side of the room,"
    " there is a locked door with a key hole. On the north side of the room,"
    " there is a box with 3 blue dog toys in it.") {
    // action->displayActionResults("unlockSuccess");
    std::cout << "The key worked! Now you can move into the south side door!"
              << std::endl;
    std::cout << this->room->getDescription() << std::endl;

    //make exit room an adjacent room to lockedDoorRoom
    Character* puppy = new Character("puppy");
    PuppyInteractions* pi = new PuppyInteractions(puppy);
    puppy->setActionList(pi);
    Item* pistol = new Item("A pistol", "A gun, looks like it's loaded.");
    Room* exitRoom = new Room();
    exitRoom->addAdjacentRoom("north", room);
    puppy->setRoom(exitRoom);
    exitRoom->setDescription("The room inside the locked door."
    " At the center of the room, there is a loaded pistol."
    " At the south side of the room there is a cute puppy."
    " on a leash attached to a pole.");
    Inventory* exrInv = exitRoom->getInventory();
    exrInv->addItem("pistol", pistol);
    exitRoom->addCharacter(puppy);

    Interactions* exrInteractions = exitRoom->getRoomActionList();
    DogExitRoomInts* derInts = new DogExitRoomInts(exitRoom);
    exitRoom->setActionList(derInts);
    RoomInteractions* exitRoomInteractions = exitRoom->getRoomActionList();
    room->addAdjacentRoom("south", exitRoom);
    room->getCharacter("Player")->getInventory()->removeItem("key");
  } else if (s == "pistol" && getCharacter()->checkItem(s)
    && room->getDescription() ==
  "The room inside the locked door."
  " At the center of the room, there is a loaded pistol."
  " At the south side of the room there is a cute puppy."
  " on a leash attached to a pole.") {
    int choice;
    bool loop = true;

    while (loop == true) {
      std::cout << "1. Shoot the puppy" << std::endl;
      std::cout << "2. Shoot yourself" << std::endl;

      std::cin >> choice;
      std::cout << choice << std::endl;
      std::cin.clear();
      std::cin.ignore(500, '\n');
      system("clear");
      //shoot at dog
      if (choice == 1) {
        action->displayActionResults("shootPuppy");
        room->getCharacter("Player")->getStats()->setStat("morality", -5);
        room->getCharacter("Player")->getStats()->setStat("humanity", +10);

        std::cout << "BANG!!!!!....................." << std::endl;
        std::cout <<"...it was a blank?..." << std::endl;
        std::cout <<"Still alive, the puppy whimpers."
                  << "And slowly fades away." << std::endl;
        std::cout <<"A voice suddenly fills up the room." << std::endl;
        std::cout << "You are one messed up intelligent being......"
                  << " But I guess you have to do whatever"
                  << " in order to survive this place." << std::endl;
        loop = false;
      } else if (choice == 2) {
        action->displayActionResults("shootYourself");
        room->getCharacter("Player")->getStats()->modifyStat("morality", +5);
        room->getCharacter("Player")->getStats()->modifyStat("humanity", -10);

        std::cout << "BANG!!!!!....................." << std::endl;
        std::cout << "...it was a blank?..." << std::endl;
        std::cout << "Still alive, the puppy suddenly jumps onto you"
                  << " and licks your face."
                  << " Then slowly fades away." << std::endl;
        std::cout << "A voice suddenly fills up the room." << std::endl;
        std::cout << "Interesting choice..."
                  << " Lucky for you it was a blank."
                  << " But did that matter anyway"
                  << " if the puppy wasn't real?" << std::endl;

        loop = false;
      } else {
        std::cout << "YOU MUST CHOOSE TO KILL!!!!" << std::endl;
      }
    }
    room->getCharacter("Player")->getStats()->modifyStat("puzzles", +1);
    room->getCharacter("Player")->getInventory()->removeItem("pistol");
    std::cout << "This puzzle has been completed." << std::endl;
    std::cout << "Find your way back to the main room."
              << " (directions: north, west, north)" << std::endl;

    //CONNECT EXTERNAL ROOM HERE FOR THE NEXT PUZZLE.
    //make exit room an adjacent room to lockedDoorRoom
    // Room* exitRoom = new Room();
    // exitRoom->setDescription("The room inside the locked door."
    // " The door behind you is gone and you are trapped in this room."
    // " At the center of the room, there is a loaded pistol."
    // " At the south side of the room there is a cute puppy"
    // " on a leash attached to a pole."
    // " On the east side of the room there is a metal electronic door.");
    // exitRoom->addAdjacentRoom("north", room);
    // Once room is entered, previous room should be unaccesible
    // Inventory* exrInv = exitRoom->getInventory();
    // exrInv->addItem("pistol", pistol);
    // exitRoom->addCharacter(puppy);
    //
    // Interactions* exrInteractions = exitRoom->getRoomActionList();
    // DogExitRoomInts* derInts = new DogExitRoomInts(exitRoom);
    // exitRoom->setActionList(derInts);
    // RoomInteractions* exitRoomInteractions = exitRoom->getRoomActionList();
    // room->addAdjacentRoom("south", exitRoom);
    // room->getCharacter("Player")->getInventory()->removeItem("key");
  } else if (s == "bobbypin") {
        std::cout << "You unlocked the door! Move north" << std::endl;
  } else {
    std::cout << "How can I use that?" << std::endl;
  }
}


void CharacterInteractions::characterInteract() {
  std::cout << action->getActionResult("interact") << std::endl;
}

void CharacterInteractions::characterKiss() {
  std::cout << action->getActionResult("kiss") << std::endl;
}

void CharacterInteractions::characterTouch() {
  std::cout << action->getActionResult("touch") << std::endl;
}

/**
* KURT ROOM SET FUNCTIONS
**/
JesterInteractions::JesterInteractions() {
  action->removeActionResult("speak");
  action->addActionResult("speak", "a");
  action->setActionResult("kiss", "They enjoy it a little too much");
  action->setActionResult("touch", "They poke you back with a *wink* ");
}

JesterInteractions::~JesterInteractions() {}

void JesterInteractions::characterSpeak() {
  Input input;
  if (action->getActionResult("speak")[0] == 'a') {
  std::cout << "Uggh John...er...Dr.Avik let you in already?"
            << std::endl;
    std::cout<< std::endl << "     I told him I can't do this yet!!!";
    std::cout << std::endl
              << "     How is an AI suppossed to deal with paradoxes"
    << " in a week?" << std::endl;
    std::cout << "     You lot have been working on these for "
    << " millenia. \n" << std::endl;
    std::cout << std::endl << "I can't believe I'm going to ask"
    << " this but since I am clearly behind schedule. \n"
    << "Turing almighty! Who programmed me to be this useless?\n\n"
    << "Okay...alright I can do this. So, Dr.Avik gave me some questions. \n";
    std::cout << "I would like you to answer these questions";
    std::cout << " okay? simple. \nJust answer the questions. \n\n";
    std::cout << "     If you need help you can look at the"
    << "\n     the other rooms they are some data Dr.Avik"
    << "\n     provided for me.\n\n";
  action->setActionResult("speak", "b");
  } else if (action->getActionResult("speak")[0] == 'b') {
    std::cout << "Did you go to the other rooms? yes? no?"
      << "\n\n     you know what I don't care...."
      << std::endl << "\nSo question #1\n" << std::endl
      << "\n\n     I am lying."
      <<"\n\n Does that mean I am lying? or am I telling"
      << " the truth but then I'm lying.\n\n";
      while (true) {
        std::cout << "******************************************" << std::endl;
        std::cout << "You must be lying then? (lie)" << std::endl;
        std::cout << "It is true. (truth)" << std::endl;
        std::cout << "It is both true and not true (both)"<< std::endl;
        std::cout << "The statement is meaningless (neither)"<< std::endl;
        std::cout << "Let me get back to you on that.... (stop)" << std::endl;
        std::cout << "******************************************" << std::endl;

        std::string choice = "";
        choice = input.getInput();
        std::cout << std::endl;
        if (choice == "lie") {
          std::cout << "\n\n  Hmmm...it's a lie? but isn't it true then?\n";
          action->setActionResult("speak", "c");
          break;
        } else if (choice == "truth") {
            std::cout << "\n\n  Hmmm...it's true? but then isn't it a lie?\n";
            action->setActionResult("speak", "c");
            break;
        } else if (choice == "both") {
          std::cout << "\n\n  I guess that makes sense..."
                    << " would that solve the problem?\n";
          action->setActionResult("speak", "c");
          break;
        } else if (choice == "neither") {
          std::cout << "\n\n   So it's nonsense..."
                    << " They didn't tell me it could be nonsense...\n";
          action->setActionResult("speak", "c");
          break;
        } else if (choice == "stop") {
          std::cout << "\n\n   Alright, let's get back to it later\n";
          break;
        } else {
          std::cout << "  Uh I don't think that's a valid answer\n"
                    << std::endl;
        }
      }
      std::cout << "\nThis whole thing seems like a lie, but maybe"
      << " that is some perverse truth.\n\n";

  } else if (action->getActionResult("speak")[0] == 'c') {
    std::cout << "\n     I'm not particuarly impressed by your last answer"
      << "\n     but, I guess we can try this again."
      << std::endl << "\nSo question #2\n" << std::endl
      << "\nAt what point does one thing become something else?"
      <<"\n\n    If I replace a nail on a ship is it then a new ship?"
      <<"\n    What if I replace a plank?"
      <<"\n    What if I replace all the nails? all the planks?"
      <<"\n\nI think the problem is I just can't find a clear enough"
      <<"\ndefinition of what a ship is."
      << " When is it one ship and not another ship.\n\n";
      while (true) {
        std::cout << "******************************************" << std::endl;
        std::cout << "No matter the changes it is always the same (same)"
                  << std::endl;
        std::cout << "Even the slightest change means"
                  << " it is an entirely new thing (new)"
                  << std::endl;
        std::cout << "It changes at some point but I'm not sure when... (point)"
                  << std::endl;
        std::cout << "It is, until it is not. (yoda)"<< std::endl;
        std::cout << "Let me get back to you on that.... (stop)" << std::endl;
        std::cout << "******************************************" << std::endl;

        std::string choice = "";
        choice = input.getInput();
        std::cout << std::endl;
        if (choice == "same") {
          std::cout << "\n\n  So nothing ever changes?"
                    << " Then when do things end or begin?";
          action->setActionResult("speak", "d");
          break;
        } else if (choice == "new") {
            std::cout << "\n\n  Nothing is really anything for very long then?";
            action->setActionResult("speak", "d");
            break;
        } else if (choice == "point") {
          std::cout << "\n\n Right, that was the question."
                    << " At WHAT POINT?? Nevermind.";
          action->setActionResult("speak", "d");
          break;
        } else if (choice == "yoda") {
          std::cout << "\n\n Saying something,"
                    << " without really saying anything, huh.";
          action->setActionResult("speak", "d");
          break;
        } else if (choice == "stop") {
          break;
        } else {
          std::cout << "Invalid Action" << std::endl;
        }
      }
      std::cout << "\n\nI wonder if I am still the same thing I once was..."
        << "\nI guess I can check, I'm really just ones and zeros.\n\n";

  } else if (action->getActionResult("speak")[0] == 'd') {
    std::cout << "So, I checked. Since I first came here to now"
      << " approximately 10 gigabytes of my data has changed."
      << std::endl << "\nAnyway, question #3\n" << std::endl
      << "\n\n     The constant pursuit of pleasure prevents one from obtaining"
      << "\n     pleasure more than if one had never tried to pursue it at all."
      << "\n\n See this, this is why I'm still stuck in this ****** room!!!"
      << "\n...he added a censor function....HE ADDED A CENSOR FUNCTION!!!\n"
      << "\n Church, he really wants me to have no fun."
      << "\n\n\n How can pursuing something put you farther from it?\n\n";
      while (true) {
        std::cout << "******************************************" << std::endl;
        std::cout << "Eventually we grow weary, even of pleasure (weary)"
                  << std::endl;
        std::cout << "Honestly, I've found the pursuit of pleasure"
                  << " very rewarding (enjoy)" << std::endl;
        std::cout << "Using Dijkstra's Algorithm I can always find"
                  << " the shortest path to pleasure (algo)"<< std::endl;
        std::cout << "Let me get back to you on that.... (stop)" << std::endl;
        std::cout << "******************************************" << std::endl;

        std::string choice = "";
        choice = input.getInput();
        std::cout << std::endl;
        if (choice == "weary") {
          std::cout << "\n\n Well that doesn't sound fun."
                    << " I wonder what you should do then?";
          action->setActionResult("speak", "e");
          break;

        } else if (choice == "enjoy") {
            std::cout << "\n\n Alright then well it sounds like"
                      << " you've got it figured out!";
            action->setActionResult("speak", "e");
            break;
        } else if (choice == "algo") {
          std::cout << "\n\n I feel like I may have some misconceptions"
                    << " about you.";
          action->setActionResult("speak", "e");
          break;
        } else if (choice == "stop") {
          break;
        } else {
          std::cout << "Invalid Action" << std::endl;
        }
      }
      std::cout << "\n\nPersonally, I'm glad I was programmed with"
                << " clear, reachable, objectives"
      << "\nthat I get rewarded for when I achieve them. This pleasure"
      << "\nthing sounds reeeeaaal complicated. \n\n";
  } else if (action->getActionResult("speak")[0] == 'e') {
    std::cout << "Yippee, Hello there helper!!!"
      << "\nYou've been wrong about everything so far but we're almost done!"
      << std::endl << "\nSo, final question!!!\n" << std::endl
      << "\n\n  The closer you get to people the more they can hurt you."
      << "\n\nIt's strange I've seen pictures of people touching and"
      << "\nthey don't seem to be in pain. But I guess if that's the"
      << "\ncase you just have to stay away from eachother."
      << "\n\n  I think I might have solved this one on my own!!!"
      << " About time!!!\n\n";
      while (true) {
        std::cout << "******************************************"
                  << std::endl;
        std::cout << "Yes, I think you have the right idea (isolation)"
                  << std::endl;
        std::cout << "It's about the challenges of"
                  << " human relationships'(relationships)"
                  << std::endl;
        std::cout << "It is a balance there are perks to the risk (balance)"
                  << std::endl;
        std::cout << "Let me get back to you on that.... (stop)" << std::endl;
        std::cout << "******************************************" << std::endl;

        std::string choice = "";
        choice = input.getInput();
        std::cout << std::endl;
        if (choice == "isolation") {
          std::cout << "\n\n     All alone, ah yes I remember how wonderful it"
            << " was before you came. Can we go back to that?";
          action->setActionResult("speak", "f");
          room->getCharacter("Player")->getStats()->modifyStat("puzzles", +1);
          break;
        } else if (choice == "relationships") {
            std::cout << "\n\n Relationships? but haven't you min-maxed those?"
                      << "\n all of mine are based on"
                      << " a carefully calculated nash equilibria";
            action->setActionResult("speak", "f");
            room->getCharacter("Player")->getStats()->modifyStat("puzzles", +1);
            break;
        } else if (choice == "balance") {
          std::cout << "\n\n     A bit of pain for a bit of pleasure?"
            << "\n     Maybe it's the contrast that's important.";
          action->setActionResult("speak", "f");
          room->getCharacter("Player")->getStats()->modifyStat("puzzles", +1);
          break;
        } else if (choice == "stop") {
          break;
        } else {
          std::cout << "Invalid Action" << std::endl;
        }
      }
      std::cout << "\n\nI don't get why you would purposely get close"
        <<"\nto something that could cause you harm."
        <<"\nBut then again I'm not exactly human am I?\n\n";
  } else if (action->getActionResult("speak")[0] == 'f') {
    std::cout << "\n\n     Well that's all folks come again!!!"
      <<"\n     Or don't. In fact, please don't.\n\n";
  }
}

VaguenessRoomInts::VaguenessRoomInts() {
  action->removeActionResult("interact");
  action->addActionResult("interact", "a");
}

VaguenessRoomInts::~VaguenessRoomInts() {
}

void VaguenessRoomInts::roomHelp() {
  std::cout << "Try interacting with the rice, or leave." << std::endl;
}


void VaguenessRoomInts::roomExamine() {
  std::cout << "The table is engraved with a question...\n" << std::endl;
  std::cout << "How many grains of rice does it take to make a pile?\n"
    << std::endl;
  }

void VaguenessRoomInts::roomInteract() {
  if (action->getActionResult("interact").length() == 1) {
    std::cout << "You place a single grain of rice on the table...\n";
    std::cout << "\n      \"I'm pretty sure this isn't a pile yet...\"\n\n";

    std::string temp = action->getActionResult("interact");
    temp += 'a';
    action->setActionResult("interact", temp);

  } else if (action->getActionResult("interact").length() > 10) {
    std::cout << "Clearly, this needs to stop. Human or machine"
      << " you are clearly broken!!! So lets just end this." << std::endl;
      room->getCharacter("Player")->getStats()->setStat("health", 0);
      return;
  } else {
  std::cout << "You add another grain of rice..." << std::endl;

    std::string temp = action->getActionResult("interact");
    temp += 'a';
    action->setActionResult("interact", temp);

    std::cout << "There are now "
              << action->getActionResult("interact").length() - 1
      << " grains of rice on the table...\n\n" << std::endl;
    std::cout << "     I wonder if this is a pile now?\n" << std::endl;
  }
}

DecisionTheoryRoomInts::DecisionTheoryRoomInts() {}

DecisionTheoryRoomInts::~DecisionTheoryRoomInts() {}

void DecisionTheoryRoomInts::roomLook() {
  std::cout << "\nThis is probably going to be more "
  << " trouble than it's worth\n" << std::endl;
}

void DecisionTheoryRoomInts::roomExamine() {
  std::string muralNum;

  room->setDescription("On closer inspection you see three murals");
  room->getDescription();

  while (std::cin != "stop") {
  std::cout << std::endl
            << "Would you like to look at one of the Murals?" << std::endl;
  std::cout << "(mural1, mural2, mural3, stop): ";
  std::cin >> muralNum;
  if (muralNum == "mural1") {
    std::cout << "\nThe mural depicts a group of unique stick people all with"
              << " oddly shaped heads talking. One looks particularly angry."
              << std::endl;
    std::cout << "\"We dreamed of being tolerant"
              << " and thus tolerated everything.\""
              << std::endl;
  }
  if (muralNum == "mural2") {
    std::cout << "\nThe mural depicts a group of identitcal stick people"
              << " beating on one with a distinctive head..."
              << std::endl;
    std::cout << "\"Eventually we tolerated intolerance"
              << " until we were only intolerant.\"" << std::endl;
  }
  if (muralNum == "mural3") {
    std::cout << "\nThe mural depicts a group of unique stick people"
              << " pushing a particularly angry one off a cliff." << std::endl;
    std::cout << "\"Eventually in our intolerance we became intolerant of"
              << " our own intolerance itself and finally,"
              << " were truly tolerant.\""
              << std::endl;
  }
  if (muralNum == "stop") {
    std::cout << "\n\n" << std::endl;
  break;
}
}
}

//ALBERTS DOG ROOM Interactions

DogEntranceRoomInts::DogEntranceRoomInts(Room* r) {
  this->setRoom(r);
}

DogEntranceRoomInts::~DogEntranceRoomInts() {
}

void DogEntranceRoomInts::roomHelp() {
  std::cout << "These dog toys don't seem like we can pick them up..."
  << "Let's try moving rooms." << std::endl;
}

DogKeyRoomInts::DogKeyRoomInts(Room* r) {
  this->setRoom(r);
}

DogKeyRoomInts::~DogKeyRoomInts() {
}

void DogKeyRoomInts::roomHelp() {
  std::cout << "Those colours seem familiar."
            << " Try interacting with the safe in the room"
            << std::endl;
}

void DogKeyRoomInts::roomInteract() {
  int input;

  std::cout << "Enter the code" << std::endl;
  std:: cin >> input;
  if (input == 1337) {
    std::cout << "You enter the correct code."
              << " You open the safe and you pick up the key inside."
              << std::endl;
    //Give player key
    Item* dogKey = new Item("dogKey", "A key for some sort of door");
    Character* p = room->getCharacter("Player");
    Inventory* pInvp = p->getInventory();
    pInvp->addItem("key", dogKey);
  } else {
    std::cout << "BUZZZZ!!! INCORRECT CODE!!" << std::endl;
  }
}

void DogKeyRoomInts::roomExamine() {
  std::cout << "You examine the safe."
            << " To unlock the same there seems to be"
            << " a 4 digit passcode you will have to enter... "
            << std::endl;
  std::cout << "Each digit is marked with a letter."
            << " From left to right - R, G, B, Y" << std::endl;
}

void DogKeyRoomInts::roomLook() {
  action->displayActionResults("look");
}

DogLockedDoorRoomInts::DogLockedDoorRoomInts(Room* r) {
  this->setRoom(r);
}

DogLockedDoorRoomInts::~DogLockedDoorRoomInts() {
}

void DogLockedDoorRoomInts::roomHelp() {
  std::cout << "Maybe there is a key nearby?" << std::endl;
}

void DogLockedDoorRoomInts::characterUseItem(Item* item, Room* r) {
  if (item->getName() == "dogKey") {
    action->displayActionResults("unlockSuccess");
    //make exit room an adjacent room to lockedDoorRoom
    room->addAdjacentRoom("south", r);
  } else {
    action->displayActionResults("unlockFail");
  }
}

DogExitRoomInts::DogExitRoomInts(Room* r) {
  this->setRoom(r);
}

DogExitRoomInts::~DogExitRoomInts() {
}

void DogExitRoomInts::roomHelp() {
  std::cout << "I think I need to use that pistol..."
            << std::endl;
}

void DogExitRoomInts::roomInteract() {
  std::cout << "You pickup the pistol." << std::endl;
  Item* pistol = new Item("A pistol", "A gun, looks like it's loaded.");
  Character* p = room->getCharacter("Player");
  Inventory* pInvp = p->getInventory();
  pInvp->addItem("pistol", pistol);
}

PuppyInteractions::PuppyInteractions(Character* c) {
  this->character = c;
}

PuppyInteractions::~PuppyInteractions() {
}

void PuppyInteractions::characterSpeak() {
  std::cout << "Puppy: barks..." << std::endl;
}

void PuppyInteractions::characterTouch() {
  std::cout << "You pet the puppy."
            << " The puppy smiles at you and licks your hand. "
            << std::endl;
}

void PuppyInteractions::characterKiss() {
  std::cout << "You kiss the puppy...." << std::endl;
  std::cout << "Suddenly the puppy grows in size"
            << " and turns into a ferocious wolf." << std::endl;
  std::cout << "The gigantic wolf looks at you,"
            << " opens it's mouth wide and swallows you whole."
            << std::endl;

  character->getRoom()->getCharacter("Player")
  ->getStats()->setStat("health", 0);

  return;
}

/*
* Hana's Four Virtues Room Interactions
*/

/*
* Kindess Room Interactions
*/
KindessRoomInts::KindessRoomInts() {
  action->removeActionResult("interact");
  action->addActionResult("interact", "a");
}

KindessRoomInts::~KindessRoomInts() {
}

void KindessRoomInts::roomHelp() {
  std::cout << "Try interacting with the room" << std::endl;
}

void KindessRoomInts::roomInteract() {
  if (action->getActionResult("interact")[0] == 'a') {
    std::cout << "You can choose between two options:" << std::endl
              << "Press 1: help her" << std::endl
              << "Press 2: do not help her and move to the next room"
              << std::endl;

    int input;
    std:: cin >> input;
    std::cin.clear();
    std::cin.ignore(500, '\n');

    if (input == 1) {
      std::cout << "You chose to help her." << std::endl;
      std::cout << "Old lady becomes conscious and says thank you."
                << std::endl;
      std::cout << "Type 'stop' twice so that you can back to menu."
                << " And move to the next room." << std::endl << std::endl;
      room->getCharacter("Player")->getStats()->modifyStat("humanity", +5);
      room->getCharacter("Player")->getStats()->modifyStat("morality", +5);
      action->setActionResult("interact", "b");
      room->getCharacter("Player")->getStats()->modifyStat("puzzles", +1);
    } else {
      std::cout << "You chose not to help her. Head to the next room."
                << std::endl;
      std::cout << "Type 'stop' twice so that you can back to menu."
                << " And move to the next room." << std::endl << std::endl;
      room->getCharacter("Player")->getStats()->modifyStat("humanity", -5);
      room->getCharacter("Player")->getStats()->modifyStat("morality", -5);
      action->setActionResult("interact", "b");
      room->getCharacter("Player")->getStats()->modifyStat("puzzles", +1);
    }
  } else {
  std::cout << "There is nothing else to interact with" << std::endl;
  }
}


/*
* RightOrWrong Room Interactions
*/
RightOrWrongRoomInts::RightOrWrongRoomInts() {
  action->removeActionResult("interact");
  action->addActionResult("interact", "a");
}

RightOrWrongRoomInts::~RightOrWrongRoomInts() {
}

void RightOrWrongRoomInts::roomHelp() {
  std::cout << "Try interacting with the room" << std::endl;
}

void RightOrWrongRoomInts::roomInteract() {
  if (action->getActionResult("interact")[0] == 'a') {
    std::cout << "You can choose between two options:" << std::endl
              << "Press 1: Say nothing and give them your cigarette"
              << std::endl
              << "Press 2: Say that you should not smoke"
              << " and do not give them ciagreette" << std::endl;

    int input;
    std:: cin >> input;
    std::cin.clear();
    std::cin.ignore(500, '\n');

    if (input == 1) {
      std::cout << "You give teenagers cigarette and let them smoke."
                << std::endl;
      std::cout << "Type 'stop' twice so that you can back to menu."
                << " And move to the next room." << std::endl << std::endl;
      room->getCharacter("Player")->getStats()->modifyStat("morality", -5);
      room->getCharacter("Player")->getStats()->modifyStat("puzzles", +1);
      action->setActionResult("interact", "b");
    } else {
      std::cout << "You decided not to give teenagers cigarette"
                << " and tell them you should not smoke. Great behavior!"
                << std::endl;
      std::cout << "Type 'stop' twice so that you can back to menu."
                << " And move to the next room." << std::endl << std::endl;
      room->getCharacter("Player")->getStats()->modifyStat("morality", +5);
      room->getCharacter("Player")->getStats()->modifyStat("puzzles", +1);
      action->setActionResult("interact", "b");
    }
  } else {
  std::cout << "There is nothing else to interact with" << std::endl;
  }
}

/*
* Patience Room Interactions
*/
PatienceRoomInts::PatienceRoomInts() {
  action->removeActionResult("interact");
  action->addActionResult("interact", "a");
}

PatienceRoomInts::~PatienceRoomInts() {
}

void PatienceRoomInts::roomHelp() {
  std::cout << "Try interacting with the room" << std::endl;
}

void PatienceRoomInts::roomInteract() {
  if (action->getActionResult("interact")[0] == 'a') {
    std::cout << "You can choose between two options:" << std::endl
              << "Press 1: eat cake" << std::endl
              << "Press 2: do not eat cake" << std::endl;

    int input;
    std:: cin >> input;
    std::cin.clear();
    std::cin.ignore(500, '\n');

    if (input == 1) {
      std::cout << "You chose to eat cake. It was delicious!" << std::endl;
      std::cout << "Type 'stop' twice so that you can back to menu."
                << " And move to the next room." << std::endl << std::endl;
      room->getCharacter("Player")->getStats()->modifyStat("humanity", +5);
      room->getCharacter("Player")->getStats()->modifyStat("morality", -5);
      room->getCharacter("Player")->getStats()->modifyStat("puzzles", +1);
      action->setActionResult("interact", "b");
    } else {
      std::cout << "You chose not to eat cake. Great!" << std::endl;
      std::cout << "Type 'stop' twice so that you can back to menu."
                << " And move to the next room." << std::endl << std::endl;
      room->getCharacter("Player")->getStats()->modifyStat("humanity", -5);
      room->getCharacter("Player")->getStats()->modifyStat("morality", +5);
      room->getCharacter("Player")->getStats()->modifyStat("puzzles", +1);
      action->setActionResult("interact", "b");
    }
  } else {
  std::cout << "There is nothing else to interact with" << std::endl;
  }
}

/*
* Honesty Room Interactions
*/
HonestyRoomInts::HonestyRoomInts() {
  action->removeActionResult("interact");
  action->addActionResult("interact", "a");
}

HonestyRoomInts::~HonestyRoomInts() {
}

void HonestyRoomInts::roomHelp() {
  std::cout << "Try interacting with the room" << std::endl;
}

void HonestyRoomInts::roomInteract() {
  if (action->getActionResult("interact")[0] == 'a') {
    std::cout << "You can choose between two options:" << std::endl
              << "Press 1: I accidently broke it. I'm sorry" << std::endl
              << "Press 2: I didn't break it."
              << " It was already like this when I came here" << std::endl;

    int input;
    std:: cin >> input;
    std::cin.clear();
    std::cin.ignore(500, '\n');

    if (input == 1) {
      std::cout << "You tell the truth: I accidently broke it."
                << " I'm really sorry." << std::endl;
      std::cout << "Owner forgives you." << std::endl;
      std::cout << "Type 'stop' twice so that you can back to menu."
                << " And move to the next game!" << std::endl << std::endl;
      room->getCharacter("Player")->getStats()->modifyStat("humanity", -5);
      room->getCharacter("Player")->getStats()->modifyStat("morality", +5);
      room->getCharacter("Player")->getStats()->modifyStat("puzzles", +1);
      action->setActionResult("interact", "b");
    } else {
      std::cout << "You lie: I didn't break it."
                << " It was already like this when I came here."
                << std::endl;
      std::cout << "Type 'stop' twice so that you can back to menu."
                << " And move to the next game!." << std::endl
                << std::endl;
      room->getCharacter("Player")->getStats()->modifyStat("humanity", +5);
      room->getCharacter("Player")->getStats()->modifyStat("morality", -5);
      room->getCharacter("Player")->getStats()->modifyStat("puzzles", +1);
      action->setActionResult("interact", "b");
    }
  } else {
  std::cout << "There is nothing else to interact with" << std::endl;
  }
}

// Name purposely misspelled.
DrAvikInteractions::DrAvikInteractions() {
  action->removeActionResult("speak");
  action->addActionResult("speak", "a");
}

DrAvikInteractions::~DrAvikInteractions() {}

void DrAvikInteractions::characterSpeak() {
  Input input;
  if (room->getCharacter("Player")->getStat("puzzles") < 6) {
    if (action->getActionResult("speak")[0] == 'a') {
      std::cout << "Hello!!! and welcome to Life-2.0's Logout-Beta!!!"
                << std::endl;
      std::cout << std::endl
                << "\n   I'm Dr.Avik the AI responsible for evaluating";
      std::cout << std::endl
                << "\n   your performance during this Beta." << std::endl;
      std::cout << std::endl
                << "If it is your first time here we generally"
                << " recommend you start with the \"virtue\" rooms.\n"
                // Hanna's rooms
                << "   The \"puppy\" room is a"
                << " good follow up.\n\n"
                << "The \"jester\" room is...a work in progress\n";
      std::cout << "The AI \"Jester\" is struggling a bit with their puzzles."
                << " Maybe you can help them out?";
      std::cout << "\n\n\nFeel free to ask me"
                << " if you have any additional questions\n\n";

      std::cout << "\n*Also don't kiss the puppy....\n\n";

    action->setActionResult("speak", "b");
    } else {
        std::cout << "Hi! What can I help you with? \n" << std::endl;

        while (true) {
          std::cout << "================================" << std::endl;
          std::cout << "Can you tell me about the CATCHA's? (game)"
                    << std::endl;
          std::cout << "Can you remind me about the other rooms? (rooms)"
                    << std::endl;
          std::cout << "What should I do here? (help)"<< std::endl;
          std::cout << "Tell me about yourself... (you)"<< std::endl;
          std::cout << "How much longer? (remaining)" << std::endl;
          std::cout << "Nevermind. (stop)" << std::endl;
          //std::cout << "5. Interactions" << std::endl;
          //std::cout << "6. Help" << std::endl;
          std::cout << "================================" << std::endl;

          std::string choice = "";
          choice = input.getInput();
          std::cout << std::endl;
          if (choice == "game") {
            std::cout << "\n\n   The CAPTCHA's are here to test out how human"
              << "\n we think you are. Based on that we will output"
              << "\n your results at the end and then see if our"
              << "\n conclusions are valid based on your player type state."
              << "\n That is to say I don't actually know if you are a human"
              << "\n or an AI so forgive us if we are incorrect at the end as"
              << "\n this program is still a work in progress.\n\n";
          } else if (choice == "rooms") {
              std::cout << "\n\nThere are 4 sets of rooms to"
              << " the north, east, south ,and west."
              << "\n\n The rooms to the \"east\" are generally"
              << " where we recommend that new players"
              << "\n start out as it includes a set of directives"
              << " to make things easier"
              << "\n for human players and introduces AI's to the outputs."
              << "\n\nThe \"north\" and \"south\" roomsh are good"
              << " follow ups and a lot of fun."
              << "\n\n The \"west\" room is a bit of a work"
              << " in progress but we would"
              << " appreciate any help you can provide us with.\n\n";
          } else if (choice == "remaining") {
              std::cout << "\n\n It looks like you have"
              << room->getCharacter("Player")->getStat("puzzles") - 6
              << " puzzles left." << std::endl;
              std::cout << "\n Try going back to rooms you have previously"
              << "\ncompleted and interacting with the NPC's again\n\n";
          } else if (choice == "john") {
            if (action->getActionResult("speak").length() < 4) {
              std::cout << "\n Please don't call me that....\n";

              std::string temp = action->getActionResult("speak");
              temp += 'a';
              action->setActionResult("speak", temp);

            } else {
              std::cout << "\n   Clearly you cannot follow"
                        << " simple instructions."
                        << "\n   As such I am removing you from the Beta.\n"
                        << std::endl;
              room->getCharacter("Player")->getStats()->setStat("health", 0);
              return;
            }
          } else if (choice == "help") {
            std::cout << "\n\n AI or human your goal here is"
            << " to provide us with data so we can"
            << "\n distinguish between the two."
            << " We have defined a morality and humanity"
            << "\n index as measures of"
            << " if you are human or not and you will help"
            << "\n us test the validity of our metrics"
            << " based on your player type (AI or human)"
            << "\n which is not revealed to us until the end of the test.\n\n";
          } else if (choice == "you") {
            std::cout << "\n\n I am an artificial intelligence"
            << " named after a professor"
            << "\n   one of my programmers had several years ago."
            << " I am essentially the administrator of these CAPTCHA's"
            << " and keep the other AI's in line"
            << "\n     while evaluating the data we receive"
            << " from those that participate"
            << "\n     in the Beta. I add, remove,"
            << " and modify CAPTCHA's based on their "
            << "\n     performance, and occasionally introduce"
            << " other AI's to build new tests"
            << "\n     as needed.\n\n";
          } else if (choice == "stop") {
            break;
          } else {
            std::cout << "Invalid Action" << std::endl;
          }
        }
      }
    } else { // end game
      std::cout << "Congratulations you have completed the Beta!!!!"
                << std::endl;
      if (room->getCharacter("Player")->getStat("humanity") >= 0)
      { std::cout << "\n\nBased on our results you definitely were a human"
        << "\nwhich means we were correct!!!" << std::endl;
      } else {
        std::cout << "\n\nBased on our results you were a computer!!!"
        << "\n Oh....that's not correct. There is either something"
        << " very wrong with our metrics or, well, you're a little different..."
        << std::endl;
      }
      if (room->getCharacter("Player")->getStat("morality") >= 0) {
        std::cout << "\n\nWell despite that you are certainly a moral"
        << "\nperson glad to know that there is still good in the world"
        << std::endl;
      } else {
        std::cout << "\n\nWell despite that you are certainly an immoral"
        << "\nperson you might want to think about how you can be better"
        << "\nto those around you."
        << std::endl;
      }
      std::cout << "\n\n THANKS FOR PLAYING!!!!!!!"
                << std::endl;
      room->getCharacter("Player")->getStats()->setStat("health", 0);
}
}

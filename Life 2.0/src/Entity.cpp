#include "Entity.h"
#include "Exceptions.h"
#include "Input.h"
#include <map>
#include <string>
#include <list>


Entity::Entity() {
  inventory = new Inventory;
  description = "It's enigmatic...";
}

Entity::Entity(Inventory* inv, std::string desc) {
  inventory = inv;
  description = desc;
}

Entity::~Entity() {
if (inventory) delete inventory;
}

std::string Entity::getDescription() {
  return description;
}

void Entity::setDescription(std::string newDesc) {
  description = newDesc;
}

void Entity::displayDescription() {
  std::cout << description << std::endl;
}

Inventory* Entity::getInventory() {
  return inventory;
}

void Entity::setInventory(Inventory* inv) {
  if (inventory) delete inventory;
  inventory = inv;
}

bool Entity::checkItem(std::string s) {
  return getInventory()->findItem(s);
}

Room::Room() {
  roomInts = new RoomInteractions();
  roomInts->setRoom(this);
}

Room::~Room() {
  if (roomInts != nullptr) delete roomInts;
  std::list<Character*>::iterator it;
  for (it = charactersPresent.begin(); it != charactersPresent.end(); ++it) {
    if (*it) delete *it;
  }
}

RoomInteractions* Room::getRoomActionList() {
  return roomInts;
}

std::map<std::string, Room*> Room::getAdjacentRooms() {
  return adjacentRooms;
}

Room* Room::findAdjacentRoom(std::string direction) {
  return adjacentRooms[direction];
}

void Room::addAdjacentRoom(std::string direction, Room* room) {
  adjacentRooms[direction] = room;
}

void Room::removeAdjacentRoom(std::string direction) {
  adjacentRooms.erase(direction);
}

void Room::addCharacter(Character* c) {
  charactersPresent.push_front(c);
}

void Room::removeCharacter(Character* c) {
  charactersPresent.remove(c);
}


bool Room::findCharacter(Character* c) {
  for (std::list<Character*>::iterator it = charactersPresent.begin();
    it != charactersPresent.end(); ++it) {
      if (*it == c) {
        return true;
      }
    }
    return false;
}

void Room::setActionList(RoomInteractions* roomInteraction) {
  if (roomInts) delete roomInts; // This could be dangerous.....
  roomInts = roomInteraction;
  roomInts->setRoom(this);
}


/**********************************************************
MAKE TESTS FOR THIS FUNCTION
**********************************************************/
bool Room::findCharacterName(std::string name) {
  for (std::list<Character*>::iterator it = charactersPresent.begin();
    it != charactersPresent.end(); ++it) {
      if ((*it)->getName() == name) {
        return true;
      }
    }
    return false;
}

Character* Room::getCharacter(std::string name) {
  for (std::list<Character*>::iterator it = charactersPresent.begin();
    it != charactersPresent.end(); ++it) {
      if ((*it)->getName() == name) {
        return (*it);
      }
    }
  throw invalid_parameter_error("invalid_parameter_error");
}

std::list<Character*> Room::getRoomEntities() { // this also breaks
  //if (charactersPresent.empty())
    //throw invalid_parameter_error("invalid_parameter_error");
  return charactersPresent;
}

Character::Character() {
  name = "John Doe";
  stats = new Stats;
  charInts = new CharacterInteractions;
  charInts->setCharacter(this);
  charInts->setRoom(getRoom());
}

Character::Character(std::string n) {
  name = n;
  stats = new Stats;
  charInts = new CharacterInteractions;
  charInts->setCharacter(this);
  charInts->setRoom(getRoom());
}

Character::~Character() {
  if (stats) delete stats;
  if (charInts) delete charInts;
}

CharacterInteractions* Character::getCharacterActionList() {
  return charInts;
}

void Character::setActionList(CharacterInteractions* charInteraction) {
  if (charInts) delete charInts;
  charInts = charInteraction;
  charInts->setRoom(this->getRoom());
}

std::string Character::getName() {
  return name;
}

Stats* Character::getStats() {
  return stats;
}

int Character::getStat(std::string stat) {
  return stats->getStat(stat);
}

Room* Character::getRoom() {
  return room;
}

bool Character::checkForItem(std::string itemName, Item* item) {
  if (item  == inventory->getItem(itemName)) {
    return true;
  } else {
    return false;
  }
}

// NOW ADDS CHARACTER TO ROOM AS WELL
void Character::setRoom(Room* r) {
  room = r;
}

bool Character::checkMoveValid(std::string direction) {
  if (room->getAdjacentRooms()[direction] == NULL) {
    return false;
  } else {
    return true;
  }    //  case 5:
        //displayMap();
        //break;

    //  case 5:
    //    playerInteract();
      //  break;
}

Player::Player() {
name = "Player";
getStats()->addStat("puzzles", 0);
}
Player::~Player() {
//
}

void Player::playerInteract() { // THIS HAS A SEGMENTATION FAULT
  bool interactTrue = false;

  Input input;

  std::string choice = " ";

  while (interactTrue == false) {
    if (getStat("health") <= 0) // can change to show GAME OVER screen.
      return;
  // self interaction is covered by basic menu can add later if
  // someone needs it.
  std::cout << "Interactables: ";
  std::cout << "(room";

  // TEMP FIX - Make sure to delete the characters at end of function.
  // Skip to room if no one present
  std::list<Character*> tempList = room->getRoomEntities();

  if (!(room->getRoomEntities().empty())) {
    for (std::list<Character*>::iterator it=tempList.begin();
      (it != tempList.end()); ++it) {
        if ((*it)->getName() != "Player")
        std::cout << ", " << (*it)->getName();
      }
  }
  std::cout << ")" << " \"stop\" to end." << std::endl;

  std::cout << "What would you like to interact with?: ";

  choice = input.getInput();
  if (choice == "room") {
    playerInteractRoomWrapper();
  } else if (room->findCharacterName(choice)) {
    playerInteractCharacterWrapper(choice);
  } else if (choice == "stop") {
    break;
  } else {
  }
}
}

void Player::playerHelp() {
  getRoom()->getRoomActionList()->roomHelp();
  //std::cout << "welp that sucks" << std::endl;
}

void Player::playerMove(std::string direction) {
  system("clear");
  if (checkMoveValid(direction)) {
    getRoom()->removeCharacter(this); // removes player from old room;
    setRoom(room->findAdjacentRoom(direction));
    getRoom()->addCharacter(this);  // adds character to new room
    std::cout << room->getDescription() << std::endl;
  } else {
    std::cout << "You can't go that way" << std::endl;
  }
  playerChoice();
}

// Class of pointer to methods would be
void Player::playerInteractRoomWrapper() {
  // have this be a wrapper function instead.
  Input input;
  std::string interaction;
  // or playerInteractRoom() call;
  while (true) {
    if (getStat("health") <= 0) // can change to show GAME OVER screen.
      return;
    std::cout << "Actions available:";

    // Outputs a list of available actions
    // based on the actionresult list
    std::list<std::string> temp = room->getRoomActionList()
    ->getActionResult()->getActionResults();
    for (std::list<std::string>::iterator it = temp.begin();
      it != temp.end(); ++it) {
        // provides simple help function that shows
        // all available actions in the action result list.
        std::cout << " " << (*it) << ",";
      }
      std::cout << " stop (to end)" << std::endl;

    std::cout << "What would you like to do?: ";
    interaction = input.getInput();
    std::cout << std::endl;
    if (interaction == "look") {
      room->getRoomActionList()->roomLook();
    } else if (interaction == "interact") {
      room->getRoomActionList()->roomInteract();
    } else if (interaction == "examine") {
      room->getRoomActionList()->roomExamine();
    } else if (interaction == "stop") {
      break;
    } else {
      std::cout << "Invalid Action" << std::endl;
      std::cout << "stop" << std::endl;
    }
  }
}

void Player::playerInteractCharacterWrapper(std::string charName) {
  Input input;
  std::string interaction = "";
  // or playerInteractCharacer() call;
  while (true) {
    if (getStat("health") <= 0)
      return;
    std::cout << "Actions available:";
    // Outputs a list of available actions based on the actionresult list
    std::list<std::string> temp = room->getCharacter(charName)
    ->getCharacterActionList()->getActionResult()->getActionResults();
    for (std::list<std::string>::iterator it = temp.begin();
      it != temp.end(); ++it) {
      // provides simple help function that shows
      // all available actions in the action result list.
        std::cout << " " << (*it) << ",";
      }
      std::cout << " stop (to end)" << std::endl;

    std::cout << "What would you like to do?: ";
    interaction = input.getInput();
    std::cout << std::endl;
    if (interaction == "speak") {
      room->getCharacter(charName)->getCharacterActionList()->characterSpeak();
    } else if (interaction == "kiss") {
      room->getCharacter(charName)->getCharacterActionList()->characterKiss();
    } else if (interaction == "touch") {
      room->getCharacter(charName)->getCharacterActionList()->characterKiss();
    } else if (interaction == "stop") {
      break;
    } else {
      std::cout << "Invalid Action" << std::endl;
    }
  }
}

void Player::playerUseItem(std::string s) {
  getCharacterActionList()->setRoom(getRoom());
  getCharacterActionList()->characterUseItem(s);
}

void Player::playerPickUpItem(std::string s) {
  if (getRoom()->getInventory()->findItem(s)) {
    getInventory()->addItem(getRoom()->getInventory()->getItem(s)
    ->getName(), getRoom()->getInventory()->getItem(s));
    getRoom()->getInventory()->removeItem(s);
  } else {
    std::cout << "That item isn't here..." << std::endl;
  }

  // below allows room specific item behaviours
  //room->getRoomActionList()->roomPickup();
}

void Player::playerDropItem(std::string s) {
  if (getInventory()->findItem(s)) {
    getRoom()->getInventory()->addItem(getInventory()
    ->getItem(s)->getName(), getInventory()->getItem(s));
    getInventory()->removeItem(s);
  } else {
    std::cout << "You don't have that item..." << std::endl;
  }
}

void Player::playerChoice() {
  bool choiceLoop = true;
  int choice = 0;
  Room* room = getRoom();
  Inventory* inv = getInventory();
  Input in;
  while (choiceLoop == true) {
    if (getStat("health") <= 0) {
      break;
    } // can change to show GAME OVER screen. by breaking loop
    if (getStat("puzzles") > 5) {
      std::cout << "\n\nYou have completed enough of the";
      std::cout << "\n CAPTCHAS to finish the Game please";
      std::cout << "\n talk to Dr.Avik in the main room";
      std::cout << "\n when you are ready to end the game\n\n";
    }
    std::cout << "================================" << std::endl;
    std::cout << "Type in a number:" << std::endl;
    std::cout << "1. Move rooms" << std::endl;
    std::cout << "2. Get Room Description" << std::endl;
    std::cout << "3. Check your inventory" << std::endl;
    std::cout << "4. Use Item" << std::endl;
    std::cout << "5. Interactions" << std::endl;
    std::cout << "6. Help" << std::endl;
    std::cout << "================================" << std::endl;

    std::cin >> choice;
    std::cin.clear();
    std::cin.ignore(500, '\n');

    switch (choice) {
      case 1: {
        if (!(getRoom()->getAdjacentRooms().empty())) {
          std::string roomChoice;
          std::cout << "================================" << std::endl;
          std::cout << "Type in the direction of the room"
                    << " you would like to enter:" << std::endl;
          std::cout << "(";
          std::map<std::string, Room*> temp = getRoom()->getAdjacentRooms();
          for (std::map<std::string, Room*>::iterator it=temp.begin();
            it != temp.end(); ++it)
            std::cout << " " << it->first;
          std::cout << " )" << std::endl;
          std::cout << "================================" << std::endl;
          roomChoice = in.getInput();
          playerMove(roomChoice); // recursive....
      } else {
        std::cout << "There are no adjacent rooms." << std::endl;
      }
        break;
      }
      case 2:
        system("clear");
        std::cout << room->getDescription() << std::endl;
        break;
      case 3:
        system("clear");
        inv->showInventory();
        break;
      case 4: {
        std::string itemChoice;
        std::cout << "================================" << std::endl;
        std::cout << "Type in the item you would like to use" << std::endl;
        std::cout << "================================" << std::endl;
        inv->showInventory();
        itemChoice = in.getInput();
        playerUseItem(itemChoice);
        break;
      }
      case 5:
        playerInteract();
        break;
      case 6:
        playerHelp();
        break;
      default:
        std::cout << "Please pick a number from 1 to 6" << std::endl;
        choice = 0;
    }
  }
  if (getStat("health") <= 0) {
  std::cout << "GAME OVER" << std::endl;}
}

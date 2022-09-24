#ifndef INTERACTIONS_H_INCLUDED
#define INTERACTIONS_H_INCLUDED

#include <map>
#include <string>
#include <list>
#include "Entity.h"
#include "ActionResultList.h"
#include "Item.h"
#include "Game.h"
#include <iostream>

class Entity;
class Character;
class Room;

/**
* Acsts as a set of rules for individaul actions
* and changes entities in response to specific actions
*/
class Interactions {
 public:
  /**
  * Default Constructor.
  */
  Interactions();

  /**
  * Destructor
  */
  virtual ~Interactions();


  /**
  * General getter function that returns a pointer to the Interactions
  * action result list.
  **/
  virtual ActionResultList* getActionResult();

  /**
  * General setter function that sets a pointer to the Interactions
  * action result list.
  **/
  virtual void setActionResult(ActionResultList* alist);

  /**
  * returns the room the interaction is linked to
  * @return a pointer to Room object
  */
  virtual Room* getRoom();

  /**
  * sets the room the interaction is linked to
  * @param a pionter to Room object
  */
  virtual void setRoom(Room*);

 protected:
  ActionResultList* action; //change this to correct type.
  std::list<std::string> interactableItems;
  Room* room;
};

/**
* Initiates interactions and consequences with another character
* in reponse to player input
*/
class CharacterInteractions : public Interactions {
 public:
  /**
  * Constructor.
  */
  CharacterInteractions();

  /**
  * Destructor
  */
  virtual ~CharacterInteractions();

  /**
  * returns the character the interaction is linked to
  * @return a pointer to Character object
  */
  virtual Character* getCharacter();

  /**
  * sets a character to the interaction
  * @param a pionter to Character object
  */
  virtual void setCharacter(Character*);

  /**
  * speak to a character may trigger additional actions
  */
  virtual void characterSpeak();

  virtual void characterTouch(); // obsolete?

  /**
  * attempt to use an item may trigger additional actions
  */
  virtual void characterUseItem(std::string);

  /**
  * attempt to attack a character may trigger additional actions
  */
  virtual void characterInteract();

  /**
  * attempt to kiss another character may trigger additional actions
  */
  virtual void characterKiss();

  /**
  * attempt to persuade another character may trigger additional actions
  */
  // void characterPersuade();

 protected:
  Character* character;
};

class RoomInteractions : public Interactions {
 public://
  /**
  * Constructor.
  */
  RoomInteractions();

  /**
  * Destructor
  */
  virtual ~RoomInteractions();

  /**
  * triggers the use function for that specific room
  * defaults to output of room action list result key "use"
  **/
  virtual void roomUse();

  /**
  * Outputs a hint for the room you are in.
  **/
  virtual void roomHelp();


  /**
  * Get a room's description.
  */
  virtual void roomLook();


  /**
  * triggers the touch function for that specific room
  * defaults to output of room action list result key "touch"
  **/
  virtual void roomTouch();

  /**
  * triggers the interact function for that specific room
  * defaults to output of room action list result key "interact"
  **/
  virtual void roomInteract();

  /**
  * triggers the look function for that specific room
  * defaults to output of room action list result key "look"
  **/
  virtual void roomExamine();
};

class JesterInteractions : public CharacterInteractions {
 public:
  /**
  * Constructor.
  */
  JesterInteractions();

  /**
  * Destructor
  */
  virtual ~JesterInteractions();

  /**
  * triggers a very specific and verbose set of dialogue options
  * triggered by the use of "speak".
  **/
  virtual void characterSpeak();
};

class DrAvikInteractions : public CharacterInteractions {
 public:
  /**
  * Constructor.
  */
  DrAvikInteractions();

  /**
  * Destructor
  */
  virtual ~DrAvikInteractions();

  /**
  * triggers a set of helpful background information from a  set of dialogue options
  * triggered by the use of "speak".
  **/
  virtual void characterSpeak();
};

class VaguenessRoomInts : public RoomInteractions {
 public://
  /**
  * Constructor.
  */
  VaguenessRoomInts();

  /**
  * Destructor
  */
  virtual ~VaguenessRoomInts();


  /**
  * outputs a set of room specific options by using the "examine key"
  **/
  void roomExamine();

  /**
  * outputs a set of room specific dialogue to help the user in the
  * specific room they are in triggered from the main menue (i.e. player choice.)
  **/
  void roomHelp();

  /**
  * outputs a set of room specific options by using the "examine key"
  * in this case the player is able to add up to 10 grains of rice Before
  * losing the game.
  **/
  void roomInteract();
};

class DecisionTheoryRoomInts : public RoomInteractions {
 public://
  /**
  * Constructor.
  */
  DecisionTheoryRoomInts();

  /**
  * Destructor
  */
  virtual ~DecisionTheoryRoomInts();

  /**
  * Modified room look for the Decision theory room which opens up a new menu.
  **/
  void roomLook();

  /**
  * outputs a set of room specific options by using the "examine key"
  * triggers a dialogue window that the plater can explore a set of murals.
  **/
  void roomExamine();
};

class DogEntranceRoomInts : public RoomInteractions {
 public://
  /**
  * Constructor.
  */
  DogEntranceRoomInts(Room* r);

  /**
  * Destructor
  */
  virtual ~DogEntranceRoomInts();

  /**
  * displays room specific help for the DogKeyRooms
  **/
  void roomHelp();
};

class DogKeyRoomInts : public RoomInteractions {
 public://
  /**
  * Constructor.
  */
  DogKeyRoomInts(Room* r);

  /**
  * Destructor
  */
  virtual ~DogKeyRoomInts();

  /**
  * displays room specific help for the DogKeyRooms
  **/
  void roomHelp();

  /**
  * Interaction to use the safe and enter a code. Will give the character a key
  * if code is correct.
  **/
  void roomInteract();

  /**
  * Examine the safe and get details.
  */
  void roomExamine();

  /**
  * Interaction to inspect the safe in the room.
  */
  void roomLook();
};

class DogLockedDoorRoomInts : public RoomInteractions {
 public://
  /**
  * Constructor.
  */
  DogLockedDoorRoomInts(Room* r);

  /**
  * Destructor
  */
  virtual ~DogLockedDoorRoomInts();

  /**
  * displays room specific help for the DogLockedDoorRoom
  **/
  void roomHelp();

  /**
  * Interaction to unlock the door. If player has the key, they can unlock and
  * go to the next room.
  **/
  void characterUseItem(Item* key, Room* r);
};

class DogExitRoomInts : public RoomInteractions {
 public://
  /**
  * Constructor.
  */
  DogExitRoomInts(Room* r);

  /**
  * Destructor
  */
  virtual ~DogExitRoomInts();


  /**
  * displays room specific help for the DogExitRoom
  **/
  void roomHelp();

  /**
  * Interaction to shoot gun. Will take in a boolean which will be shooting
  * the dog (true) or themself (false).
  **/
  void roomInteract();
};

class PuppyInteractions : public CharacterInteractions {
 public:
  PuppyInteractions(Character* c);

  virtual ~PuppyInteractions();

  void characterSpeak();

  void characterTouch();

  void characterKiss();
};

class KindessRoomInts : public RoomInteractions {
 public:
  /**
  * Constructor.
  */
  KindessRoomInts();

  /**
  * Destructor
  */
  virtual ~KindessRoomInts();

  /**
  * displays room specific help for the KindessRoom
  **/
  void roomHelp();

  /**
  * Interaction in Kindess Room. The player can choose to help the character or not.
  **/
  void roomInteract();
};



class RightOrWrongRoomInts : public RoomInteractions {
 public://
  /**
  * Constructor.
  */
  RightOrWrongRoomInts();

  /**
  * Destructor
  */
  virtual ~RightOrWrongRoomInts();

  /**
  * displays room specific help for the RightOrWrongRoom
  **/
  void roomHelp();

  /**
  * Interaction in Right or Wrong Room. The player can choose between two options.
  **/
  void roomInteract();
};

class PatienceRoomInts : public RoomInteractions {
 public://
  /**
  * Constructor.
  */
  PatienceRoomInts();

  /**
  * Destructor
  */
  virtual ~PatienceRoomInts();

  /**
  * displays room specific help for the PatienceRoom
  **/
  void roomHelp();
  /**
  * Interaction in Patience Room. The player can choose to eat or not.
  **/
  void roomInteract();
};

class HonestyRoomInts : public RoomInteractions {
 public://
  /**
  * Constructor.
  */
  HonestyRoomInts();

  /**
  * Destructor
  */
  virtual ~HonestyRoomInts();

  /**
  * displays room specific help for the HonestyRoom
  **/
  void roomHelp();

  /**
  * Interaction in Honesty Room. The player can choose to tell the truth or lie.
  **/
  void roomInteract();
};

#endif

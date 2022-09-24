/**
* @author Kurt Clarke <@kurt.clarke> (entity Superclass)
* @author Ayobami (character & player)
* @author Albert (Room)
* @date 2021-11
*/

#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <string>
#include <map>
#include <iostream>
#include <list>
#include "Stats.h"
#include "Inventory.h"
#include "Interactions.h"


class Interactions;
class CharacterInteractions;
class RoomInteractions;

class Entity {
 public:
  /**
  Default entity constructor
  **/
  Entity();
  /**
  Entity class constructor - <virtual>
  Creates the template for a basic entity
  @Param Inventory pointer inv points to a new inventory if not specified.
  @Param Actionlist pointer al points to a new Actionlise if not specified
  @Param string desc provides a description of the entity
  **/
  Entity(Inventory*, std::string);

  /**
  Class destructor.
  **/
  virtual ~Entity();

  /**
  returns an entities description.
  @return returns an entities description.
  **/
  std::string getDescription();

  /**
  sets an entities description based on a string input.
  @param string to be used for entities description.
  **/
  void setDescription(std::string);

  /**
  Displays an entities description to the terminal.
  **/
  void displayDescription();

  /**
  returns a pointer to an entities action list.
  @return a pointer to an entities action list.
  **/
  Interactions* getActionList();

  /**
  sets an entities action list.
  @param ActionList* sets an entities action list to ActionList*
  **/
  void setActionList(Interactions*); // this should be removed.

  /**
  returns a pointer to an entities Inventory
  @return s a pointer to an entities Inventory
  **/
  Inventory* getInventory();

  /**
  sets an entities inventory
  @Param Inventory* sets an entities inventory to Inventory*
  **/
  void setInventory(Inventory*);

  /**
  checks if an entity has an item.
  @param Item* a pointer to the item of interest.
  @return true if item is in inventory, false if not.
  **/
  bool checkItem(std::string);

 protected:
  Inventory* inventory;
  //Interactions* actions; // DELEGATED TO SUB CLASSES
  std::string description;
};

class Character;

class Room : public Entity {
 public:
  /**
  * Constructor.
  */
  Room();

  /**
  * Destructor
  */
  virtual ~Room();

  /**
  * Returns a list of adjacent rooms
  * @return a list of rooms in a map.
  */

  RoomInteractions* getRoomActionList();

  /**
  * Returns a list of adjacent rooms
  * @return a list of rooms in a map.
  */
  std::map<std::string, Room*> getAdjacentRooms();

  /**
  * Returns the room from the corresponding direction.
  * @return the room in the corresponding direction.
  */
  Room* findAdjacentRoom(std::string direction);

  /**
  * Adds a new room pointer ot the map of rooms.
  * @param direction, the direction of the adjacent room.
  * @param room, the room being added.
  */
  void addAdjacentRoom(std::string direction, Room* room);

  /**
  * Removes a room pointer from the map of rooms.
  * @param direction, the direction of the adjacent room to
  * be removed.
  */
  void removeAdjacentRoom(std::string direction);

  /**
  * Adds a character to the list of characters in a room.
  * @param c, the character being added to the room.
  */
  void addCharacter(Character* c);

  /**
  * Removes a character from the list of characters in a room.
  * @param c, the character being removed from the room.
  */
  void removeCharacter(Character* c);

  /**
  * Returns true if character is present in the room, false otherwise.
  * @param c, the character pointer being searched for.
  * @return true if character is found, false otherwise.
  */
  bool findCharacter(Character* c);

  /**
  * Returns true if character is present in the room, false otherwise.
  * @param c, the character name being searched for.
  * @return true if character is found, false otherwise.
  */
  bool findCharacterName(std::string name);

  /**
  returns a character pointer using a name
  **/
  Character* getCharacter(std::string name);


  /**
  * Gets the list of all entities in a room.
  * @return the list of entities.
  */
  std::list<Character*> getRoomEntities();

  /**
  * Sets the rooms interaction list to the @param roomInteraction.
  * @param roomInteraction, room interaction pointer to replace.
  *     the original roomInteraction Pointer.
  */
  void setActionList(RoomInteractions* roomInteraction);

 protected:
  RoomInteractions* roomInts; //jenky fix.
  std::map<std::string, Room*> adjacentRooms;
  std::list<Character*> charactersPresent;
};

class Character : public Entity {
 public:
  Character();
  /**
  * Constructor.
  */
  Character(std::string name);

  /**
  * Destructor
  */
  ~Character();

  /**
  * Returns character's name
  * @Param the name of the character
  */
  CharacterInteractions* getCharacterActionList();

  /**
  * Sets the characters interaction list to the @param charInteraction.
  * @param charInteraction, character interaction pointer to replace.
  *     the original charInteraction Pointer.
  */
  void setActionList(CharacterInteractions* charInteraction);

  /**
  * Returns character's name
  * @return the name of the character
  */
  std::string getName();

  /**
  * Returns a list of the character's stats
  * @return a map of character's stats
  */
  Stats* getStats();

  /**
  * Returns the value for the specified stat passed in the parameter.
  * @param stat, the specific stat to be retrieved.
  * @return the value of the stat specified.
  */
  int getStat(std::string stat);

  /**
  * Returns a pointer to the room that a character is currently in.
  * @return the room the character is currently in.
  */
  Room* getRoom();
  /**
  * Adds item to their inventory
  @param item, item is added
  */
  int addItem();

  /**
  * Checks if the item is in their inventory
  * @param item, item to be checked.
  * @return true if item is in inventory, false otherwise.
  */
  bool checkForItem(std::string itemName, Item* item);

  /**
  * Sets the room the character is in.
  * @param the room to set the character in.
  */
  void setRoom(Room* r);

  /**
  * Checks if there is a room to the @param direction
  * @param the direction key for the the room the
  *     character is in's room adjacency list.
  */
  bool checkMoveValid(std::string direction);

 protected:
  CharacterInteractions* charInts; //jenky fix.
  std::string name;
  Stats* stats;
  Room* room;
};

class Player : public Character {
 public:
  /**
  * Default constructor, Constructs a player class.
  */
  Player();

  /**
  * Destructor
  */
  virtual ~Player();

  /**
  * Moves the player to a different room depending
  * on their input and which room they are currently in.
  */
  void playerMove();

  /**
  * Asks the player what they would like to interact
  * with and what interaction they would like to perform
  * based on the room they are in and the other
  * characters also in that room.
  */
  void playerInteract();

  /**
  * Asks the player what item they would like to use
  * and on what. Interaction will then check if this
  * is a valid interaction and implement any changes
  * that happen because of the interaction.
  */
  void playerUseItem(std::string item);

  /**
  * Calls player help. This is dependent on the room
  * the player is in and the other characters and items
  * in that room.
  */
  void playerHelp();


  /**
  * Calls character move from super class characer. using player interface
  * @param direction; the direction the player would like to move.
  */
  void playerMove(std::string direction);

  /**
  * A general function for the players interface for interacting with rooms
  * provides a variety of options based on the rooms action resuslts list.
  **/
  void playerInteractRoomWrapper();

  void playerInteractRoom(std::string);


  /**
  * A general function for the players interface for interacting with characters
  * provides a variety of options based on the characters action resuslts list.
  **/
  void playerInteractCharacterWrapper(std::string charName);

  void playerInteractCharacter(std::string, Character*);

  void playerPickUpItem(std::string); // obsolete?

  void playerDropItem(std::string);// obsolete?

  /**
  * A general function for the players interface it acts as a general main menu
  * from which the player can move, check inventory, use an item, get help, get
  * a rooms description or interact with something in the room.
  **/
  void playerChoice();

 private:
};

#endif

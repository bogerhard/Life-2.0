#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <vector>
#include "Entity.h"

class Room;
class Character;

/**
* Sets a general class for the implementation of the game and the “meta” functions for the entire game. 
*/
class Game {
 public:
  /**
  * Constructor.
  */
  Game();

  /**
  * Destructor
  */
  virtual ~Game();

  /**
  * initiates the beginning of the game.
  */
  void gameStart();
};

#endif

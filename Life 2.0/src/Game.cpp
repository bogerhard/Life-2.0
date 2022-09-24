#include "Game.h"
#include "Entity.h"
#include "Input.h"
#include "Interactions.h"
#include "Inventory.h"
#include "Item.h"
#include "Stats.h"


Game::Game() {}

Game::~Game() {}

void Game::gameStart() {
  Player * player = new Player();

  /**********************************************************************
  * Initialization of Main Room
  **********************************************************************/
  Room * mainRoom = new Room();

  Character * dravik = new Character("dravik");
  DrAvikInteractions * avikInts = new DrAvikInteractions();
  dravik->setActionList(avikInts);
  mainRoom->addCharacter(dravik);
  avikInts->setRoom(mainRoom);
  mainRoom->setDescription
  ("An largely empty room with a friendly looking gentleman in it.");

  /**********************************************************************
  * Initialization of Jester Rooms
  **********************************************************************/
  Room * jesterRoom = new Room();
  jesterRoom->getRoomActionList()->getActionResult()->
  setActionResult("examine", "The jester seems a little off....");
  Room * philosophyRoom = new Room();
  philosophyRoom->getRoomActionList()->getActionResult()
  ->setActionResult("examine", "There's not much to do much here");
  Room * vaguenessRoom = new Room();
  vaguenessRoom->getRoomActionList()->getActionResult()
  ->setActionResult("examine", "What makes a pile, what is a pile?...");
  Room * decisionTheoryRoom = new Room();
  vaguenessRoom->getRoomActionList()->getActionResult()
  ->setActionResult("examine", "Three murals. Probably check them out.");

  Character * jadedJester = new Character("jester");
  JesterInteractions * newJester = new JesterInteractions();
  jadedJester->setActionList(newJester);
  newJester->setRoom(jesterRoom);
  Character * wisefool = new Character("platus");

     wisefool->getCharacterActionList()->getActionResult()
     ->removeActionResult("speak");
     wisefool->getCharacterActionList()->getActionResult()
     ->addActionResult("speak",
     "\nNo, no, no!!! You know what I don't know why the Sun rises and sets,"
     " each answer only brings 10 fold more questions!!!"
     " I am happy not knowing just that!!! I don't need to not know any more.");

  Character * foolishScholar = new Character("aria");
     foolishScholar->getCharacterActionList()
     ->getActionResult()->removeActionResult("speak");
     foolishScholar->getCharacterActionList()
     ->getActionResult()->addActionResult("speak", "\nBut...but..."
     " what about all that came from answering that question?"
     " what of astrology? and physicics?"
     " and the nature of the Universe itself?");

  JesterInteractions* jesterInts = new JesterInteractions();
  VaguenessRoomInts * vagueRoomInts = new VaguenessRoomInts();
  DecisionTheoryRoomInts * decTheoryInts = new DecisionTheoryRoomInts();

  // Jester Room initialization
  jesterRoom->addCharacter(jadedJester);
  jesterRoom->setDescription("A jester sits alone."
  " His once bright colours now faded.");
  jesterRoom->addAdjacentRoom("north", vaguenessRoom);
  jesterRoom->addAdjacentRoom("east", decisionTheoryRoom);
  jesterRoom->addAdjacentRoom("south", philosophyRoom);

  // Philosophy room initialization;
  philosophyRoom->addAdjacentRoom("north", jesterRoom);
  philosophyRoom->setDescription("Two people are in a heated argument.");
  philosophyRoom->addCharacter(wisefool);
  philosophyRoom->addCharacter(foolishScholar);

  // Vagueness room initialization;
  vaguenessRoom->addAdjacentRoom("south", jesterRoom);
  vaguenessRoom->setDescription("A bag of rice sits on a table.");
  vaguenessRoom->setActionList(vagueRoomInts);

  // Descision theory room intitialization
  decisionTheoryRoom->addAdjacentRoom("west", jesterRoom);
  decisionTheoryRoom->setDescription("A set of bright murals cover the walls.");
  decisionTheoryRoom->setActionList(decTheoryInts);

  /**********************************************************************
  * Initialization of Puppy Rooms
  **********************************************************************/
  //Room setup
  Room* entranceRoom = new Room();
  Room* keyRoom = new Room();
  Room* lockedDoorRoom = new Room();
  //Room* exitRoom = new Room();

  //entranceRoom setup
  entranceRoom->setDescription("The entrance room. By the door entrance"
  " there is a box with 1 red dog toy in it."
  " In the south side of the room there is a door"
  " with a box with 3 green dog toys in it."
  " On the east side of the room there is another door.");
  entranceRoom->getRoomActionList()->getActionResult()
  ->setActionResult("examine", "Four doors, east is a good place to start");
  entranceRoom->addAdjacentRoom("main", mainRoom);
  entranceRoom->addAdjacentRoom("south", keyRoom);
  entranceRoom->addAdjacentRoom("east", lockedDoorRoom);
  entranceRoom->addAdjacentRoom("south", keyRoom);
  Inventory* erInv = entranceRoom->getInventory();

  DogEntranceRoomInts* derInts = new DogEntranceRoomInts(entranceRoom);
  entranceRoom->setActionList(derInts);
  RoomInteractions* derInteractions = entranceRoom->getRoomActionList();

  //keyRoom setup
  keyRoom->setDescription("The Key Room. On the south side of the room,"
  " there is a metal safe. On the west side of the room there is a box"
  " with 7 yellow dog toys in it."
  " On the east side of the room you hear a growling noise behind the wall...");
  keyRoom->addAdjacentRoom("north", entranceRoom);
  Inventory* krInv = keyRoom->getInventory();

  DogKeyRoomInts* dkrInts = new DogKeyRoomInts(keyRoom);
  keyRoom->setActionList(dkrInts);
  RoomInteractions* krInteractions = keyRoom->getRoomActionList();

  krInteractions->getActionResult()->removeActionResult("look");

  krInteractions->getActionResult()->addActionResult("look",
  "The safe seems to have a 4 digit code."
  " From left to right, each digit corresponds to a letter. R, G, B, and Y.");

  //lockedDoorRoom setup
  lockedDoorRoom->setDescription("The room with a locked door."
  " On the south side of the room, there is a locked door with a key hole."
  " On the north side of the room, there is a box with 3 blue dog toys in it.");
  lockedDoorRoom->addAdjacentRoom("west", entranceRoom);
  Inventory* ldrInv = lockedDoorRoom->getInventory();

  DogLockedDoorRoomInts* ldrInts = new DogLockedDoorRoomInts(lockedDoorRoom);
  lockedDoorRoom->setActionList(ldrInts);
  RoomInteractions* ldrInteractions = keyRoom->getRoomActionList();

  Room* kindessRoom = new Room();
  Room* rightOrWrongRoom = new Room();
  Room* honestyRoom = new Room();
  Room* patienceRoom = new Room();

  // kindessRoom setup
  kindessRoom->setDescription("When you enters a room"
  " and there is a old woman who lying unconsious on the floor."
  "\n Go to 5.Interactions and choose to interact with room."
  " Choose action 'interact'.");

  kindessRoom->addAdjacentRoom("east", rightOrWrongRoom);

  KindessRoomInts* kinInt = new KindessRoomInts();
  kindessRoom->setActionList(kinInt);

  // rightOrWrongRoom setup
  rightOrWrongRoom->setDescription("Some teenagers"
  " who are wearing school uniforms come and ask you for cigarette."
  "\n Go to 5.Interactions and choose to interact with room."
  " Choose action 'interact'.");

  rightOrWrongRoom->addAdjacentRoom("east", patienceRoom);

  RightOrWrongRoomInts* rowInt = new RightOrWrongRoomInts();
  rightOrWrongRoom->setActionList(rowInt);

  // patienceRoom setup
  patienceRoom->setDescription("There is a piece of cake on the table"
  " and the cake doesn't belong to you. You becomes hungry"
  " and you are thinking about whether to eat cake or not."
  "\n Go to 6.Interactions and choose to interact with room."
  " Choose action 'interact'.");
  patienceRoom->addAdjacentRoom("east", honestyRoom);

  PatienceRoomInts* patInt = new PatienceRoomInts();
  patienceRoom->setActionList(patInt);

  // honestyRoom setup
  honestyRoom->setDescription("There is a pottery on the floor and"
  " the player accidently broke it."
  " Soon, the owner of the pottery comes to you"
  " and asks what happened."
  "\n Go to 6.Interactions and choose to interact with room."
  " Choose action 'interact'.");

  HonestyRoomInts* honInt = new HonestyRoomInts();
  honestyRoom->setActionList(honInt);

  mainRoom->addAdjacentRoom("puppy", entranceRoom);
  mainRoom->addAdjacentRoom("virtue", kindessRoom);
  mainRoom->addAdjacentRoom("jester", jesterRoom);
  honestyRoom->addAdjacentRoom("main", mainRoom);
  jesterRoom->addAdjacentRoom("main", mainRoom);

  // Game Play
  player->setRoom(mainRoom);
  mainRoom->addCharacter(player);

  std::cout << "================================" << std::endl;
  std::cout << "WELCOME TO LIFE2.0 - LOGOUT"
            << std::endl;
  std::cout << "THE GOAL OF THE GAME IS TO COMPLETE A SET OF"
            << std::endl;
  std::cout << "CAPTCHAS TO PROVE THAT YOU ARE HUMAN"<< std::endl;
  std::cout << "TALK TO DR.AVIK OR HEAD IMMEDIATELY TO THE"<< std::endl;
  std::cout << "VIRTUE ROOMS TO GET MORE INFORMATION OR" << std::endl;
  std::cout << "START THE GAME'S TUTORIAL" << std::endl;
  std::cout << "================================" << std::endl;

  player->playerChoice();
}

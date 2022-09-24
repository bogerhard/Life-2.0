#ifndef ACTIONRESULTLIST_H_INCLUDE
#define ACTIONRESULTLIST_H_INCLUDED

#include <map>
#include <string>
#include <list>

/**
* A class for the organization and management of action results
*/
class ActionResultList {
 public:
 /**
  * Default Constructor.
  */
  ActionResultList();

  /**
   * Constructs a specific ActionResultList
   * @ param input for specifying default values.
   * 1 for character
   * 2 for room
   */
  ActionResultList(int type);

  /**
  * Destructor
  */
  ~ActionResultList();

  /**
  * adds an action key and action result to the list of action results
  * @param k is a string of the action key and r is a string of the action result
  */
  void addActionResult(std::string k, std::string r);

  /**
  * returns a list of actions which have results
  * @return a list of string that containing all the action result keys
  */
  std::list<std::string> getActionResults();

  /**
  * returns a specfic action result from a Key
  * @param a string input key.
  * @return a specific action result for a key.
  */
  std::string getActionResult(std::string s);

  void setActionResult(std::string key, std::string result);


  /**
  * remove an action key and its paired result value
  * @param a string of action
  */
  void removeActionResult(std::string);

  /**
  * displays and action result in response to an action key value
  * @param a string of the action key
  */
  void displayActionResults(std::string);


  /*
  * Checks if an action list is empty or not
  */
  bool isEmpty();

 private:
  std::map<std::string, std::string> actionResults;
};

#endif

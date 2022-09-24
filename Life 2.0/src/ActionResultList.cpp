#include "ActionResultList.h"
#include <iostream>
#include <string>
#include <utility>
#include <list>

ActionResultList::ActionResultList() {
}

ActionResultList::ActionResultList(int type) {
  if (type == 1) { // for character intitialization
    addActionResult("speak", "Hello....");
    addActionResult("touch", "\"Please don't\"");
    addActionResult("kiss", "Let's not");

  } else if (type == 2) { // for rooms initialization
      addActionResult("look", "nothing");
      addActionResult("interact", "With what?");
      addActionResult("examine", "nothing stands out.");
  } else {}
}

ActionResultList::~ActionResultList() {
}

void ActionResultList::addActionResult(std::string k, std::string r) {
  actionResults.insert(std::pair<std::string, std::string> (k, r));
}

// Make test for this...
std::list<std::string> ActionResultList::getActionResults() {
  std::list<std::string> l;
  for (auto iter : actionResults) {
    l.push_back(iter.first);
  }
    return l;
}

std::string ActionResultList::getActionResult(std::string s) {
  return actionResults[s];
  }

void ActionResultList::setActionResult(std::string key, std::string result) {
  actionResults[key] = result;
  }


void ActionResultList::removeActionResult(std::string k) {
  if (!actionResults.empty())
    actionResults.erase(k);
}


void ActionResultList::displayActionResults(std::string k) {
  std::cout << actionResults[k] << std::endl;
}

bool ActionResultList::isEmpty() {
  return actionResults.empty();
}

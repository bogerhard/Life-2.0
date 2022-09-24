/**
* @author
* @date
*/
#include <map>
#include <string>
#include "Stats.h"

Stats::Stats() {
  addStat("health", 100);
  addStat("humanity", 0);
  addStat("morality", 0);
  addStat("puzzles", 0);
}

void Stats::setStat(std::string s, int amount) {
  statistics[s] = amount;
}

Stats::~Stats() {
}

void Stats::modifyStat(std::string s, int amount) {
  statistics[s] += amount;
}

void Stats::addStat(std::string s, int amount) {
  statistics[s] = amount;
}

void Stats::removeStat(std::string s) {
  statistics.erase(s);
}

/*map<string, int>& Stats::getStats() {
  return statistics;
}*/

int Stats::getStat(std::string stat) {
  return statistics[stat];
}

bool Stats::isEmpty() {
  if (statistics.size() == 0) {
    return true;
  } else {
    return false;
  }
}

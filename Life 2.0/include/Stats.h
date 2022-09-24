/**
* @author Albert Arrieta <@albert.arrieta>
* @date 2021-11-11
*/

#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED

#include <map>
#include <string>


class Stats {
 public:
  /**
  Default constructor
  creates an empty map of stats.
  **/
  Stats();

  /**
  * Destructor.
  */
  virtual ~Stats();

  /**
  * finds a key value "s" and sets the value to "amount" of the
  * statistics map.
  * @param string s, the key to be added to the map.
  * @param int amount, the value to be linked to the key.
  **/
  void setStat(std::string s, int amount);

    /**
    * finds a key value "s" and modifies the value to "amount" of the
    * statistics map.
    * @param string s, the key to be added to the map.
    * @param int amount, the value to be linked to the key.
    **/
  void modifyStat(std::string s, int amount);


    /**
    * adds a key value "s" and sets the value to "amount" of the
    * statistics map.
    * @param string s, the key to be added to the map.
    * @param int amount, the value to be linked to the key.
    **/
  void addStat(std::string s, int amount);

  /**
  * removes a key "s" and its linked value
  * @param string s, the key to be added to the map.
  **/
  void removeStat(std::string s);

  /**
  * Returns the value of the specified stat in the parameter.
  * @param stat, the specified stat to be retrieved.
  * @return the value of the specified stat.
  */
  int getStat(std::string stat);

  /**
  * Checks if the statistics Map is empty or not.
  * @param returns true if empty, false if not.
  **/
  bool isEmpty();

 private:
  std::map<std::string, int> statistics;
};

#endif

/**
* @author Albert Arrieta <@albert.arrieta>
* @date 2021-11-11
*/
#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <string>

class Item {
 public:
  /**
  * Constructor, constructs the Item.
  * @param name is the name of the item.
  * @param description is the details about the item.
  */
  Item(std::string name, std::string description);

  /**
  * Destructor.
  */
  virtual ~Item();

  /**
  * Returns the name of the item.
  */
  std::string getName();

  /**
  * Returns the description of the item.
  */
  std::string getDescription();

 private:
  std::string name;
  std::string description;
};

#endif

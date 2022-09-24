/**
* @author Kurt Clarke <@kurt.clarke>
* @date 2021-11
*/

#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <string>

class Input {
 public:
  /**
  Requests an input from the user and returns a formatted version
  of that input for further use.
  @return returns a formatted string for further processing.
  **/
  std::string getInput();

  /**
  turns a string into all lowercase strings
  @param string a unprocessed string of upper and lowecase letters
  @return a string of only lowercase letters.
  **/
  std::string lowercase(std::string);

  /**
  converts a character to lowercase
  @ param a char of unknown case
  @ return returns a lowercase character
  **/
  char toLowercaseChar(char);
};

#endif

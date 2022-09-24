/**
* @author Kurt Clarke <kurt.clarke@uleth.ca>
* @date 2021-11-11
*/
#include <algorithm>
#include <string>
#include "Input.h"
#include "iostream"

// will currently only input a single word maybe?.
std::string Input::getInput() {
  std::string input;
  //std::cout << "Input: ";
  std::cin >> input;

  std::cin.clear();
  std::cin.ignore(500, '\n');

  // std::cout << std::endl;
  input = lowercase(input);
  //std::cout << "Input: " << input << " " << std::endl;
  return input;
}

std::string Input::lowercase(std::string unknCase) {
  std::string temp;
  for (int i = 0; i < unknCase.length(); i++)
  temp += toLowercaseChar(unknCase[i]);

  return temp;
}

char Input::toLowercaseChar(char unknCase) {
  if (unknCase <= 'Z' && unknCase >= 'A')
    return unknCase - ('Z' - 'z');
  return unknCase;
}

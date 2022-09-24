#include <string>
#include <sstream>
#include "gtest/gtest.h"
#include "Input.h"

TEST(TestInput, validInputTest) {
//What kind of constraints are we going to put on the program?
}

TEST(TestInput, getInputTest) {
  Input m;
  std::istringstream iss("Meow");
  std::cin.rdbuf(iss.rdbuf()); //sets cin to string stream.

  EXPECT_EQ("meow", m.getInput());
}

TEST(TestInput, lowercaseTest) {
  std::string s1, s2, s3;
  Input m;
  s1 = "It'S LoWeRcAsE?"; // add test with terminal special character.
  s2 = "it's lowercase?";
  s3 = m.lowercase(s1);
  EXPECT_EQ(s2, m.lowercase(s1));
}

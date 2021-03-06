#include <gtest/gtest.h>

#include "arguments/argumentParser/XMLArgumentParser/XMLArgumentParser.h"

/**
 * ***************************************************
 * Test correct functionality of the class XMLArgumentParser.
 * ******************************************+********
 */

/**
* Test that constructor sets all values as expected.
*/
TEST(XMLArgumentParser, constructor) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  const std::vector<std::string> args{"-x", "--filename", "file", "-b", "-3"};

  XMLArgumentParser<dim> parser{args};

  EXPECT_EQ(parser.getTokens(), args);
}

/**
* Test that validate input works as expected.
*/
TEST(XMLArgumentParser, validInput) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  const std::vector<std::string> args{"-x", "--filename", "file", "-b", "-3"};
  XMLArgumentParser<dim> parser{args};

  EXPECT_TRUE(parser.validateInput());
}

/**
* Test that validate input works as expected (missing filename).
*/
TEST(XMLArgumentParser, invalidInput_missingFileName) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  const std::vector<std::string> args{"-x", "-b", "-3"};
  XMLArgumentParser<dim> parser{args};

  EXPECT_THROW(parser.validateInput(), std::invalid_argument);
}

/**
* Test that validate input works as expected (unknown value).
*/
TEST(XMLArgumentParser, invalidInput) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  const std::vector<std::string> args{"-x", "--filename", "file", "-b", "-3", "-z"};
  XMLArgumentParser<dim> parser{args};

  EXPECT_THROW(parser.validateInput(), std::invalid_argument);
}

/**
* Test that create argument works as expected.
*/
TEST(XMLArgumentParser, createValidArgument) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  const std::vector<std::string>
      args{"-x", "--filename", "../../tests/arguments/argumentParser/XMLArgumentParser/input/valid_1.xml"};
  XMLArgumentParser<dim> parser{args};

  parser.validateInput();

  EXPECT_NO_THROW(parser.createArgument());
}

/**
* Test with invalid domain size. Domain size should be multiple of cell size.
*/
TEST(XMLArgumentParser, createInvalidArgumentDomainSize) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  const std::vector<std::string>
      args{"-x", "--filename", "../../tests/arguments/argumentParser/XMLArgumentParser/input/invalid_1.xml"};
  XMLArgumentParser<dim> parser{args};

  parser.validateInput();

  EXPECT_THROW(parser.createArgument(), std::invalid_argument);
}

/**
* Test with invalid cutoff radius size. Cutoff radius needs to be at least the size of the cell size.
*/
TEST(XMLArgumentParser, createInvalidArgumentCutoffRadius) { // NOLINT(cert-err58-cpp)
  constexpr static size_t dim = 3;

  const std::vector<std::string>
      args{"-x", "--filename", "../../tests/arguments/argumentParser/XMLArgumentParser/input/invalid_3.xml"};
  XMLArgumentParser<dim> parser{args};

  parser.validateInput();

  EXPECT_NO_THROW(parser.createArgument());
}

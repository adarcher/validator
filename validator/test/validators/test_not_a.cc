#include "test_not_a.h"

/// Functions defined in a cc file will allow for faster debug compiles
bool TestValidatorNotAValidate(TestData &data, bool &pass) {
  pass = data.a == 0;
  return pass;
}

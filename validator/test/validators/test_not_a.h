#pragma once

#include "../test_validator.h"

struct TestValidatorNotA : Validator<TestValidatorNotA, TestData> {
  static bool Validate(TestData &data, bool &pass) {
    pass = data.a == 0;
    return pass;
  }
};
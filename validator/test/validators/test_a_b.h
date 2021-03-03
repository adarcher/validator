#pragma once

#include "../test_validator.h"

struct TestValidatorAisB : Validator<TestValidatorAisB, TestData> {
  static bool Validate(TestData &data, bool &pass) {
    pass = data.a == data.b;
    return pass;
  }
};
#pragma once

#include "../validator.h"

struct TestData : public ValidationData {
  int a;
  int b;
};

ValidatorClass(TestValidator, TestData);

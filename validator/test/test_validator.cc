
#include "test_validator.h"

/// Include each validator function header, best to keep them separate
#include "validators/test_a.h"
#include "validators/test_a_b.h"
#include "validators/test_not_a.h"

ValidatorClassSetup(TestValidator);

void TestValidator::Initialize() {
  /// Recommended to either:
  //   check for multiple initializations OR
  //   clear them
  Names.clear();
  NameMap.clear();
  Validators.clear();

  /// Add/Register all validators here
  //  !! Order Matters
  RegisterValidatorFunction(TestValidatorA);
  RegisterValidatorFunction(TestValidatorAisB);
  RegisterValidatorFunction(TestValidatorNotA);
}

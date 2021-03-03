#include "validator/test/test_validator.h"

int main(int argc, char **args) {
  TestValidator::Initialize();

  std::cout << "This is a test of a simple Validator\n";

  TestData data = {.a = 1, .b = 2};
  bool pass = true;

  std::cout << ValidatorName(TestValidator) << " Test Run(...):" << std::endl;
  TestData dataA = data;
  uint32_t last = TestValidator::Run(dataA, pass);

  for (auto const &v : dataA.history) {
    std::cout << "  " << TestValidator::NameOf(v.validatorEnum) << "["
              << v.validatorEnum << "] " << (v.pass ? "PASSED" : "FAILED")
              << std::endl;
  }

  std::cout << ValidatorName(TestValidator)
            << " Test Run(..., all=true):" << std::endl;
  TestData dataB = data;
  pass = true;
  last = TestValidator::Run(dataB, pass, true);

  for (auto const &v : dataB.history) {
    std::cout << "  " << TestValidator::NameOf(v.validatorEnum) << "["
              << v.validatorEnum << "] " << (v.pass ? "PASSED" : "FAILED")
              << std::endl;
  }

  return 0;
}
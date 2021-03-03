// Simple class/func to call multiple conditional checks on a set of data

#pragma once

#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/// Example enum name generator: just uses the validation function class name
#define ValidatorName(v) #v

struct ValidationResult {
  uint32_t validatorEnum;
  bool pass;
};
struct ValidationData {
  /// Each data run will hold the history of the validations and if they passed
  std::deque<ValidationResult> history;
  bool pass;

  uint32_t FirstFail() {
    for (auto &&h : history) {
      if (!h.pass)
        return h.validatorEnum;
    };
    return 0;
  }
};

/// Example register helper, use only inside T::Initialize()
#define RegisterValidatorFunction(v) Register(&v::Validate, ValidatorName(v))

template <class T, class D> class Validator {
public:
  /// No constructor, just the base functions to validate and initialize
  typedef bool (*ValidatorFunc)(D &data, bool &pass);
  static bool Validate(D &data, bool &pass) { return T::Validate(data, pass); };
  static void Initialize() { T::Initialize(); }

  /// These are required by the validation class:
  //   typedef bool (*ValidatorFunc)(D data, bool &pass);
  //   static std::deque<ValidatorFunc> Validators;
  //   static std::map<std::string, unsigned int> NameMap;
  //   static std::vector<std::string> Names;
  //   static std::vector<std::string> Name;

  /// Loop through registered validator functions:
  //   pass is modified with the final result
  //   data is the test structure passed down: sequential tests can add data as
  //   needed return enum/index of last validator run
  static uint32_t Run(D &data, bool &pass, bool all = false) {
    uint32_t i = 0;
    bool cumulative_pass = true;
    for (; i < T::Validators.size(); i++) {
      T::Validators[i](data, pass);
      cumulative_pass = pass && cumulative_pass;
      data.history.push_back({i, pass});
      if (!pass && !all) {
        break;
      }
    }
    data.pass = cumulative_pass;
    return i;
  }

  /// Lookup helper functions
  static std::string NameOf(uint32_t i) { return T::Names[i]; }
  static uint32_t ValidatorEnum(std::string name) { return T::NameMap[name]; }

  /// Required function that is usually inside  T::Initialize()
  //   validatorName can be from the ValidatorName() macro in this file
  static uint32_t Register(ValidatorFunc validationFunction,
                           std::string validationName) {
    /// Check if this is a duplication: not allowe
    if (T::NameMap.find(validationName) != T::NameMap.end()) {
      std::cerr << T::Name << " Error: " << validationName
                << " already registered." << std::endl;
      return 0;
    }
    T::Validators.push_back(validationFunction);
    T::NameMap[validationName] = T::Names.size();
    T::Names.emplace_back(validationName);

    return T::Names.size();
  }
};

/// This will create the subclass needed to run tests
//   (This can be done by hand, this is just a helper)
#define ValidatorClass(_CLASS_NAME_, _DATA_NAME_)                              \
  class _CLASS_NAME_ : public Validator<_CLASS_NAME_, _DATA_NAME_> {           \
  public:                                                                      \
    friend class Validator<_CLASS_NAME_, _DATA_NAME_>;                         \
                                                                               \
    template <class V> static bool Validate(_DATA_NAME_ &data, bool &pass) {   \
      return V::Validate(data, pass);                                          \
    };                                                                         \
                                                                               \
    static void Initialize();                                                  \
                                                                               \
    static std::string Name;                                                   \
                                                                               \
  protected:                                                                   \
    static std::deque<ValidatorFunc> Validators;                               \
    static std::map<std::string, unsigned int> NameMap;                        \
    static std::vector<std::string> Names;                                     \
  };

/// This will initialize the class static members
//   (This can be done by hand, this is just a helper)
#define ValidatorClassSetup(_CLASS_NAME_)                                      \
  std::deque<_CLASS_NAME_::ValidatorFunc> _CLASS_NAME_::Validators;            \
  std::vector<std::string> _CLASS_NAME_::Names;                                \
  std::map<std::string, unsigned int> _CLASS_NAME_::NameMap;                   \
  std::string _CLASS_NAME_::Name = ValidatorName(TestValidator);\

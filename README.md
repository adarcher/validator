***Note:** my dad wanted to see an example of a few things I mentioned during a phone conversation, so this is a "quick and dirty" reply to him.  It includes a few things as formalities and caveats that this isn't a fully fleshed-out or mature tool.*

# Simple Validator Class

_Anddy Archer, 2021 :: licensed under CC0_

This is an example of a helper class that is never instatiated.

The purpose of this class is to organize similar tests for a set of data that are intended to be run sequencially and stop as soon as one fails.

## Install/Run

To use this is simple: just copy the `validator.h` to where you'd like your validators to live and start subclassing it.

The `run.sh` will compile and run the example. It requires that you have `clang++` and `-std=c++2a` available.

## Explaination

The `Validator` class is abstract in the sense that it is missing required members that are defined in the first level subclass.

See `validator/validator.h` for the base class and some comments explaining the helper macros.

See `validator/test/test_validator.[hc]` for exmample usage of the macros and the class. Notice that the class declaration and setup is generic but the `Initialize()` function is needed to setup the order of registered validation functions. Also notice the difference and usage of the example validator functions' files: only a header and the `Validate(...)` function are required. The latter of which can be defined in a `.c` file and compiled as an object if desired--see `test_not_a.[h,cc]`.

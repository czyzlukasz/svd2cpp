# svd2cpp
Zero-cost abstraction register library generator.
## What is *svd2cpp*?
*svd2cpp* is a generator that parses .svd files provided by ARM chip vendor.
It generates header file that allows for reading and writing to microcontroller's registers with zero overhead.

## How to get *svd2cpp*?
  Download source code and compile it. Note that this repo uses submodules thus do not forget to `git submodule init` and `git submodule update` after cloning.

OR

  Download precompiled parser.

## How to use *svd2cpp*?
That's super easy:
```console
./svd2cpp -i svdFile.svd -o generatedHeader.hpp
```

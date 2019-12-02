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

## How to use generated header?
After including header in your code, you can use all features such as *set*, *reset*, *read*.

Syntax is quite simple and easy to use:
```cpp
operation<PERIPHERAL::REGISTER::BIT>();
```
###Examples:
Set bit UE(USART enable) in USART1 Control Register 1
```cpp
set<USART1::CR1::UE>();
```

Reset bit UE(USART enable) in USART1 Control Register 1
```cpp
reset<USART1::CR1::UE>();
```

Read Channel 1 Transfer Complete flag in DMA1 ISR Register
```cpp
bool transferComplete = read<DMA1::ISR::TCIF1>();
```

Set Memory address for DMA1 channel 2
```cpp
set<DMA1::CMAR2::MA>(0xDEADBEEF);
```

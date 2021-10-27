# Big Integer Library

```

██████╗ ██╗ ██████╗     ██╗███╗   ██╗████████╗
██╔══██╗██║██╔════╝     ██║████╗  ██║╚══██╔══╝
██████╔╝██║██║  ███╗    ██║██╔██╗ ██║   ██║   
██╔══██╗██║██║   ██║    ██║██║╚██╗██║   ██║   
██████╔╝██║╚██████╔╝    ██║██║ ╚████║   ██║   
╚═════╝ ╚═╝ ╚═════╝     ╚═╝╚═╝  ╚═══╝   ╚═╝   
                                  
```
## About `big_int`

`big_int` is an [arbitrary precision (infinite-precision arithmetic)](https://en.wikipedia.org/wiki/Arbitrary-precision_arithmetic) integer library which can be used to do arithmetic calculations on numbers whose digits of precision are limited only by the available memory of the host system. Infinite-precision arithmetic has lot of applications in the field of computing especially if the programming language doesnt natively support infinite-precision arithmetics such as C & C++. Some of the main applications include [**public-key cryptography**](https://en.wikipedia.org/wiki/Public-key_cryptography), calculation involving very long numbers such as factorial of large numbers, example: 1000!.

### Project

The `big_int` library is implemented purely in C++ language without any 3rd party libraries or dependencies. The project uses CMake build file generator and uses [`pybind11`](https://github.com/pybind/pybind11) for exposing C++ API's as python modules for testing.

### Get started: Build & Test Project

``` sh
git clone <url>
cd big_int
git submodule update --init --recursive #if python module generation is required
mkdir build && cd build
cmake .. -DPYTHON_TEST_BINDINGS_GEN=ON -DENABLE_IPO=ON -DCMAKE_BUILD_TYPE=Release #turn -DPYTHON_TEST_BINDINGS_GEN=OFF if  python module generation is not required
make
python3 ../tests/pybind_tests/run_tests.py 1
```

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

`big_int` is an [arbitrary precision (infinite-precision arithmetic)](https://en.wikipedia.org/wiki/Arbitrary-precision_arithmetic) integer library which can be used to do arithmetic calculations on numbers whose digits of precision are limited only by the available memory of the host system. Infinite-precision arithmetic has lot of applications in the field of computing especially if the programming language doesnt natively support infinite-precision arithmetics such as C & C++. Some of the main applications include [**public-key cryptography**](https://en.wikipedia.org/wiki/Public-key_cryptography) and calculation involving very long numbers such as factorial of large numbers, for example `100000!`.


## Project

The `big_int` library is implemented purely in C++ language without any 3rd party libraries or dependencies. The project uses CMake build file generator and uses [`pybind11`](https://github.com/pybind/pybind11) for exposing C++ API's as python modules for testing.

### Get started: Build & Test Project

``` sh
git clone <url>
cd big_int
git submodule update --init --recursive #if python module generation is required
mkdir build && cd build
cmake .. -DPYTHON_TEST_BINDINGS_GEN=ON -DENABLE_IPO=ON -DCMAKE_BUILD_TYPE=Release #turn -DPYTHON_TEST_BINDINGS_GEN=OFF if  python module generation is not required
make
python3 ../tests/pybind_tests/run_tests.py 1 #only if -DPYTHON_TEST_BINDINGS_GEN=ON
```

## Available operations

| Operations/Functions | Brief description |
|     :---      | :---:          |
| `int big_int_from_string(const std::string &str_num)`     | Convert a hexadicimal string of any length to `big_int`.    |
| `int big_int_from_base_type(const BI_BASE_TYPE &bt_val, const bool is_neg)`      | Convert a number of type `BI_BASE_TYPE` (default, `uint32_t`) to `big_int`.      |
|  `std::string     big_int_to_string(bi_base base)`      |   Convert a `big_int` to string (Note: Currently only support hexadecimal string output)    |
|   `int             big_int_compare(const big_int &other) const`     |  Compare two `big_int`s, returns 1 if calling `big_int` is greater than `other`, 0 if equal and -1 if less than.    |
|        |      |
|        |      |
|        |      |
|        |      |
|        |      |
|        |      |
|        |      |
|        |      |
|        |      |
|        |      |

### Examples using `big_int`:


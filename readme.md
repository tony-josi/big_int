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
| :---      |   :---          |
| `int big_int_from_string(const std::string &str_num)`     | Convert a hexadicimal string of any length to `big_int`.    |
| `int big_int_from_base_type(const BI_BASE_TYPE &bt_val, const bool is_neg)`      | Convert a number of type `BI_BASE_TYPE` (default, `uint32_t`) to `big_int`.      |
|  `std::string     big_int_to_string(bi_base base)`      |   Convert a `big_int` to string (Note: Currently only support hexadecimal string output)    |
|   `int             big_int_compare(const big_int &other) const`     |  Compare two `big_int`s, returns 1 if calling `big_int` is greater than `other`, 0 if equal and -1 if less than.    |
|    `int             big_int_unsigned_compare(const big_int &other) const`    | Unsigned comparisson, returns 1 if calling `big_int` is greater than `other`, 0 if equal and -1 if less than.       |
|   `int             big_int_unsigned_add(const big_int &b, big_int &res)`     |   Does unsigned addition of two `big_int`s and stores the result in res.   |
|  `int             big_int_signed_add(const big_int &b, big_int &res)`      |   Does signed addition of two `big_int`s and stores the result in res.    |
|    `int             big_int_set_negetive(bool set_unset)`    |    Set `big_int` as negetive/positive based on `set_unset`  |
|   `int             big_int_set_zero()`     |   Set `big_int` as zero   |
|   `bool            big_int_is_negetive() const`     |    Check if the `big_int` is negetive  |
|    `bool            big_int_is_zero() const`    |  Check if the `big_int` is zero    |
|     `int             big_int_clear()`   |  Clear the contents    |
|    `int             big_int_signed_sub(const big_int &b, big_int &res)`    |   Does signed subtraction of two `big_int`s and stores the result in res    |
|   `int             big_int_unsigned_sub(const big_int &b, big_int &res) const`     |    Does unsigned subtraction of two `big_int`s and stores the result in res. (Note: This functions `throws` if the absolute value of argument `other` is less than the calling object. )  |
|   `int             big_int_multiply(const big_int &b, big_int &res)`     |   Does signed multiplication of two `big_int`s and stores the result in res   |

| Operations/Functions | Brief description |
| :---      |   :---          |
|   `int             big_int_unsigned_multiply_base_type(const BI_BASE_TYPE &b, big_int &res) const`     |   Does unsigned multiplication of calling `big_int` and a `BI_BASE_TYPE` (default, `uint32_t`) value and stores the result in res   |
|    `int             big_int_get_num_of_hex_chars() const`    |   Get the number of hex characters in the hexadecimal representation of the `big_int`   |
|   `int             big_int_get_num_of_bits() const`     |   Get the bit size of the calling `bit_int`   |
|  `int             big_int_div(const big_int &divisor, big_int &quotient, big_int &remainder)`      |  Signed division of calling `big_int` with the `divisor` `big_int` and stores the quotient in `quotient` and remainder in `remainder`    |
|    `int             big_int_power_base_type(const BI_BASE_TYPE &exponent, big_int &result)`    |  Calculates the power of calling big_int when its raised to    a `BI_BASE_TYPE` (default, `uint32_t`) value, `exponent` and stores the result in `result`  |
|   `int             big_int_fast_modular_exponentiation(const big_int &exponent, const big_int &modulus, big_int &result)`     |   Calculates the fast modular exponentiation using the **fast modular exponentiation algorithm** and stores the result in `result`.   |
|   `int             big_int_modulus(const big_int &modulus, big_int &result)`     |   Calculates the modulus of the calling `big_int` and stores the result in `result`.    |

| Operations/Functions | Brief description |
| :---      |   :---          |
|   `int             big_int_gcd_euclidean_algorithm(const big_int &b, big_int &op_gcd)`     |    Calculates the greatest common divisor of the calling `big_int` and another `big_int` `b` using the **euclidean algorithm** and stores the result in `op_gcd`  |
| `int             big_int_modular_inverse_extended_euclidean_algorithm(const big_int &modulus, big_int &inverse)`       |  Calculates the modular inverse of the calling `big_int` in the field `modulus`, using **extended euclidean algorithm** and stores the result in `inverse`    |
|   `bool            big_int_is_even() const`     | Check if number is even     |
|   `int             big_int_fast_divide_by_power_of_two(int power, big_int &remainder, big_int &coefficient) const`     |   Fast division of big_int by powers of 2   |
|  `int             big_int_fast_multiply_by_power_of_two(int power, big_int &result) const`      |   Fast multiplication of big_int by powers of 2   |
|   `int             big_int_get_random_unsigned(int bits)`     | Generate a random unsigned big_int with given number of bits     |
|    `int             big_int_get_random_unsigned_between(const big_int &low, const big_int &high)`    |   Generate a random unsigned `big_int` between given `low` and `high` `big_int`s  |
|    `int             big_int_get_random_unsigned_prime_rabin_miller(int bits, int reqd_rabin_miller_iterations)`    |   Generate a random unsigned prime `big_int` of given bits, at verifies the primility using **Rabin Miller algorithm** for the given `reqd_rabin_miller_iterations` iterations   |

| Operations/Functions | Brief description |
| :---      |   :---          |
|   `int  big_int_get_random_unsigned_prime_rabin_miller_threaded(int bits, int reqd_rabin_miller_iterations, int no_of_threads)`     |  Generate a random unsigned prime `big_int` of given bits, at verifies the primility using **Rabin Miller algorithm** for the given `reqd_rabin_miller_iterations` iterations, using `no_of_threads` threads. Negetive or 0 thread count causes maximum (`std::thread::hardware_concurrency();`) threads to be used, more than `std::thread::hardware_concurrency();` will cause max threads to be `std::thread::hardware_concurrency();`    |
|   `int             big_int_left_shift_word(int shift_words, big_int &res)`     |   Left shift the `big_int` with `shift_words` mulitples of 32 bits.   |
|     `int             big_int_left_shift(int bits, big_int &res)`   |   Left shift the `big_int` with given `bits`.     |
|   `int             big_int_right_shift_word(int shift_words, big_int &res)`     |   Right shift the `big_int` with `shift_words` mulitples of 32 bits.   |
|     `int             big_int_right_shift(int bits, big_int &res)`   |  Right shift the `big_int` with given `bits`.     |

### Examples using `big_int`:

#### 100000 Factorial

* [`factorial_100000.txt`](https://github.com/TonyJosi97/big_int/blob/master/examples/factorial_100000.txt)


#### RSA-8192

* [RSA-8192.txt](https://github.com/TonyJosi97/big_int/blob/master/examples/RSA-8192.txt)
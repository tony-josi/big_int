# Big Integer Library

```

██████╗ ██╗ ██████╗     ██╗███╗   ██╗████████╗
██╔══██╗██║██╔════╝     ██║████╗  ██║╚══██╔══╝
██████╔╝██║██║  ███╗    ██║██╔██╗ ██║   ██║   
██╔══██╗██║██║   ██║    ██║██║╚██╗██║   ██║   
██████╔╝██║╚██████╔╝    ██║██║ ╚████║   ██║   
╚═════╝ ╚═╝ ╚═════╝     ╚═╝╚═╝  ╚═══╝   ╚═╝   
                                        
```

Big int is an arbitrary precision (infinite-precision arithmetic) integer library which can be used to do arithmetic calculations on numbers whose digits of precision are limited only by the available memory of the host system.

### Build & Test Project

```
mkdir build && cd build
cmake .. -DPYTHON_TEST_BINDINGS_GEN=ON -DENABLE_IPO=ON -DCMAKE_BUILD_TYPE=Release
make
python3 ../tests/pybind_tests/run_tests.py 1
```


### Build & Test Project

```
mkdir build && cd build
cmake .. -DPYTHON_TEST_BINDINGS_GEN=ON -DENABLE_IPO=ON
make
python3 ../tests/pybind_tests/run_tests.py 1
```
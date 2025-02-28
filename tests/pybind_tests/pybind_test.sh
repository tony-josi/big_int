
command_output="$(python3-config --extension-suffix)"
bi_python_module="../../build/src/big_int_test_cases/py_big_int_tc_wrap$command_output"

echo "Expected python module path: $bi_python_module"

cp $bi_python_module ./py_big_int_tc_wrap.so

python3 run_tests.py 1

# CMake generated Testfile for 
# Source directory: C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/test
# Build directory: C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/out/build/x64-Debug/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unittest_polynomial_1 "test_polynomial" "C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/data/p1.txt")
set_tests_properties(unittest_polynomial_1 PROPERTIES  PASS_REGULAR_EXPRESSION "2.25" _BACKTRACE_TRIPLES "C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/test/CMakeLists.txt;11;add_test;C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/test/CMakeLists.txt;0;")
add_test(unittest_polynomial_2 "test_polynomial" "C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/data/p2.txt")
set_tests_properties(unittest_polynomial_2 PROPERTIES  PASS_REGULAR_EXPRESSION "0.75" _BACKTRACE_TRIPLES "C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/test/CMakeLists.txt;12;add_test;C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/test/CMakeLists.txt;0;")
add_test(unittest_pol_func_1 "test_polynomial_function" "C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/data/")
set_tests_properties(unittest_pol_func_1 PROPERTIES  PASS_REGULAR_EXPRESSION "3" _BACKTRACE_TRIPLES "C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/test/CMakeLists.txt;17;add_test;C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/test/CMakeLists.txt;0;")
add_test(unittest_lambda_func_1 "test_lambda_function" "C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/data/")
set_tests_properties(unittest_lambda_func_1 PROPERTIES  PASS_REGULAR_EXPRESSION "1.6875" _BACKTRACE_TRIPLES "C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/test/CMakeLists.txt;21;add_test;C:/Users/XIAOCHUYANG/Desktop/cs100-hw10/test/CMakeLists.txt;0;")

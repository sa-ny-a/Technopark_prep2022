# CMake generated Testfile for 
# Source directory: /home/sanya/Homework/project/tests
# Build directory: /home/sanya/Homework/build/project/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BaseTest "/home/sanya/Homework/memtest.sh" "/home/sanya/Homework/build/project/tests/tests" "/home/sanya/Homework/project/tests/data" "--gtest_filter=-*Extra*")
set_tests_properties(BaseTest PROPERTIES  _BACKTRACE_TRIPLES "/home/sanya/Homework/project/tests/CMakeLists.txt;26;ADD_TEST;/home/sanya/Homework/project/tests/CMakeLists.txt;0;")
add_test(ExtraTest "/home/sanya/Homework/memtest.sh" "/home/sanya/Homework/build/project/tests/tests" "/home/sanya/Homework/project/tests/data" "--gtest_filter=*Extra*")
set_tests_properties(ExtraTest PROPERTIES  _BACKTRACE_TRIPLES "/home/sanya/Homework/project/tests/CMakeLists.txt;30;ADD_TEST;/home/sanya/Homework/project/tests/CMakeLists.txt;0;")

# Testing library
FetchContent_Declare(
catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG        v2.9.1
)
FetchContent_MakeAvailable(catch2)

add_executable(linkedlist_test
    test_main.cpp
)

# Use C++17
target_compile_features(linkedlist_test PRIVATE cxx_std_17)

# Link to main library and Catch2 library
target_link_libraries(linkedlist_test PRIVATE linkedlist Catch2::Catch2)

# Register tests
add_test(NAME linkedlist_test_all COMMAND linkedlist_test)

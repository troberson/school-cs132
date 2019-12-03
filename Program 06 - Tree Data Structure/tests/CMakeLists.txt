# Testing library
FetchContent_Declare(
catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG        v2.9.1
)
FetchContent_MakeAvailable(catch2)

add_executable(tree_test
    test_main.cpp
    Tree_test.cpp
)

# Use C++17
target_compile_features(tree_test PRIVATE cxx_std_17)

# Link to main library and Catch2
target_link_libraries(tree_test
    PRIVATE
        tree
        Catch2::Catch2
)

# Register tests
add_test(NAME linkedlist_test_all COMMAND linkedlist_test)

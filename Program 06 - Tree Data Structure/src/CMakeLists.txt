# Compile the main linkedlist library
add_library (tree
    Tree.cpp
)

# Include the header files
target_include_directories(tree PUBLIC ${Tree_SOURCE_DIR}/include)

# Use C++17
target_compile_features(tree PRIVATE cxx_std_17)


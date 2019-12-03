add_executable(tree_app
    tree_app.cpp
)

# Use C++17
target_compile_features(tree_app PRIVATE cxx_std_17)

# Link to the main library
target_link_libraries(tree_app PRIVATE tree)

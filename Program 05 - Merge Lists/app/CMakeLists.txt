add_executable(merge_app
    MergeLinkedList.cpp
)

# Use C++17
target_compile_features(merge_app PRIVATE cxx_std_17)

# Link to the main library
target_link_libraries(merge_app PRIVATE linkedlist)

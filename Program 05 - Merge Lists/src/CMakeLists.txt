# Compile the main linkedlist library
add_library (linkedlist
    LkList.cpp
)

# Include the header files
target_include_directories(linkedlist PUBLIC ${LinkedList_SOURCE_DIR}/include)

# Use C++17
target_compile_features(linkedlist PRIVATE cxx_std_17)


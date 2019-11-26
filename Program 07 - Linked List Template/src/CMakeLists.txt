# Compile the main linkedlist library
add_library (linkedlist INTERFACE)

# Include the header files
target_include_directories(linkedlist INTERFACE ${LinkedList_SOURCE_DIR}/include)

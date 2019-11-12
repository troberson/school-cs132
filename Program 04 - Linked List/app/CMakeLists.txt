add_executable(linkedlist_app
    Linked\ List\ Assignment.cpp
)

configure_file(infile1.txt infile1.txt COPYONLY)
configure_file(infile2.txt infile2.txt COPYONLY)

# Use C++17
target_compile_features(linkedlist_app PRIVATE cxx_std_17)

# Link to the main library
target_link_libraries(linkedlist_app PRIVATE linkedlist)

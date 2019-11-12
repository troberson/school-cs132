add_executable(trstring_app
    format_words.cpp
)

configure_file(infile3.txt infile3.txt COPYONLY)

# Use C++17
target_compile_features(trstring_app PRIVATE cxx_std_17)

# Link to the main library
target_link_libraries(trstring_app PRIVATE trstring)


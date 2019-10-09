# Compile the main euler library
add_library(trstring
    string_utils.cpp
    TRString.cpp
)

# Include the header files
target_include_directories(trstring PUBLIC ${TRString_SOURCE_DIR}/include)

# Use C++17
target_compile_features(trstring PRIVATE cxx_std_17)

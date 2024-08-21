project(T9Predictor)

# Cxx T9 prediction library
add_library(${PROJECT_NAME}_LIB
            SHARED
            "src/LetterFrequencyTrie.cpp")

include_directories(.)

target_compile_definitions(${PROJECT_NAME}_LIB
                           PRIVATE
                           CXX_LIB=1)

set_target_properties(${PROJECT_NAME}_LIB PROPERTIES
                      PUBLIC_HEADER "include/LetterFrequencyTrie.h")

# Library to expose this in C (with Unity in mind)
add_library(${PROJECT_NAME}_C_LIB
            SHARED
            "src/LetterFrequencyTrieCBindings.cpp"
            "src/LetterFrequencyTrie.cpp")

# Test app for the cpp
set(TEST_APP_SRCS "main.cpp")

add_executable(predictor ${TEST_APP_SRCS})
target_link_libraries(predictor
                     ${PROJECT_NAME}_LIB)

# Test app for the C
set(C_TEST_APP_SRCS "c_test_main.cpp")

add_executable(predictor_c ${C_TEST_APP_SRCS})
target_link_libraries(predictor_c
                     ${PROJECT_NAME}_C_LIB)
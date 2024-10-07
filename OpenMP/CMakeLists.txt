find_package(OpenMP)
add_compile_options(-Wunknown-pragmas)

add_executable(matrix_vector src/matrix_vector.cpp)
target_link_libraries(matrix_vector OpenMP::OpenMP_CXX)
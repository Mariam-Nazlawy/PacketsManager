include(GenerateExportHeader)
cmake_minimum_required(VERSION 3.23)
project(Project1_cppv2)

set(CMAKE_CXX_STANDARD 20)
add_library(PacketsManagerlib STATIC PacketsManager.cpp PacketsManager.h)

generate_export_header(PacketsManagerlib)
install(FILES ${PROJECT_BINARY_DIR}/PacketsManager.h DESTINATION include)

add_executable(Project1_cppv2 main.cpp)


target_link_libraries(Project1_cppv2 PUBLIC PacketsManagerlib)


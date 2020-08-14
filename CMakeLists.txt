cmake_minimum_required( VERSION 2.8 )

project(GauNMRScaler)
message(status "Project: GauNMRScaler")

include_directories(
${PROJECT_SOURCE_DIR}/include
)

set(SRC
${PROJECT_SOURCE_DIR}/src/GauNMRScaler.c
${PROJECT_SOURCE_DIR}/src/GauNMRScaler_sub.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
${PROJECT_SOURCE_DIR}/bin
)

add_executable(
${PROJECT_NAME} ${SRC}
)


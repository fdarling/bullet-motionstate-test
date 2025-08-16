cmake_minimum_required(VERSION 3.13)

project(bullet-motionstate-test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Bullet REQUIRED)

include_directories(${PROJECT_NAME} PRIVATE
    ${BULLET_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${BULLET_LIBRARIES}
)

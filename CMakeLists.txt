cmake_minimum_required(VERSION 3.20.2)

project(ViGEmClient)

find_package(ament_cmake)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ViGEmClient.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Internal.h ${CMAKE_CURRENT_SOURCE_DIR}/src/resource.h ${CMAKE_CURRENT_SOURCE_DIR}/src/ViGEmClient.rc)
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME}
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(${PROJECT_NAME}
    INTERFACE setupapi
)
add_executable(vigem_example
    example.cpp
)
target_link_libraries(vigem_example PUBLIC ${PROJECT_NAME})
target_compile_definitions(vigem_example PUBLIC WIN32_LEAN_AND_MEAN)

install(TARGETS ${PROJECT_NAME} vigem_example
    EXPORT ${PROJECT_NAME}-export
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY include/ViGEm
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
if(ament_cmake_FOUND)
    message(STATUS "Ament was found. Building a ROS2-style cmake package")
    ament_export_targets(${PROJECT_NAME}-export)
    ament_package()
endif()
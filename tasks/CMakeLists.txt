
file(GLOB RACK_TASKS_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
)

add_library(tasks STATIC
    ${RACK_TASKS_SOURCES}
)

target_include_directories(tasks PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(tasks
        pico_stdlib
        FreeRTOS-Kernel-Heap4
)
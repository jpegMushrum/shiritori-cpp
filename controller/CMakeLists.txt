add_library(controller STATIC
    info_controller.cpp
    task_queue.cpp
)

target_include_directories(controller PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(controller PRIVATE service)
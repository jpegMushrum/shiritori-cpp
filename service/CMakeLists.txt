add_library(service STATIC
    game_session.cpp
    game_fabric.cpp
    info_service.cpp
    mapper.cpp
    dto/user_info.cpp
    game_info.cpp
    player_score.cpp
)

target_include_directories(service PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(service PUBLIC repo)
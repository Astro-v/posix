
add_executable(server main.cpp Server.cpp Client.cpp DummyMessageProcessing.cpp)

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(server lib_posix)

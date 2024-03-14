add_library(lib_posix Socket.cpp Listener.cpp Address.cpp)

target_include_directories(lib_posix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
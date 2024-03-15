
add_executable(server main.cpp include/Client.hpp)

target_link_libraries(server lib_posix)

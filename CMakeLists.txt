cmake_minimum_required(VERSION 3.15)
project(WinFi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Windows SDK
if(MSVC)
    add_compile_options(/ZW /EHsc /utf-8)
    link_libraries(windowsapp.lib)
endif()

add_executable(WinFi WIN32 main.cpp)

# Link necessary Windows libraries
target_link_libraries(WinFi PRIVATE 
    user32.lib 
    gdi32.lib 
    runtimeobject.lib
)

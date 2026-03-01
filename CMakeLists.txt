cmake_minimum_required(VERSION 3.15)
project(WinFi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure for MSVC (Windows)
if(MSVC)
    # /EHsc: Standard C++ exception handling
    # /utf-8: Set source and execution character sets to UTF-8
    # We REMOVE /ZW because C++/WinRT is standard C++17 and doesn't use C++/CX metadata
    add_compile_options(/EHsc /utf-8)
    
    # Link against the Windows App support library for WinRT APIs
    link_libraries(windowsapp.lib)
endif()

# Define the executable as a Win32 GUI app (no console window)
add_executable(WinFi WIN32 main.cpp)

# Link core Windows libraries
target_link_libraries(WinFi PRIVATE 
    user32.lib 
    gdi32.lib 
    runtimeobject.lib
)

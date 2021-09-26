cmake_minimum_required(VERSION 3.17)
project(wkTestStuff)

set(CMAKE_CXX_STANDARD 20)

add_library(hacklib STATIC
        lib/hacklib/ExeFile.cpp lib/hacklib/ExeFile_WIN32.cpp
        lib/hacklib/PatternScanner.cpp lib/hacklib/Memory_WIN32.cpp)

link_directories(lib)
include_directories(include lib/hacklib)

configure_file(
        resource.rc.in
        resource.rc
)
add_definitions(-DLIBRARY_EXPORTS)

add_library(wkTestStuff SHARED
        src/dllmain.cpp
        src/Config.cpp src/Config.h
        src/WaLibc.cpp src/WaLibc.h
        src/DevConsole.cpp src/DevConsole.h
        src/Hooks.cpp src/Hooks.h
        src/BitmapImage.cpp src/BitmapImage.h
        src/W2App.cpp src/W2App.h
        src/Utils.cpp src/Utils.h
        src/Debugf.h
        src/Chat.cpp src/Chat.h
        src/commands/Sudoku.cpp src/commands/Sudoku.h
        src/entities/CTask.h src/entities/CGameTask.h src/entities/CList.h
        src/entities/CTaskTeam.h src/entities/CTaskWorm.h
        src/Constants.h
        ${CMAKE_CURRENT_BINARY_DIR}/resource.rc
        src/commands/Help.cpp src/commands/Help.h
        src/commands/Ammo.cpp src/commands/Ammo.h
        src/commands/Delete.cpp src/commands/Delete.h
        src/commands/Objects.cpp src/commands/Objects.h)

set_property(TARGET wkTestStuff hacklib PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(wkTestStuff hacklib capstone Polyhook_2 version)

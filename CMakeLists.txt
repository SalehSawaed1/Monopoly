cmake_minimum_required(VERSION 3.16)

project(monopoly_game VERSION 0.1 LANGUAGES CXX)

# Enable automatic handling of Qt features like UIC, MOC, RCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required Qt components
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui)

# Ensure Qt is found
if(NOT Qt${QT_VERSION_MAJOR}_FOUND)
    message(FATAL_ERROR "Qt${QT_VERSION_MAJOR} not found. Ensure Qt is installed and accessible.")
endif()

# Include directories for Qt
include_directories(${Qt${QT_VERSION_MAJOR}_INCLUDE_DIRS})

# Link directories for Qt
link_directories(${Qt${QT_VERSION_MAJOR}_LIBRARY_DIRS})

# Add your GUI source files
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    form.h form.cpp form.ui
    ../Downloads/board.jpg
    board.qrc
    Grid.cpp
    Grid.h
    player.h player.cpp
    propertygrid.h propertygrid.cpp
    railroadgrid.h railroadgrid.cpp
    utilitygrid.h utilitygrid.cpp
    monopolyboard.h monopolyboard.cpp
    gamemanager.h gamemanager.cpp
    specialgrid.h specialgrid.cpp
    surprisegrid.h surprisegrid.cpp
    taxgrid.h taxgrid.cpp
    gotojailgrid.h gotojailgrid.cpp
    freeparkinggrid.h freeparkinggrid.cpp
    gamehandler.h gamehandler.cpp
    jailgrid.h jailgrid.cpp
)

# Add the Qt GUI application executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(monopoly_game
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        PointF.h
        playeraction.h
    )
else()
    if(ANDROID)
        add_library(monopoly_game SHARED ${PROJECT_SOURCES})
    else()
        add_executable(monopoly_game ${PROJECT_SOURCES})
    endif()
endif()

# Link Qt libraries for the main executable
target_link_libraries(monopoly_game PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)

# Set target properties for the main executable
set_target_properties(monopoly_game PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Setup installation paths
include(GNUInstallDirs)
install(TARGETS monopoly_game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executable for Qt 6+
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(monopoly_game)
endif()

cmake_minimum_required(VERSION 3.4)
project(sfml_test)

set(sfml_test_VERSION_MAJOR 1)
set(sfml_test_VERSION_MINOR 0)
set(sfml_test_VERSION_PATCH 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(SOURCE_FILES
    main.cpp
    game.cpp
    scenenode.cpp
    entity.cpp
    aircraft.cpp
    world.cpp
    spritenode.cpp
    command.h category.h commandqueue.cpp commandqueue.h player.cpp player.h aircraftmover.h derivedaction.h statestack.cpp statestack.h state.cpp state.h states.h statestack.hpp fontholder.h fonts.h application.cpp application.h titlestate.cpp titlestate.h menustate.cpp menustate.h gamestate.cpp gamestate.h pausestate.cpp pausestate.h printargs.h loadingstate.cpp loadingstate.h paralleltask.cpp paralleltask.h util.h component.cpp component.h container.cpp container.h label.cpp label.h button.cpp button.h settingsstate.cpp settingsstate.h)

add_executable(sfml_test MACOSX_BUNDLE ${SOURCE_FILES})

find_package(SFML 2 REQUIRED graphics window system)

target_link_libraries(sfml_test ${SFML_LIBRARIES})

#if (APPLE)
#    set(MACOSX_DEPLOYMENT_TARGET 10.7)
#    set(CMAKE_BUNDLE_VERSION  "${sfml_test_VERSION_MAJOR}.${sfml_test_VERSION_MINOR}.${sfml_test_VERSION_PATCH}")
#    set(CMAKE_BUNDLE_NAME "CMake ${CMAKE_BUNDLE_VERSION}")
#
#    set_target_properties(sfml_test PROPERTIES
#            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/mac/Info.plist"
#            MACOSX_BUNDLE_SHORT_VERSION_STRING "${CMAKE_BUNDLE_VERSION}"
#            MACOSX_BUNDLE_BUNDLE_VERSION "${CMAKE_BUNDLE_VERSION}"
#            MACOSX_BUNDLE_COPYRIGHT "Copyright © 2016. All rights reserved. Blah")
#
#    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
#    target_link_libraries(sfml_test ${COREFOUNDATION_LIBRARY})
#
#    add_custom_command(TARGET sfml_test COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/media ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Resources/media)
#else()
    add_custom_command(TARGET sfml_test COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/media $<TARGET_FILE_DIR:sfml_test>/media)
#endif()

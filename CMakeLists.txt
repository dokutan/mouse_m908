# SPDX-FileCopyrightText: 2021 George Florea Bănuș <georgefb899@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.15)

project(mouse_m908 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(GNUInstallDirs)
include(FeatureSummary)

find_package(LibUSB)
set_package_properties(LibUSB PROPERTIES TYPE REQUIRED)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

add_executable(mouse_m908)
target_sources(mouse_m908
    PRIVATE
        mouse_m908.cpp
        include/data.cpp
        include/help.h
        include/load_config.cpp
        include/load_config.h
        include/rd_mouse.cpp
        include/rd_mouse.h
        include/generic/constructor.cpp
        include/generic/data.cpp
        include/generic/getters.cpp
        include/generic/helpers.cpp
        include/generic/mouse_generic.h
        include/generic/readers.cpp
        include/generic/setters.cpp
        include/generic/writers.cpp
        include/m607/constructor.cpp
        include/m607/data.cpp
        include/m607/getters.cpp
        include/m607/helpers.cpp
        include/m607/mouse_m607.h
        include/m607/readers.cpp
        include/m607/setters.cpp
        include/m607/writers.cpp
        include/m709/constructor.cpp
        include/m709/data.cpp
        include/m709/getters.cpp
        include/m709/helpers.cpp
        include/m709/mouse_m709.h
        include/m709/readers.cpp
        include/m709/setters.cpp
        include/m709/writers.cpp
        include/m711/constructor.cpp
        include/m711/data.cpp
        include/m711/getters.cpp
        include/m711/helpers.cpp
        include/m711/mouse_m711.h
        include/m711/readers.cpp
        include/m711/setters.cpp
        include/m711/writers.cpp
        include/m715/constructor.cpp
        include/m715/data.cpp
        include/m715/getters.cpp
        include/m715/helpers.cpp
        include/m715/mouse_m715.h
        include/m715/readers.cpp
        include/m715/setters.cpp
        include/m715/writers.cpp
        include/m719/constructor.cpp
        include/m719/data.cpp
        include/m719/getters.cpp
        include/m719/helpers.cpp
        include/m719/mouse_m719.h
        include/m719/readers.cpp
        include/m719/setters.cpp
        include/m719/writers.cpp
        include/m721/constructor.cpp
        include/m721/data.cpp
        include/m721/getters.cpp
        include/m721/helpers.cpp
        include/m721/mouse_m721.h
        include/m721/readers.cpp
        include/m721/setters.cpp
        include/m721/writers.cpp
        include/m908/constructor.cpp
        include/m908/data.cpp
        include/m908/getters.cpp
        include/m908/helpers.cpp
        include/m908/mouse_m908.h
        include/m908/readers.cpp
        include/m908/setters.cpp
        include/m908/writers.cpp
        include/m913/constructor.cpp
        include/m913/data.cpp
        include/m913/getters.cpp
        include/m913/helpers.cpp
        include/m913/mouse_m913.h
        include/m913/readers.cpp
        include/m913/setters.cpp
        include/m913/writers.cpp
        include/m990/constructor.cpp
        include/m990/data.cpp
        include/m990/getters.cpp
        include/m990/helpers.cpp
        include/m990/mouse_m990.h
        include/m990/readers.cpp
        include/m990/setters.cpp
        include/m990/writers.cpp
        include/m990chroma/constructor.cpp
        include/m990chroma/data.cpp
        include/m990chroma/getters.cpp
        include/m990chroma/helpers.cpp
        include/m990chroma/mouse_m990chroma.h
        include/m990chroma/readers.cpp
        include/m990chroma/setters.cpp
        include/m990chroma/writers.cpp
)

target_link_libraries(mouse_m908 PRIVATE LibUSB::LibUSB)

install(TARGETS mouse_m908 DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES mouse_m908.rules DESTINATION ${CMAKE_INSTALL_FULL_SYSCONFDIR}/udev/rules.d)
install(FILES mouse_m908.1 DESTINATION ${CMAKE_INSTALL_MANDIR})
install(FILES README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(FILES keymap.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(DIRECTORY examples DESTINATION ${CMAKE_INSTALL_DOCDIR})

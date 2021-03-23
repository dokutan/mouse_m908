# SPDX-FileCopyrightText: 2006 Laurent Montel <montel@kde.org>
# SPDX-FileCopyrightText: 2019 Heiko Becker <heirecka@exherbo.org>
# SPDX-FileCopyrightText: 2020 Elvis Angelaccio <elvis.angelaccio@kde.org>
# SPDX-FileCopyrightText: 2021 George Florea Bănuș <georgefb899@gmail.com>
#
# SPDX-License-Identifier: BSD-3-Clause

find_package(PkgConfig QUIET)

pkg_check_modules(PC_USB QUIET libusb-1.0)

find_path(LibUSB_INCLUDE_DIRS
    NAMES libusb.h
    PATH_SUFFIXES libusb-1.0
    HINTS ${PC_USB_INCLUDEDIR}
)

find_library(LibUSB_LIBRARIES
    NAMES usb-1.0
    HINTS ${PC_USB_LIBDIR}
)

set(LibUSB_VERSION ${PC_USB_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibUSB
    FOUND_VAR
        LibUSB_FOUND
    REQUIRED_VARS
        LibUSB_LIBRARIES
        LibUSB_INCLUDE_DIRS
    VERSION_VAR
        LibUSB_VERSION
)

if (LibUSB_FOUND AND NOT TARGET LibUSB::LibUSB)
    add_library(LibUSB::LibUSB UNKNOWN IMPORTED)
    set_target_properties(LibUSB::LibUSB PROPERTIES
        IMPORTED_LOCATION "${LibUSB_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${LibUSB_INCLUDE_DIRS}"
    )
endif()

mark_as_advanced(LibUSB_LIBRARIES LibUSB_INCLUDE_DIRS)

include(FeatureSummary)
set_package_properties(LibUSB PROPERTIES
    URL "https://libusb.info"
    DESCRIPTION "a C library that provides generic access to USB devices."
)

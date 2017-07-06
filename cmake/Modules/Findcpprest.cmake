# - Finds Microsoft's cpprestsdk library
# https://github.com/Microsoft/cpprestsdk

# You can set PPLX_ROOT_DIR and CPPREST_ROOT_DIR optionally to specify where
# to look for both PPL tasks and the C++ Rest SDK

set(PPLX_ROOT_DIR
    "${PPLX_ROOT_DIR}"
    CACHE
    PATH
    "Path to search for pplx library")
set(CPPREST_ROOT_DIR
    "${CPPREST_ROOT_DIR}"
    CACHE
    PATH
    "Path to search for cpprestsdk library")

# pplx

find_path(PPLX_INCLUDE_DIR
    NAMES
    pplx/pplx.h
    HINTS
    "${PPLX_ROOT_DIR}"
    PATH_SUFFIXES
    include
    cpprest
    PATHS
    /usr/local
    /opt/local
    /sw)
mark_as_advanced(PPLX_INCLUDE_DIR)

# cpprest

find_path(CPPREST_INCLUDE_DIR
    NAMES
    version.h
    HINTS
    "${CPPREST_ROOT_DIR}"
    PATH_SUFFIXES
    include/cpprest
    cpprest
    PATHS
    /usr/local
    /opt/local
    /sw)
mark_as_advanced(CPPREST_INCLUDE_DIR)

# lib

find_library(CPPREST_LIBRARY
    NAMES
    cpprest
    HINTS
    "${CPPREST_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    lib64
    PATHS
    /usr/local
    /opt/local
    /sw)
mark_as_advanced(CPPREST_LIBRARY)

# standard args

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(cpprest
    DEFAULT_MSG
    CPPREST_LIBRARY
    CPPREST_INCLUDE_DIR
    PPLX_INCLUDE_DIR)

# set options

if (CPPREST_FOUND)
    # if cpprestsdk is found, the components for it are likely already
    # present, right?
    set(CPPREST_INCLUDE_DIRS "${PPLX_INCLUDE_DIR} ${CPPREST_INCLUDE_DIR}")
    set(CPPREST_LIBRARIES "${CPPREST_LIBRARY}")
endif()

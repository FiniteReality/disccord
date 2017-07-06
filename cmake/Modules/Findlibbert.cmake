# - Finds Rüdiger Sonderfel's libBERT library
# https://github.com/ruediger/libbert

# You can set BERT_ROOT_DIR optionally to specify where to look for libBERT.


set(BERT_ROOT_DIR
    "${BERT_ROOT_DIR}"
    CACHE
    PATH
    "Path to search for libBERT library")

find_path(BERT_INCLUDE_DIR
    NAMES
    bert.h
    HINTS
    "${BERT_ROOT_DIR}"
    PATH_SUFFIXES
    include
    bert
    PATH
    /usr/local
    /opt/local
    /sw)
mark_as_advanced(BERT_INCLUDE_DIR)

find_library(BERT_LIBRARY
    NAMES
    bert
    bert_capi
    HINTS
    "${BERT_ROOT_DIR}"
    PATH_SUFFIXES
    lib
    lib64
    PATHS
    /usr/local
    /opt/local
    /sw)
mark_as_advanced(BERT_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libbert
    DEFAULT_MSG
    BERT_LIBRARY
    BERT_INCLUDE_DIR)

if (LIBBERT_FOUND)
    set(BERT_INCLUDE_DIRS "${BERT_INCLUDE_DIR}")
    set(BERT_LIBRARIES "${BERT_LIBRARY}")
endif()

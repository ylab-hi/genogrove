set(CPM_DOWNLOAD_VERSION 0.40.2)
set(CPM_HASH SUM "c8cdc32c03816538ce22781ed72964dc864b2a34a310d3b7104812a5ca2d835d")

# download CPM.cmake
file(DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.2/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cpm/
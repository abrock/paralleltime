Project(ParallelTime CXX)

set(header_path ${ParallelTime_SOURCE_DIR})

set(header ${header_path}/header-a.hpp)

if (NOT TARGET ParallelTime)
add_library(ParallelTime paralleltime.cpp)
endif()

install(TARGETS ParallelTime LIBRARY ARCHIVE DESTINATION "lib/")
install(FILES paralleltime.h DESTINATION "include/ParallelTime/")

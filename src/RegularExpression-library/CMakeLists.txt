project(RegularExpression-library)

set(source-files "${PROJECT_SOURCE_DIR}/RegularExpression.cpp" CACHE INTERNAL "")

add_library(
        RegularExpression-library SHARED ${source-files} ${Testing_SOURCE_DIR}/include/RegularExpression.h
)

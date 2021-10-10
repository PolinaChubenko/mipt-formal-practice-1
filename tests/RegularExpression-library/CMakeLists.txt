set(TARGET_NAME "RegularExpression-library")
set(COVERAGE_NAME "coverage")
set(COVERAGE_TARGET "coverage-RegularExpression-library")
set(SOURCE_DIR_MAIN "${RegularExpression-library_SOURCE_DIR}")
set(SOURCES ${source-files})

message(INFO ${SOURCES})

set(TEST_SOURCES RegularExpressionTestCase.h RegularExpressionTestCase.cpp
        RegularExpressionMock.h RegularExpressionMock.cpp)
run_coverage(
        "${TEST_SOURCES}"
        "${SOURCES}"
        "${COVERAGE_TARGET}"
        "${TARGET_NAME}"
        "${COVERAGE_NAME}"
)

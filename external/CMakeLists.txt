
include(FetchContent)

FetchContent_Declare (
    tracy
    GIT_REPOSITORY https://github.com/wolfpld/tracy.git
    GIT_TAG v0.11.1
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

set(TRACY_ENABLE OFF)
set(TRACY_ON_DEMAND ON)

FetchContent_MakeAvailable(tracy)

cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Task_1")

set(exe ${PROJECT_NAME})
set(output ${PROJECT_SOURCE_DIR}/output)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${output})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output})

add_executable (${exe} "Main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${exe} PROPERTY CXX_STANDARD 14)
endif()

set(lib c_string_list)
add_library(${lib} STATIC "List.cpp")
target_link_libraries(${exe} ${lib})

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
enable_testing()
add_executable(lib_test Test.cpp)
target_link_libraries(lib_test ${lib} gtest_main)
add_test(NAME String_list_test COMMAND lib_test)
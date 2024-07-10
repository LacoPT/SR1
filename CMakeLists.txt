cmake_minimum_required (VERSION 3.8)
# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(PROJECT_VERSION 0.1)


project ("SR1" VERSION ${PROJECT_VERSION})

find_package(Boost COMPONENTS unit_test_framework REQIRED)

add_executable(helloworldcli main.cpp)
add_library(helloworld lib.cpp)
add_executable(test_version test_version.cpp)


set_target_properties(helloworldcli helloworld test_version PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworld PRIVATE "${CMAKE_BINARY_DIR}")

target_link_libraries(helloworldcli PRIVATE helloworld)

install(TARGETS helloworldcli RUNTIME DESTINATION bin)


enable_testing()

add_test(test_version test_version)


#configure_file(version.h.in version.h)

cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)


#set (BOOST_ROOT "C:/libraries/boost_1_82_0")


project ("SR1" VERSION ${PROJECT_VERSION})
 
find_package(Boost REQUIRED COMPONENTS unit_test_framework REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})

configure_file(version.h version.h)

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

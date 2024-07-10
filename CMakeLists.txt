cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


project ("SR1" VERSION ${PROJECT_VERSION})

find_package(Boost COMPONENTS unit_test_framework REQIRED)

add_executable(helloworldcli main.cpp)
add_library(helloworld lib.cpp)
add_executable(test_version test_version.cpp)

#configure_file(version.h.in version.h)

cmake_minimum_required (VERSION 3.8)


# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project ("SR1" VERSION ${PROJECT_VERSION})


#set (BOOST_ROOT "C:/local/boost_1_85_0/")
#SET (BOOST_INCLUDEDIR "C:/local/boost_1_85_0/boost")
#SET (BOOST_LIBRARYDIR "C:/local/boost_1_85_0/stage/lib")

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
 
find_package(Boost REQUIRED COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

configure_file(version.h version.h)

add_executable(helloworldcli main.cpp)
add_library(helloworld lib.cpp)


add_executable(test_version test_version.cpp)
set_target_properties(test_version PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_NO_LIB)
target_include_directories(test_version PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    helloworld)



set_target_properties(helloworldcli helloworld test_version PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworld PRIVATE "${CMAKE_BINARY_DIR}")

target_link_libraries(helloworldcli PRIVATE helloworld)



install(TARGETS helloworldcli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "LacoPT")

include(CPack)



enable_testing()

add_test(test_version test_version)



#configure_file(version.h.in version.h)

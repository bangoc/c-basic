project(c-basic)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

add_library(bkc STATIC double_linked_list.c)

add_subdirectory(tests)

include(CTest)

add_test(NAME DoubleLinkedListGenericAPIs COMMAND dll_generic_apis_ut)
add_test(NAME DoubleLinkedListIntAPIs COMMAND dll_int_apis_ut)


project(thirdparty)

add_library(thirdparty INTERFACE)

set(DIR_FILES)
set(DIR_LIST)

file(GLOB DIR_FILES LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

message(${CMAKE_CURRENT_SOURCE_DIR})
foreach(FILE_NAME ${DIR_FILES})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME})
        list(APPEND DIR_LIST ${FILE_NAME})
    endif()
endforeach()

target_include_directories(thirdparty
    INTERFACE ${DIR_LIST}
)

project(net)

file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS *.cpp )
file(GLOB_RECURSE INCLUDE CONFIGURE_DEPENDS *.h *.hpp)

add_library(net)

target_sources(net
PRIVATE ${SOURCE} ${INCLUDE})

target_link_libraries(net 
    PUBLIC thirdparty
)

target_include_directories(net
    PUBLIC ..
)
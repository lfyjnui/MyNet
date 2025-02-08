

file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS *.cpp )
file(GLOB_RECURSE INCLUDE CONFIGURE_DEPENDS *.h *.hpp)

add_executable(server)

target_sources(server
PRIVATE
    ${SOURCE}
    ${INCLUDE}
)

target_link_libraries(server PRIVATE net)
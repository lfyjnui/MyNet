

file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS *.cpp )
file(GLOB_RECURSE INCLUDE CONFIGURE_DEPENDS *.h *.hpp)

add_executable(client)


target_sources(client
PRIVATE
    ${SOURCE}
    ${INCLUDE}
)

target_link_libraries(client PRIVATE net)

target_include_directories(client
PRIVATE
    ../third_party
    ../third_party/asio/
)

file(GLOB_RECURSE SOURCES "*.c")
#file(GLOB_RECURSE COMPONENTS "./../components/*.c")


idf_component_register(SRCS ${SOURCES} #${COMPONENTS}
                       INCLUDE_DIRS "."
                                    )

set(COMPONENT_ADD_INCLUDEDIRS .)
file(GLOB SRC_FILES "*.c")
set(COMPONENT_SRCS ${SRC_FILES})
set(COMPONENT_REQUIRES 
	spidriver
)

register_component()

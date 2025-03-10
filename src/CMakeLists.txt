set(SRC main.cpp
	file_handler.cpp
)

set(HEADER
	include/array_factory.h
	include/array_transformer.h
	include/array_utils.h
	include/file_arrays.h
	include/file_handler.h
	include/type_handler.h
)

add_executable(Source ${SRC} ${HEADER})

target_include_directories(Source PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

source_group("Header Files" FILES ${HEADER})
source_group("Source Files" FILES ${SRC})


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/input.txt ${CMAKE_BINARY_DIR}/src/data/input.txt COPYONLY)

project(lexilla)

file(GLOB LIBLEXILLA_SRC 
	"src/*.cxx" 
	"lexlib/*.cxx" 
	"lexers/*.cxx"
)

add_library(${PROJECT_NAME} ${LIBLEXILLA_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC 
	${PROJECT_SOURCE_DIR} 
	${PROJECT_SOURCE_DIR}/src 
	${PROJECT_SOURCE_DIR}/lexlib
	${PROJECT_SOURCE_DIR}/lexers
	${PROJECT_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/scintilla/include
)

# set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")  

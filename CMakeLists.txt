cmake_minimum_required(VERSION 3.5)
project(Pacman CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB SRC_LIST
        "src/*.hpp"
        "src/*.cpp"
        )

# SOIL ########################################################################
IF (SOIL_INCLUDE_DIR)
    # Already in cache, be silent
    SET(SOIL_FIND_QUIETLY TRUE)
ENDIF (SOIL_INCLUDE_DIR)

FIND_PATH(SOIL_INCLUDE_DIR SOIL.h PATH_SUFFIXES include/SOIL include)

SET(SOIL_NAMES SOIL Soil soil)
FIND_LIBRARY(SOIL_LIBRARY NAMES ${SOIL_NAMES} )
MARK_AS_ADVANCED( SOIL_LIBRARY SOIL_INCLUDE_DIR )

# Per-recommendation
SET(SOIL_INCLUDE_DIRS "${SOIL_INCLUDE_DIR}")
SET(SOIL_LIBRARIES    "${SOIL_LIBRARY}")

# handle the QUIETLY and REQUIRED arguments and set SOIL_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SOIL DEFAULT_MSG SOIL_LIBRARIES
    SOIL_INCLUDE_DIRS)

include_directories(${SOIL_INCLUDE_DIRS})
link_libraries(${SOIL_LIBRARIES})
###############################################################################

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries( ${PROJECT_NAME} ${OPENGL_LIBRARIES} )
target_link_libraries( ${PROJECT_NAME} ${GLUT_LIBRARY} )

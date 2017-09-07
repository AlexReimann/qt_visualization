##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(qt_visualization)

##############################################################################
# Dependencies
##############################################################################

find_package(catkin REQUIRED
                plane_calibration
                qglv_extras
                qglv_opengl
                cmake_modules
)

set(QT_INCLUDE_DIRS_NO_SYSTEM TRUE)
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

find_package(Eigen REQUIRED)

##############################################################################
# Catkin
##############################################################################

# Because it does not set an xxxx_INCLUDE_DIRS...
# Note : do not use QT_INCLUDE_DIR - that is only /usr/include/qt4 whereas
#        QT_INCLUDES brings in all the required components
set(QT_INCLUDE_DIRS ${QT_INCLUDES})

catkin_package(
    INCLUDE_DIRS
        include
    LIBRARIES
        ${PROJECT_NAME}
    CATKIN_DEPENDS
        plane_calibration
        qglv_extras
        qglv_opengl
    DEPENDS
        QT
        Eigen
)

##############################################################################
# Project Configuration
##############################################################################

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
add_definitions(${catkin_DEFINITIONS})
include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${QT_INCLUDES}    # list of escaped QtCore, ... subdirs.
        ${QT_INCLUDE_DIR} # the root level qt4 dir
        ${EIGEN_INCLUDE_DIRS}
)
add_definitions(${EIGEN_DEFINITIONS})

##############################################################################
# Subdirectories includes
##############################################################################

add_subdirectory(src)

##############################################################################
# Installs
##############################################################################
install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

install(DIRECTORY ui DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

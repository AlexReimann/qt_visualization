##############################################################################
# Qt
##############################################################################

qt4_wrap_cpp(QT_CUSTOM_WRAP
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/plane_calibration_qgl.hpp
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/plane_calibration_ui.hpp
)

qt4_wrap_ui(UI_INTERFACE_SOURCES
    ${PROJECT_SOURCE_DIR}/ui/plane_calibration.ui
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})  # this is where ui headers are dropped.

###############################################################################
# Applications
###############################################################################

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") #for multithreading

add_executable(plane_calibration_view
    ${QT_CUSTOM_WRAP}
    ${UI_INTERFACE_SOURCES}
    plane_calibration_view.cpp
    plane_calibration_ui.cpp
    plane_calibration_qgl.cpp
)

target_link_libraries(plane_calibration_view
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${QT_LIBRARIES}
)
install(TARGETS plane_calibration_view RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

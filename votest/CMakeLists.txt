cmake_minimum_required(VERSION 2.8.3)
project(votest)
set( CMAKE_CXX_FLAGS "-std=c++11" )
## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  image_transport 
  cv_bridge
  Eigen3
)

find_package( G2O REQUIRED )
include_directories(
  include ${catkin_INCLUDE_DIRS} ${G2O_INCLUDE_DIRS} )

find_package( CSparse REQUIRED )
include_directories( ${CSPARSE_INCLUDE_DIR} )

# eigen 
include_directories( "/usr/include/eigen3/" )
# opencv 
find_package(OpenCV 3.2.0 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
# pcl 
find_package( PCL REQUIRED COMPONENT common io )
include_directories( ${PCL_INCLUDE_DIRS} )
add_definitions( ${PCL_DEFINITIONS} )

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES votest
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include ${catkin_INCLUDE_DIRS}
    ${G2O_INCLUDE_DIRS}
    ${CSPARSE_INCLUDE_DIR}
  
)

   



add_executable(cam_pub
  src/cam_pub.cpp
)
add_dependencies(cam_pub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(cam_pub
  ${catkin_LIBRARIES} ${OpenCV_LIBRARIES}
)

add_executable(cam_sub
  src/cam_sub.cpp
)
add_dependencies(cam_sub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(cam_sub
  ${catkin_LIBRARIES} ${OpenCV_LIBRARIES}
)

add_executable(image
  src/image.cpp
)
add_dependencies(image ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(image
  ${catkin_LIBRARIES} ${OpenCV_LIBRARIES}
)

add_executable(pj
  src/pj.cpp
)
add_dependencies(pj ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(pj
  ${catkin_LIBRARIES} ${OpenCV_LIBS} ${PCL_LIBRARIES}
)

add_executable(depth
  src/depth.cpp
)
add_dependencies(depth ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(depth
  ${catkin_LIBRARIES} ${OpenCV_LIBS}
)


add_executable(pose_2d_2d
  src/pose_2d_2d.cpp
)
add_dependencies(pose_2d_2d ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(pose_2d_2d
  ${catkin_LIBRARIES} ${OpenCV_LIBS}
)

add_executable(epnp_ba
  src/epnp_ba.cpp
)
add_dependencies(epnp_ba ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(epnp_ba
  ${OpenCV_LIBS}
   ${CSPARSE_LIBRARY}
   g2o_core g2o_stuff g2o_types_sba g2o_csparse_extension
)

add_executable(fast
  src/fast.cpp
)
add_dependencies(fast ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(fast
  ${catkin_LIBRARIES} ${OpenCV_LIBS}
)
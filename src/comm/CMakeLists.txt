cmake_minimum_required(VERSION 3.5)
project(comm)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

ament_export_dependencies(rosidl_default_runtime)
ament_export_include_directories(include)

# for including pub.hpp and sub.hpp
include_directories(include)

add_executable(publisher src/pub_impl.cpp src/pub_main.cpp)
ament_target_dependencies(publisher rclcpp std_msgs)

add_executable(subscriber src/sub_impl.cpp src/sub_main.cpp)
ament_target_dependencies(subscriber rclcpp std_msgs)

add_executable(pubsub src/pointer_passing.cpp src/pub_impl.cpp src/sub_impl.cpp)
ament_target_dependencies(pubsub rclcpp std_msgs)

set(msg_files "msg/StampedBin.msg")

rosidl_generate_interfaces(
  ${PROJECT_NAME} ${msg_files}
  DEPENDENCIES std_msgs)

rosidl_target_interfaces(
  publisher
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

rosidl_target_interfaces(
  subscriber
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

rosidl_target_interfaces(
  pubsub
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

install(TARGETS
  publisher
  subscriber
  pubsub
  DESTINATION lib/${PROJECT_NAME})

ament_package()

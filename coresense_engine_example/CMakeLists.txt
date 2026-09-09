cmake_minimum_required(VERSION 3.20)
project(coresense_engine_example)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(behaviortree_cpp REQUIRED)
find_package(behaviortree_ros2 REQUIRED)
find_package(btcpp_ros2_interfaces REQUIRED)
find_package(coresense_msgs REQUIRED)
find_package(coresense_example_msgs REQUIRED)

set(DEPENDENCIES
  coresense_msgs
  coresense_example_msgs
  behaviortree_ros2
  behaviortree_cpp
  btcpp_ros2_interfaces
  #std_msgs
  #std_srvs
  #nav2_msgs
  #decision_msgs
  #rclcpp
)

add_library(example_service SHARED src/example_service.cpp)
target_include_directories(example_service PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
ament_target_dependencies(example_service ${DEPENDENCIES})

add_library(example_action_plugin SHARED src/bt_example_action.cpp)
target_include_directories(example_action_plugin PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_compile_definitions(example_action_plugin PRIVATE BT_PLUGIN_EXPORT)
ament_target_dependencies(example_action_plugin ${DEPENDENCIES})


add_library(example_service_plugin SHARED src/bt_example_service.cpp)
target_include_directories(example_service_plugin PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_compile_definitions(example_service_plugin PRIVATE BT_PLUGIN_EXPORT)
ament_target_dependencies(example_service_plugin ${DEPENDENCIES})


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


### Install targets and directories
install(TARGETS
  example_service
  #  example_action_plugin
  #  example_service_plugin
  DESTINATION lib/${PROJECT_NAME}
)

# Install plugins for other packages to load# Install plugins for other packages to load
install(TARGETS
  example_action_plugin
  example_service_plugin
  LIBRARY DESTINATION share/${PROJECT_NAME}/bt_plugins
  ARCHIVE DESTINATION share/${PROJECT_NAME}/bt_plugins
  RUNTIME DESTINATION share/${PROJECT_NAME}/bt_plugins
)

# Install headers for plugins
install(DIRECTORY
  include/
  DESTINATION include
)

# Export plugin dependencies for downstream packages
ament_export_dependencies(${DEPENDENCIES})
ament_export_include_directories(
  include
)

ament_package()

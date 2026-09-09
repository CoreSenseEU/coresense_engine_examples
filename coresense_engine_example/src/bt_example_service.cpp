#include "behaviortree_ros2/plugins.hpp"

#include "coresense_engine_example/bt_example_service.hpp"

bool ExampleService::setRequest(Request::SharedPtr& request)
{
  getInput("some_input_name", request->input);
  std::cout << "setRequest " << std::endl;
  return true;
}


BT::NodeStatus ExampleService::onFailure(BT::ServiceNodeErrorCode error)
{
  RCLCPP_ERROR(logger(), "Error: %d", error);
  return BT::NodeStatus::FAILURE;
}

BT::NodeStatus ExampleService::onResponseReceived(const Response::SharedPtr& response) {
  setOutput("some_output_name", response->result);
  return BT::NodeStatus::SUCCESS;
}
//-----------------------------------------------------------

CreateRosNodePlugin(ExampleService, "ExampleService");

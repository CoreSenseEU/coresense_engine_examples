#include "bt_example_service.hpp"

bool ExampleService::setRequest(Request::SharedPtr& request)
{
  getInput("ExampleServicePort1", request->data);
  std::cout << "setRequest " << std::endl;
  return true;
}

BT::NodeStatus ExampleService::onResponseReceived(const Response::SharedPtr& response)
{
  std::cout << "onResponseReceived " << std::endl;
  if(response->success)
  {
    RCLCPP_INFO(logger(), "example service succeeded.");
    return BT::NodeStatus::SUCCESS;
  }
  else
  {
    RCLCPP_INFO(logger(), "example service failed: %s", response->message.c_str());
    return BT::NodeStatus::FAILURE;
  }
}

BT::NodeStatus ExampleService::onFailure(BT::ServiceNodeErrorCode error)
{
  RCLCPP_ERROR(logger(), "Error: %d", error);
  return BT::NodeStatus::FAILURE;
}

//-----------------------------------------------------------

BT::NodeStatus ExampleRobotService::tick()
{
  std::string robot;
  if(getInput("robot", robot) && !robot.empty())
  {
    setServiceName(robot + "/" + service_suffix_);
  }
  return ExampleRobotService::tick();
}

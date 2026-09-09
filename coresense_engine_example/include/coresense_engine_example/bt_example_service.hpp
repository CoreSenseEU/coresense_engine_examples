#pragma once

#include <behaviortree_ros2/bt_service_node.hpp>
#include "coresense_example_msgs/srv/example_service.hpp"
#include "coresense_example_msgs/msg/example_service_input.hpp"
#include "coresense_example_msgs/msg/example_service_output.hpp"

//using coresense_example_msgs::srv::ExampleService = std_srvs::srv::coresense_example_msgs::srv::ExampleService;

class ExampleService : public BT::RosServiceNode<coresense_example_msgs::srv::ExampleService>
{
public:
  explicit ExampleService(const std::string& name, const BT::NodeConfig& conf,
                          const BT::RosNodeParams& params)
    : RosServiceNode<coresense_example_msgs::srv::ExampleService>(name, conf, params)
  {}

  static BT::PortsList providedPorts()
  {
    return providedBasicPorts({ 
      BT::InputPort<coresense_example_msgs::msg::ExampleServiceInput>("some_input_name"),
      BT::OutputPort<coresense_example_msgs::msg::ExampleServiceOutput>("some_output_name")
    });
  }

  bool setRequest(Request::SharedPtr& request) override;

  BT::NodeStatus onResponseReceived(const Response::SharedPtr& response) override;

  virtual BT::NodeStatus onFailure(BT::ServiceNodeErrorCode error) override;

private:
  std::string service_suffix_;
};

//----------------------------------------------


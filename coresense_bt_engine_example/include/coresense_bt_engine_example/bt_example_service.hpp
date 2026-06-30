#pragma once

#include <behaviortree_ros2/bt_service_node.hpp>
#include "coresense_example_msgs/srv/ExampleService.hpp"

using coresense_example_msgs::srv::ExampleService = std_srvs::srv::coresense_example_msgs::srv::ExampleService;

class ExampleService : public BT::RosServiceNode<coresense_example_msgs::srv::ExampleService>
{
public:
  explicit ExampleService(const std::string& name, const BT::NodeConfig& conf,
                          const BT::RosNodeParams& params)
    : RosServiceNode<coresense_example_msgs::srv::ExampleService>(name, conf, params)
  {}

  static BT::PortsList providedPorts()
  {
    return providedBasicPorts({ BT::InputPort<coresense_example_msgs::msg::ExampleServiceInputPort1>("port1") });
  }

  bool setRequest(Request::SharedPtr& request) override;

  BT::NodeStatus onResponseReceived(const Response::SharedPtr& response) override;

  virtual BT::NodeStatus onFailure(BT::ServiceNodeErrorCode error) override;

private:
  std::string service_suffix_;
};

//----------------------------------------------

class RobotExampleService : public ExampleService
{
public:
  explicit RobotExampleService(const std::string& name, const BT::NodeConfig& conf,
                               const rclcpp::Node::SharedPtr& node,
                               const std::string& port_name)
    : ExampleService(name, conf, BT::RosNodeParams(node)), service_suffix_(port_name)
  {}

  static BT::PortsList providedPorts()
  {
    return { BT::InputPort<std::string>("robot"), BT::InputPort<coresense_example_msgs::srv::ExampleServiceInputPort1>("port1") };
  }

  BT::NodeStatus tick() override;

private:
  std::string service_suffix_;
};

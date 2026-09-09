#include "behaviortree_ros2/plugins.hpp"

#include "coresense_engine_example/bt_example_action.hpp"


bool ExampleAction::setGoal(ExampleAction::Goal& goal)
{
  // TODO: abstract away this call so that code isn't copied
  if (!getInput<coresense_example_msgs::msg::ExampleActionInput>("some_input_name", goal.input))
  {
    RCLCPP_ERROR(logger(), "%s: setGoal with error: no blackboard entry for {%s}", 
        name().c_str(), "some_input_name");
    return false;

  }

  return true;
}


BT::NodeStatus ExampleAction::onResultReceived(const WrappedResult& wr)
{
  coresense_example_msgs::msg::ExampleActionOutput output;
  output = wr.result->result;

  setOutput<coresense_example_msgs::msg::ExampleActionOutput>("some_output_name", output);
  return BT::NodeStatus::SUCCESS;
}


BT::NodeStatus ExampleAction::onFeedback(const std::shared_ptr<const Feedback> feedback)
{
  RCLCPP_INFO(logger(), "%s: onFeedback: %s alternatives taken",
      name().c_str(), 
      feedback->status.c_str());
  return BT::NodeStatus::RUNNING;
}


BT::NodeStatus ExampleAction::onFailure(BT::ActionNodeErrorCode error)
{
  RCLCPP_ERROR(logger(), "%s: onFailure with error: %s", name().c_str(), toStr(error));
  return BT::NodeStatus::FAILURE;
}


void ExampleAction::onHalt()
{
  RCLCPP_WARN(logger(), "%s: onHalt with warning: goal was cancelled", name().c_str());
}

// Register this node as a plugin with the BT factory
CreateRosNodePlugin(ExampleAction, "ExampleAction");

#ifndef CS_BT_CPP__EXAMPLE_ACTION_HPP_
#define CS_BT_CPP__EXAMPLE_ACTION_HPP_

#include <behaviortree_ros2/bt_action_node.hpp>
#include <coresense_example_msgs/action/example_action.hpp>
#include "coresense_example_msgs/msg/example_action_input.hpp"
#include <coresense_example_msgs/msg/example_action_output.hpp>
#include <string>



class ExampleAction : public BT::RosActionNode<coresense_example_msgs::action::ExampleAction>
{
public:
  explicit ExampleAction(const std::string& name, const BT::NodeConfig& config,
               const BT::RosNodeParams& params)
    : BT::RosActionNode<coresense_example_msgs::action::ExampleAction>(name, config, params)
  {}

  /**
   * @brief Required method that creates list of BT ports
   *
   * Must call providedBasicPorts in it.
   *
   * @return PortsList Containing basic ports along with node-specific ports
   */
  static BT::PortsList providedPorts()
  {    
    return providedBasicPorts({ 
        BT::InputPort<coresense_example_msgs::msg::ExampleActionInput>(
            "some_input_name",
            "The first input of the action."),
        BT::OutputPort<coresense_example_msgs::msg::ExampleActionOutput>(
            "some_output_name",
            "The result of the action"),
        });
  }

  /** 
   * @brief Required callback that allows the user to set the goal message.
   *
   * @param goal The goal to be sent to the action server.
   *
   * @return false if the request should not be sent. In that case,
   * RosActionNode::onFailure(INVALID_GOAL) will be called.
   */
  bool setGoal(Goal& goal) override;

  /** 
   * @brief Required callback invoked when the result is received by the server.
   * 
   * It is up to the user to define if the action returns SUCCESS or FAILURE.
   */
  BT::NodeStatus onResultReceived(const WrappedResult& wr) override;

  /** 
   * @brief Optional callback invoked when the feedback is received.
   * 
   * It generally returns RUNNING, but the user can also use this callback to cancel the
   * current action and return SUCCESS or FAILURE.
   */
  BT::NodeStatus onFeedback(const std::shared_ptr<const Feedback> feedback) override;

  /**
   * @brief Optional callback invoked when something goes wrong. 
   *
   * It must return either SUCCESS or FAILURE.
   */
  BT::NodeStatus onFailure(BT::ActionNodeErrorCode error) override;

  /**
   * @brief Optional callback executed when the node is halted. 
   *
   * Note that cancelGoal() is done automatically.
   */
  void onHalt() override;

};

#endif

#include <memory>

#include "coresense_example_msgs/srv/example_service.hpp"
#include "rclcpp/rclcpp.hpp"

using ExampleService = coresense_example_msgs::srv::ExampleService;
rclcpp::Node::SharedPtr g_node = nullptr;

void handle_service(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<ExampleService::Request> request,
  const std::shared_ptr<ExampleService::Response> response)
{
  (void)request_header;
  response->result = request->input;
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  g_node = rclcpp::Node::make_shared("coresense_example_service");
  auto server = g_node->create_service<ExampleService>("/coresense/engines/example", handle_service);
  rclcpp::spin(g_node);
  rclcpp::shutdown();
  g_node = nullptr;
  return 0;
}

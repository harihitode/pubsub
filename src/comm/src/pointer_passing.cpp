#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "comm/pub.hpp"
#include "comm/sub.hpp"

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor executor;

  auto pub = std::make_shared<snippet_comm::Publisher>("publisher", "blob", true);
  auto sub = std::make_shared<snippet_comm::Subscriber>("subscriber", "blob", true);

  executor.add_node(sub);
  executor.add_node(pub);

  rclcpp::shutdown();
  return 0;
}

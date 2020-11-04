#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "comm/sub.hpp"

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<snippet_comm::Subscriber>("subscriber", "blob", false));
  rclcpp::shutdown();
  return 0;
}

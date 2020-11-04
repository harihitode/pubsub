#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "comm/pub.hpp"

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<snippet_comm::Publisher>("publisher", "blob", false));
  rclcpp::shutdown();

  return 0;
}

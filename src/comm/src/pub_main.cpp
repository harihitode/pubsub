#include <memory>
#include <csignal>

#include "rclcpp/rclcpp.hpp"
#include "comm/pub.hpp"

void sigint_handler(int) {
  rclcpp::shutdown();
}

int main(int argc, char * argv[]) {
  signal(SIGINT, sigint_handler);

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<snippet_comm::Publisher>("publisher", "blob", false));
  rclcpp::shutdown();

  return 0;
}

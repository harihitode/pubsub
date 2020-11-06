#include <memory>
#include <thread>
#include <csignal>

#include "rclcpp/rclcpp.hpp"
#include "comm/pub.hpp"

void sigint_handler(int) {
  rclcpp::shutdown();
}

int main(int argc, char * argv[]) {
  signal(SIGINT, sigint_handler);

  rclcpp::init(argc, argv);
  auto pub = std::make_shared<snippet_comm::Publisher>("publisher", "blob", false);
  std::thread publish_thread([&pub] {
      pub->publish_loop(1000);
      std::cerr << "finish" << std::endl;
    });
  rclcpp::spin(pub);
  publish_thread.join();
  rclcpp::shutdown();

  return 0;
}

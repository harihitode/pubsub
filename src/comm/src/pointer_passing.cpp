#include <memory>
#include <thread>
#include <csignal>

#include "rclcpp/rclcpp.hpp"
#include "comm/pub.hpp"
#include "comm/sub.hpp"

void sigint_handler(int) {
  rclcpp::shutdown();
}

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor executor;

  auto pub = std::make_shared<snippet_comm::Publisher>("publisher", "blob", true);
  auto sub = std::make_shared<snippet_comm::Subscriber>("subscriber", "blob", true);
  executor.add_node(sub);
  executor.add_node(pub);
  std::thread publish_thread([&pub] {
      pub->publish_loop(1000);
      std::cerr << "finish" << std::endl;
    });
  executor.spin();
  publish_thread.join();
  rclcpp::shutdown();
  return 0;
}

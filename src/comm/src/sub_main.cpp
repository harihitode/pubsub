#include <memory>
#include <thread>
#include <csignal>

#include "rclcpp/rclcpp.hpp"
#include "comm/sub.hpp"

void sigint_handler(int) {
  rclcpp::shutdown();
}

int main(int argc, char * argv[]) {
  signal(SIGINT, sigint_handler);

  rclcpp::init(argc, argv);
  auto sub = std::make_shared<snippet_comm::Subscriber>("subscriber", "blob", false);
  // std::thread request_thread([&sub] {
  //     sub->request_publish(100);
  //   });
  rclcpp::spin(sub);
  // request_thread.join();
  rclcpp::shutdown();

  return 0;
}

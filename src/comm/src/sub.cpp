#include <chrono>
#include <memory>
#include <cstdint>

#include "rclcpp/rclcpp.hpp"
#include "comm/msg/stamped_bin.hpp"

using namespace std::chrono;
using namespace std::chrono_literals;
using std::placeholders::_1;

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TheSubscriber>());
  return 0;
}

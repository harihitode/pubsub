#include <chrono>
#include <functional>
#include <memory>
#include <cstdlib>
#include <cstdint>

#include "rclcpp/rclcpp.hpp"
#include "comm/pub.hpp"
#include "comm/msg/stamped_bin.hpp"

using namespace std::chrono;
using namespace std::chrono_literals;

const size_t data_size = 80;

namespace snippet_comm {
  ThePublisher::
  ThePublisher() : Node("the_publisher") {
    publisher_ = this->create_publisher<comm::msg::StampedBin>("topic", 10);
    timer_ = this->create_wall_timer(500ms,
                                     std::bind(&ThePublisher::timer_callback, this));
    message_ = comm::msg::StampedBin();
    message_.data.data.clear();
    for (size_t i = 0; i < data_size; i++) {
      message_.data.data.push_back(uint8_t(rand() % 100));
    }
  }

  void ThePublisher::
  timer_callback()  {
    const high_resolution_clock::time_point time_published = high_resolution_clock::now();
    const nanoseconds nsec = duration_cast<nanoseconds>(time_published.time_since_epoch());
    message_.stamp = nsec.count();
    publisher_->publish(message_);
  }
}

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<snippet_comm::ThePublisher>());
  rclcpp::shutdown();
  return 0;
}

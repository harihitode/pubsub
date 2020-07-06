#include <chrono>
#include <functional>
#include <cstdlib>
#include <cstdint>

#include "comm/pub.hpp"
#include "comm/msg/stamped_bin.hpp"

using namespace std::chrono;
using namespace std::chrono_literals;

namespace snippet_comm {
  Publisher::
  Publisher(const std::string & name, const std::string & output,
            bool intra_process, size_t blob_size)
    : Node(name, rclcpp::NodeOptions().use_intra_process_comms(intra_process)), blob_size_(blob_size) {
    publisher_ = this->create_publisher<comm::msg::StampedBin>(output, 10);
    timer_ = this->create_wall_timer(500ms,
                                     std::bind(&Publisher::timer_callback, this));
  }

  void Publisher::
  timer_callback()  {
    auto pub_ptr = publisher_;
    if (!pub_ptr) {
      return;
    }
    comm::msg::StampedBin::UniquePtr msg(new comm::msg::StampedBin());
    msg->data.data.resize(blob_size_);
    for (size_t i = 0; i < blob_size_; i++) {
      msg->data.data[i] = uint8_t(rand() % 100);
    }
    const high_resolution_clock::time_point time_published = high_resolution_clock::now();
    const nanoseconds nsec = duration_cast<nanoseconds>(time_published.time_since_epoch());
    msg->stamp = nsec.count();
    pub_ptr->publish(std::move(msg));
  }
}

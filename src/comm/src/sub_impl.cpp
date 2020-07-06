#include <chrono>
#include <memory>
#include <cstdint>

#include "comm/sub.hpp"
#include "comm/msg/stamped_bin.hpp"

using namespace std::chrono;
using namespace std::chrono_literals;

namespace snippet_comm {
  Subscriber::
  Subscriber(const std::string & name, const std::string & input,
             bool intra_process, size_t blob_size) :
    Node(name, rclcpp::NodeOptions().use_intra_process_comms(intra_process)), blob_size_(blob_size) {
    subscriber_ = this->
      create_subscription<comm::msg::StampedBin>(input, 10,
                                                 std::bind(&Subscriber::topic_callback, this, std::placeholders::_1));
  }

  void Subscriber::
  topic_callback(const comm::msg::StampedBin::UniquePtr msg) const {
    const high_resolution_clock::time_point time_subscribed = high_resolution_clock::now();
    const uint64_t end = duration_cast<nanoseconds>(time_subscribed.time_since_epoch()).count();
    const uint64_t begin = msg->stamp;
    RCLCPP_INFO(this->get_logger(), "Latency; '%llu'", end - begin);
  }
}

#include <chrono>
#include <memory>
#include <cstdint>

#include "comm/sub.hpp"

using namespace std::chrono;
using namespace std::chrono_literals;

namespace snippet_comm {
  Subscriber::Subscriber(const std::string & name, const std::string & input, bool intra_process) :
    Node(name, rclcpp::NodeOptions().use_intra_process_comms(intra_process)) {
    // data size in message
    this->declare_parameter("blob_size", 1000);
    blob_size_ = this->get_parameter("blob_size").as_int();
    using std::placeholders::_1;
    subscriber_ = this->
      create_subscription<comm::msg::StampedBin>(input, 1,
                                                 std::bind(&Subscriber::topic_callback, this, _1));
  }

  void Subscriber::request_publish(int64_t count) {
    // waiting the service
    auto client = this->create_client<comm::srv::PublishLoop>("publish_loop");

    while (!client->wait_for_service(1s)) {
      if (!rclcpp::ok()) {
        return;
      }
    }
    auto request = std::make_shared<comm::srv::PublishLoop::Request>();
    request->count = count;

    auto result = client->async_send_request(request);
    result.wait(); // block the shared_future
    return;
  }

  void Subscriber::topic_callback(const comm::msg::StampedBin::UniquePtr msg) const {
    const high_resolution_clock::time_point time_subscribed = high_resolution_clock::now();
    const uint64_t end = duration_cast<nanoseconds>(time_subscribed.time_since_epoch()).count();
    const uint64_t begin = msg->stamp;
    RCLCPP_INFO(this->get_logger(), "Latency; '%llu'", end - begin);
  }
}

#include <chrono>
#include <cstdlib>
#include <cstdint>

#include "comm/pub.hpp"

using namespace std::chrono;
using namespace std::chrono_literals;

namespace snippet_comm {
  Publisher::Publisher(const std::string & name, const std::string & output, bool intra_process)
    : Node(name, rclcpp::NodeOptions().use_intra_process_comms(intra_process)) {
    // data size in message
    this->declare_parameter("blob_size", 1000); // not used now fixed
    blob_size_ = this->get_parameter("blob_size").as_int();
    publisher_ = this->create_publisher<comm::msg::Stamped1000KBin>(output, 1);

    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    server_ = this->
      create_service<comm::srv::PublishLoop>("publish_loop",
                                             std::bind(&Publisher::publish_loop_srv, this, _1, _2, _3));
  }

  void Publisher::publish_loop_srv(const std::shared_ptr<rmw_request_id_t>,
                                   const std::shared_ptr<comm::srv::PublishLoop::Request> request,
                                   const std::shared_ptr<comm::srv::PublishLoop::Response>) {
    this->publish_loop(request->count);
  }

  void Publisher::publish_loop(int64_t count) {
    int64_t pubcount = 0;
    rclcpp::WallRate rate(100ms);
    RCLCPP_INFO(this->get_logger(), "LOOP START %d", count);
    while (rclcpp::ok() && (pubcount++ < count)) {
      auto pub_ptr = publisher_;
      if (!pub_ptr) {
        RCLCPP_ERROR(this->get_logger(), "error in publish_loop");
        break;
      }
      comm::msg::Stamped1000KBin::UniquePtr msg(new comm::msg::Stamped1000KBin());
      // msg->data.data.resize(blob_size_);
      for (size_t i = 0; i < blob_size_; i++) {
        // msg->data.data[i] = uint8_t(rand() % 100); // for variable length
        msg->data[i] = uint8_t(rand() % 100); // for fixed length
      }
      const high_resolution_clock::time_point time_published = high_resolution_clock::now();
      const nanoseconds nsec = duration_cast<nanoseconds>(time_published.time_since_epoch());
      msg->stamp = nsec.count();
      pub_ptr->publish(std::move(msg));
      rate.sleep();
    }
    RCLCPP_INFO(this->get_logger(), "LOOP END");
  }
}

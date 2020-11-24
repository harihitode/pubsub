#ifndef SNIPPET_COMM_SUB_HPP
#define SNIPPET_COMM_SUB_HPP

#include <string>

#include "rclcpp/rclcpp.hpp"
#include "comm/msg/stamped2_m_bin.hpp"
#include "comm/srv/publish_loop.hpp"

namespace snippet_comm {
  class Subscriber : public rclcpp::Node {
  public:
    explicit Subscriber(const std::string & name, const std::string & input, bool intra_process = false);
    void request_publish(int64_t count);
  private:
    size_t blob_size_;
    rclcpp::Subscription<comm::msg::Stamped2MBin>::SharedPtr subscriber_;
    void topic_callback(const comm::msg::Stamped2MBin::UniquePtr msg) const;
  };
}

#endif

#ifndef SNIPPET_COMM_SUB_HPP
#define SNIPPET_COMM_SUB_HPP

#include "rclcpp/rclcpp.hpp"
#include "comm/msg/stamped_bin.hpp"

namespace snippet_comm {
  class Subscriber : public rclcpp::Node {
    rclcpp::Subscription<comm::msg::StampedBin>::SharedPtr subscriber_;
  public:
    explicit Subscriber(const std::string & name, const std::string & input, bool intra_process, size_t blob_size);
  private:
    size_t blob_size_;
    void topic_callback(const comm::msg::StampedBin::UniquePtr msg) const;
  };
}

#endif

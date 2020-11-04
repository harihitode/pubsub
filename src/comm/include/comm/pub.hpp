#ifndef SNIPPET_COMM_PUB_HPP
#define SNIPPET_COMM_PUB_HPP

#include "rclcpp/rclcpp.hpp"
#include "comm/msg/stamped_bin.hpp"

namespace snippet_comm {
  class Publisher : public rclcpp::Node {
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<comm::msg::StampedBin>::SharedPtr publisher_;
  public:
    explicit Publisher(const std::string & name, const std::string & output, bool intra_process = false);
  private:
    size_t blob_size_;
    void timer_callback();
  };
}

#endif

#ifndef SNIPPET_COMM_PUB_HPP
#define SNIPPET_COMM_PUB_HPP

#include "rclcpp/rclcpp.hpp"
#include "comm/msg/stamped1000_k_bin.hpp"
#include "comm/srv/publish_loop.hpp"

namespace snippet_comm {
  class Publisher : public rclcpp::Node {
  public:
    explicit Publisher(const std::string & name, const std::string & output, bool intra_process = false);
    void publish_loop(int64_t count);
  private:
    void publish_loop_srv(const std::shared_ptr<rmw_request_id_t> request_header,
                          const std::shared_ptr<comm::srv::PublishLoop::Request> request,
                          const std::shared_ptr<comm::srv::PublishLoop::Response> response);
    rclcpp::Publisher<comm::msg::Stamped1000KBin>::SharedPtr publisher_;
    rclcpp::Service<comm::srv::PublishLoop>::SharedPtr server_;
    size_t blob_size_;
  };
}

#endif

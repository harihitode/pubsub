#include <cinttypes>
#include <cstdio>
#include <memory>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "comm/pub.hpp"
#include "comm/sub.hpp"
#include "comm/msg/stamped_bin.hpp"

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor executor;

  const size_t blob_size = 8000;

  auto pub = std::make_shared<snippet_comm::Publisher>("publisher", "blob", true, blob_size);
  auto sub = std::make_shared<snippet_comm::Subscriber>("subscriber", "blob", true, blob_size);

  executor.add_node(pub);
  executor.add_node(sub);
  executor.spin();

  rclcpp::shutdown();
  return 0;
}

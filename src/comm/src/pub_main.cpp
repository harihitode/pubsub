#include <memory>

#include "comm/pub.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char * argv[]) {
  const size_t blob_size = 8000;
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<snippet_comm::Publisher>("publisher", "blob", false, blob_size));
  rclcpp::shutdown();
  return 0;
}

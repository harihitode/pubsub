#include <memory>

#include "comm/sub.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char * argv[]) {
  const size_t blob_size = 8000;
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<snippet_comm::Subscriber>("subscriber", "blob", false, blob_size));
  rclcpp::shutdown();
return 0;
}

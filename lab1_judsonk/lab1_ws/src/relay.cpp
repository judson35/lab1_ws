#include <chrono>
#include <functional>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "ackermann_msgs/msg/ackermann_drive.hpp"
#include "ackermann_msgs/msg/ackermann_drive_stamped.hpp"

using std::placeholders::_1;

class Relay : public rclcpp::Node {
public:
  Relay()
  : Node("relay") {
    subscription_ = this->create_subscription<ackermann_msgs::msg::AckermannDriveStamped>(
      "drive", 10, std::bind(&Relay::topic_callback, this, _1));

    publisher_ = this->create_publisher<ackermann_msgs::msg::AckermannDriveStamped>("drive_relay", 1); //queue size of 1

  }

private:
  void topic_callback(const ackermann_msgs::msg::AckermannDriveStamped::SharedPtr message) const {
    auto relay_message = ackermann_msgs::msg::AckermannDriveStamped();
    relay_message.drive.speed = message->drive.speed * 3;
    relay_message.drive.steering_angle = message->drive.steering_angle * 3;

    publisher_->publish(relay_message);
    // RCLCPP_INFO(this->get_logger(), "\nPublished Relay {Speed: %f \t Steering Angle: %f}", relay_message.drive.speed, relay_message.drive.steering_angle);
  }
  rclcpp::Subscription<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr subscription_;
  rclcpp::Publisher<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr publisher_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Relay>());
  rclcpp::shutdown();
  return 0;
}
#include <chrono>
#include <functional>
#include <string>
#include <typeinfo>
#include <iostream>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include "rcl_interfaces/msg/set_parameters_result.hpp"

#include "ackermann_msgs/msg/ackermann_drive_stamped.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

namespace {
    std::string SPEED = "v";
    std::string STEERING_ANGLE = "d";
}

class Talker : public rclcpp::Node {
public:
    Talker() : Node("talker") {

        auto param_desc = rcl_interfaces::msg::ParameterDescriptor{};
        param_desc.description = "This parameter is mine!";

        this->declare_parameter("v", 1.0);
        this->declare_parameter("d", 1.0);

        speed_ = this->get_parameter("v").as_double();
        steering_angle_ = this->get_parameter("d").as_double();

        publisher_ = this->create_publisher<ackermann_msgs::msg::AckermannDriveStamped>("drive", 10); //queue size of 10

        callback_handle_ = this->add_on_set_parameters_callback(std::bind(&Talker::parametersCallback, this, _1));

        this->publish_parameters();

        // timer_ = this->create_wall_timer(100ms, std::bind(&Talker::timer_callback, this));
    }

    rcl_interfaces::msg::SetParametersResult parametersCallback(const std::vector<rclcpp::Parameter> &parameters) {

        rcl_interfaces::msg::SetParametersResult result;
        result.successful = false;

        for (const auto &param:parameters) {
            if (param.get_name() == SPEED) {
                if (param.get_type() == rclcpp::ParameterType::PARAMETER_DOUBLE) {
                    result.successful = true;
                    speed_ = param.as_double();
                }
            } else if (param.get_name() == STEERING_ANGLE) {
                if (param.get_type() == rclcpp::ParameterType::PARAMETER_DOUBLE) {
                    result.successful = true;
                    steering_angle_ = param.as_double();
                }
            }
        }
    
        this->publish_parameters();

        return result;
    }

    void publish_parameters() {
        auto message = ackermann_msgs::msg::AckermannDriveStamped();
        message.drive.speed = speed_;
        message.drive.steering_angle = steering_angle_;
        publisher_->publish(message);

        RCLCPP_INFO(this->get_logger(), "\nPublished {Speed: %f" "\t Steering Angle: %f}", message.drive.speed, message.drive.steering_angle);
    }

    void timer_callback() { 
        RCLCPP_INFO(this->get_logger(), "Published {Speed: %f" "\t Steering Angle: %f}", speed_, steering_angle_);
    }

private:
    rclcpp::Publisher<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr publisher_;
    OnSetParametersCallbackHandle::SharedPtr callback_handle_;

    rclcpp::Subscription<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr subscription_;

    rclcpp::TimerBase::SharedPtr timer_;

    double speed_ = 0.0f;
    double steering_angle_ = 0.0f;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Talker>());
    rclcpp::shutdown();

    return 0;
}
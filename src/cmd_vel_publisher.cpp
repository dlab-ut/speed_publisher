#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/float32.hpp"

class CmdVelPublisher : public rclcpp::Node
{
public:
  CmdVelPublisher() : Node("velocity_publisher")
  {
    // Publisher
    publisher_ = this->create_publisher<std_msgs::msg::Float32>("/cmd_vel_linear_x", 10);
    
    // Subscriber
    subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel", 10,
      std::bind(&CmdVelPublisher::cmd_vel_callback, this, std::placeholders::_1));
  }

private:
  void cmd_vel_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
  {
    // linear.xの値を取得してFloat32メッセージに変換
    std_msgs::msg::Float32 float_msg;
    float_msg.data = msg->linear.x;
    
    // Publish
    publisher_->publish(float_msg);
  }
  
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CmdVelPublisher>());
  rclcpp::shutdown();
  return 0;
}

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"

class DiffDriveController : public rclcpp::Node
{
public:
  DiffDriveController(std::string name) : Node(name)
  {
    velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);

    timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&DiffDriveController::publishVelocity, this));

    subscription_ = this->create_subscription<nav_msgs::msg::Odometry>(
        "odom", 10, std::bind(&DiffDriveController::odom_callback, this, std::placeholders::_1));

    // target_distance_ = 3.0; // 目标距离3米
    // SetPoint = target_distance_;
    // last_error_ = 0;
    // integral_ = 0;
    // last_velocity_ = 0.0;
    // Kp_ = 0.01;
    // Ki_ = 0.01;
    // Kd_ = 0.05;
  };

private:
  void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "Received odometry message%lf", msg->pose.pose.position.x);
    if (msg->pose.pose.position.x >= 3)
    {
      speed_x = 0;
      nav_msgs::msg::Odometry::SharedPtr msg2;
      msg2->pose.pose.position.x = 3;
    }
    else if (msg->pose.pose.position.x <= 0)
    {
      speed_x = 1.0;
    }
  }
  void publishVelocity()
  {
    auto velocity_msg = geometry_msgs::msg::Twist();
    velocity_msg.linear.x = speed_x;
    velocity_msg.angular.z = 0;
    velocity_publisher_->publish(velocity_msg);
  }

  // void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
  // {
  //   double current_distance = std::sqrt(std::pow(msg->pose.pose.position.x, 2) + std::pow(msg->pose.pose.position.y, 2));
  //   double error_ = SetPoint - current_distance;
  //   integral_ += error_;
  //   double derivative_ = error_ - last_error_;

  //   // PID计算
  //   double output = Kp_ * error_ + Ki_ * integral_ + Kd_ * derivative_;

  //   // 根据PID输出调整速度
  //   if (current_distance > target_distance_ -0.5)
  //   { // 当接近目标时开始减速
  //     last_velocity_ -= output;
  //   }
  //   else
  //   {
  //     last_velocity_ += output;
  //   }

  // 发布速度命令
  //   geometry_msgs::msg::Twist cmd_vel;
  //   RCLCPP_INFO(this->get_logger(), "%lf", last_velocity_);
  //   cmd_vel.linear.x = std::max(0.0, last_velocity_); // 确保速度非负
  //   velocity_publisher_->publish(cmd_vel);

  //   last_error_ = error_;
  // }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscription_;
  float speed_x = 1.0;
  // double target_distance_;
  // double SetPoint;
  // double last_error_;
  // double integral_;
  // double last_velocity_;
  // double Kp_;
  // double Ki_;
  // double Kd_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<DiffDriveController>("diff_drive_controller");
  RCLCPP_INFO(node->get_logger(), "节点已经启动.");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
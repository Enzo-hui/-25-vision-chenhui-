
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"

class SphereMotion : public rclcpp::Node
{
public:
    SphereMotion(std::string name) : Node(name)
    {
        SpherePublisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500), std::bind(&SphereMotion::timerCallback, this));
        PosePublisher_ = this->create_publisher<nav_msgs::msg::Odometry>("position", 10);
        timer2_ = this->create_wall_timer(
            std::chrono::milliseconds(50), std::bind(&SphereMotion::publish_position, this));
        radius_ = 3.0;
        angle_ = 0.0;
    }

private:
    void timerCallback()
    {

        msg.angular.z = 2 * M_PI / 4.0;
        SpherePublisher_->publish(msg);
    }
    void publish_position()
    {
            time += 0.05;
            nav_msgs::msg::Odometry::SharedPtr msg2;
            msg2->pose.pose.position.x = radius_ * cos(time * msg.angular.z);
            msg2->pose.pose.position.y = radius_ * sin(time * msg.angular.z);
        //     PosePublisher_->publish(*msg2);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr SpherePublisher_;
    rclcpp::TimerBase::SharedPtr timer2_;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr PosePublisher_;
    double radius_ = 3.0;
    double angle_ = 0.0;
    double time = 0.0;
    geometry_msgs::msg::Twist msg;
};
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SphereMotion>("SphereMotion");
    RCLCPP_INFO(node->get_logger(), "节点已经启动.");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

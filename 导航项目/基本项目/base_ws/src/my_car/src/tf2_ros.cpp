#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.h"

class TfPublisher : public rclcpp::Node
{
public:
  TfPublisher() : Node("tf_publisher")
  {
    // 创建一个tf broadcaster
    tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);

    // 设置发布频率
    timer_ = this->create_wall_timer(
      500ms, std::bind(&TfPublisher::publishTransform, this));
  }

private:
  void publishTransform()
  {
    // 创建一个geometry_msgs::TransformStamped，并填充数据
    geometry_msgs::msg::TransformStamped transformStamped;
    transformStamped.header.stamp = this->now();
    transformStamped.header.frame_id = "odom";
    transformStamped.child_frame_id = "map";
    transformStamped.transform.translation.x = 0.0;
    transformStamped.transform.translation.y = 0.0;
    transformStamped.transform.translation.z = 0.0;
    transformStamped.transform.rotation.x = 0.0;
    transformStamped.transform.rotation.y = 0.0;
    transformStamped.transform.rotation.z = 0.0;
    transformStamped.transform.rotation.w = 1.0;

    // 发布map到odom的变换
    tf_broadcaster_->sendTransform(transformStamped);

    // 创建map_bias到map的变换
    transformStamped.header.frame_id = "map";
    transformStamped.child_frame_id = "map_bias";
    transformStamped.transform.translation.x = 2.0;
    transformStamped.transform.translation.y = 3.0;
    transformStamped.transform.translation.z = 0.0;
    transformStamped.transform.rotation.x = 0.0;
    transformStamped.transform.rotation.y = 0.0;
    transformStamped.transform.rotation.z = std::sin(M_PI / 4);
    transformStamped.transform.rotation.w = std::cos(M_PI / 4);

    // 发布map_bias到map的变换
    tf_broadcaster_->sendTransform(transformStamped);
  }

  tf2_ros::TransformBroadcaster::SharedPtr tf_broadcaster_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TfPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
// #include "rclcpp/rclcpp.hpp"
// #include "geometry_msgs/msg/twist.hpp"

// class TopicSubscribe01 : public rclcpp::Node
// {
// public:
//     TopicSubscribe01(std::string name) : Node(name)
//     {
//         RCLCPP_INFO(this->get_logger(), "大家好，我是%s.", name.c_str());
//           // 创建一个订阅者订阅话题
//         command_subscribe_ = this->create_subscription<geometry_msgs::msg::Twist>("cmd_vel", 10, std::bind(&TopicSubscribe01::command_callback, this, std::placeholders::_1));
//     }

// private:
//      // 声明一个订阅者
//     rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr command_subscribe_;
//      // 收到话题数据的回调函数
//     void command_callback(const geometry_msgs::msg::Twist msg)
//     {
        
//         RCLCPP_INFO(this->get_logger(), " hhh%f",msg.linear.x);
//     }
// };

// int main(int argc, char **argv)
// {
//     rclcpp::init(argc, argv);
//     /*创建对应节点的共享指针对象*/
//     auto node = std::make_shared<TopicSubscribe01>("topic_subscribe_01");
//     /* 运行节点，并检测退出信号*/
//     rclcpp::spin(node);
//     rclcpp::shutdown();
//     return 0;
// }

// #include "rclcpp/rclcpp.hpp"
// #include "nav_msgs/msg/odometry.hpp"

// class OdomListener : public rclcpp::Node
// {
// public:
//   OdomListener() : Node("odom_listener")
//   {
//     subscription_ = this->create_subscription<nav_msgs::msg::Odometry>(
//       "odom", 10, std::bind(&OdomListener::odom_callback, this, std::placeholders::_1));
//   }

//   void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
//   {
//     RCLCPP_INFO(this->get_logger(), "Received odometry message%lf",msg->pose.pose.position.x);
//     // 处理你的里程计数据
//   }

// private:
//   rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscription_;
// };

// int main(int argc, char ** argv)
// {
//   rclcpp::init(argc, argv);
//   auto node = std::make_shared<OdomListener>();
//   rclcpp::spin(node);
//   rclcpp::shutdown();
//   return 0;
// }
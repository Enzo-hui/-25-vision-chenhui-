#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include <iostream>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/common.h>
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>

class PCD_loading : public rclcpp::Node
{
public:
    PCD_loading(std::string name) : Node(name)
    {
        PCD_Publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("pcd", 10);
        // pcl::io::loadPCDFile("path_to_your_pcd_file.pcd", cloud_);
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&PCD_loading::PCD_publisher, this));
        // if(pcl::io::loadPCDFile<pcl::PointXYZ>("/home/chen/华南虎视觉/考核项目/导航项目/测试项目/sphere_motion/pcl_ws/pcl_task/basic_task3.pcd", *cloud_)==-1)
        // {
        //     PCL_ERROR("Couldn't read file\n");
        //     return ;
        // }
    }

private:
    void PCD_publisher()
    {

        sensor_msgs::msg::PointCloud2 output;

        // pcl::toROSMsg(*cloud_, output);
        // output.header.frame_id = "base_link";
        pcl::PassThrough<pcl::PointXYZ> pass;
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

        // Load the PCD file
        pcl::PCDReader reader;
        if (reader.read("/home/chen/华南虎视觉/考核项目/导航项目/测试项目/sphere_motion/pcl_ws/pcl_task/basic_task3.pcd", *cloud) < 0)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to read PCD file.");
            return;
        }

        pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;
        voxel_grid.setInputCloud(cloud);
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
        voxel_grid.setLeafSize(0.3f, 0.3f, 0.3f);
        voxel_grid.filter(*cloud_filtered);
        // Convert the PCL point cloud to a ROS2 message

        pass.setInputCloud(cloud_filtered);
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered_2(new pcl::PointCloud<pcl::PointXYZ>);
        pass.setFilterFieldName("z");
        pass.setFilterLimits(-std::numeric_limits<float>::max(), 0.8); // 保留高度小于0.8米的点
        pass.filter(*cloud_filtered_2);
        pcl::toROSMsg(*cloud_filtered_2, output);
        output.header.frame_id = "base_link"; // Set the frame ID
        PCD_Publisher_->publish(output);
        //  RCLCPP_INFO(this->get_logger(), "points_size(%d,%d)",output.height,output.width);
        return;
    }

    rclcpp::TimerBase::SharedPtr timer_;
    // pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr PCD_Publisher_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PCD_loading>("test1");
    rclcpp::spin(node);
    RCLCPP_INFO(node->get_logger(), "节点已经启动.");
    rclcpp::shutdown();
    return 0;
}

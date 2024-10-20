# 导入库
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    
    PCD_Publisher=Node(
        package="pcl_task",
        executable="PCD_Publisher"
    )
    PCD_Subsrciber=Node(
        package="pcl_task",
        executable="ros2pcl_test_sub"
    )
    # 创建LaunchDescription对象launch_description,用于描述launch文件
    launch_description = LaunchDescription(
        [PCD_Publisher ,PCD_Subsrciber])
    # 返回让ROS2根据launch描述执行节点
    return launch_description

import launch
import launch_ros
from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource
import os
from launch_ros.actions import Node
import launch_ros.parameter_descriptions

def generate_launch_description():
    # 获取默认路径
    robot_name_in_model="my_car"
    urdf_tutorial_path=get_package_share_directory('my_car')
    default_model_path = os.path.join(urdf_tutorial_path,'urdf','my_car.urdf.xacro')
    default_world_path=os.path.join(urdf_tutorial_path,'world','RMUC2024.world')
    
    action_declare_arg_mode_path=launch.actions.DeclareLaunchArgument(
        name='model',default_value=str(default_model_path),
        description='文件路径'
    )
    
    # robot_description=launch_ros.parameter_descriptions.ParameterValue(launch.substitutions.Command(['',launch.substitutions.LaunchConfiguration('model')])
    #         ,value_type=str
    # )
    substitutions_command_result=launch.substitutions.Command([' xacro ',launch.substitutions.LaunchConfiguration('model')])
    robot_description_value=launch_ros.parameter_descriptions.ParameterValue(substitutions_command_result,value_type=str)

    robot_state_publisher_node=launch_ros.actions.Node(
        package="robot_state_publisher",
        executable='robot_state_publisher',
        parameters=[{'robot_description':robot_description_value}]
    )

    # launch_gazebo=launch.actions.IncludeLaunchDescription(
    #     PythonLaunchDescriptionSource([get_package_share_directory(
    #         'gazebo_ros'),'/launch','/gazebo.launch.py']),launch_arguments=[('world',default_world_path),('verbose','true')]
    # )
    action_launch_gazebo = launch.actions.IncludeLaunchDescription(
        launch.launch_description_sources.PythonLaunchDescriptionSource([get_package_share_directory('gazebo_ros'), '/launch', '/gazebo.launch.py']),
        launch_arguments=[('world', default_world_path), ('verbose', 'true')]
    )


    spawn_entity_node=launch_ros.actions.Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-topic','/robot_description','-entity',robot_name_in_model]
    )
    # diff_drive_controller=Node(
    #     package='my_car',
    #     executable='control_car'
    # )

    return launch.LaunchDescription([   action_declare_arg_mode_path,
        robot_state_publisher_node,
        action_launch_gazebo,
        spawn_entity_node
        # ,
        # diff_drive_controller
        ]
    )
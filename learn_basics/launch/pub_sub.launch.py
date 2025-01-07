from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='learn_basics',
            executable='publisher_class',
            output='screen'
        ),
        Node(
            package='learn_basics',
            executable='subscriber_class',
            output='screen'
        )
    ])
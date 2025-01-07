from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='learn_basics',
            executable='param_reader',
            parameters=[{
                'number_particles': 400,
                'topics': ['scan', 'image'],
                'topic_types': ['sensor_msgs/msg/LaserScan', 'sensor_msgs/msg/Image']
            }],
            output='screen'
        )
    ])
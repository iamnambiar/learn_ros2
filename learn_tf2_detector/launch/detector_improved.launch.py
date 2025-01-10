from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(package='learn_tf2_detector',
             executable='detector_improved',
             output='screen',
             parameters=[{
                 'use_sim_time': True
             }],
             remappings=[
                 ('input_scan', '/scan_raw')
             ])
    ])
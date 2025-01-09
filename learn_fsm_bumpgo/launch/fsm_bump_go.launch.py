
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='learn_fsm_bumpgo',
            executable='bumpgo',
            output='screen',
            parameters=[{
                'use_sim_time': True
            }],
            remappings=[
                ('input_scan', '/scan_raw'),
                ('output_vel', '/key_vel')
            ]
        )
    ])
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="lab1_pkg",
            executable="relay",
            name="relay",
            output="screen",
            emulate_tty=True,
            parameters=[]
        ),
        Node(
            package="lab1_pkg",
            executable="talker",
            name="talker",
            output="screen",
            emulate_tty=True,
            parameters=[
                {"v": 4.0, "d": 1.0}
            ]
        )
    ])
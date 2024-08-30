#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from std_msgs.msg import String


class MapServerPython(Node):

    def __init__(self):
        super().__init__("map_server_python")
        self.get_logger().info("Hello world from the Python node map_server_python")


def main(args=None):
    rclpy.init(args=args)

    map_server_python = MapServerPython()

    try:
        rclpy.spin(map_server_python)
    except KeyboardInterrupt:
        pass

    map_server_python.destroy_node()
    rclpy.try_shutdown()


if __name__ == '__main__':
    main()

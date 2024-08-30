#ifndef MAP_SERVER_HPP__MAP_SERVER_HPP_
#define MAP_SERVER_HPP__MAP_SERVER_HPP_


#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"
#include "yaml-cpp/yaml.h"
#include "opencv2/opencv.hpp"
#include "my_map_server/srv/manage_map.hpp"

namespace my_map_server{
class MapServerCpp : public rclcpp::Node{
public:
  MapServerCpp();    
  ~MapServerCpp() = default;

private:
  bool loadMapFromFile(const std::string &map_yaml_file);
  void publish_map();
  void manage_map_callback(const std::shared_ptr<my_map_server::srv::manage_map::Request> request,
                           std::shared_ptr<my_map_server::srv::manage_map::Response> response);

  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr map_publisher_;
  rclcpp::Service<my_map_server::srv::ManageMap>::SharedPtr manage_map_service_;
  nav_msgs::msg::OccupancyGrid map_;
  std::string yaml_filename_;
}

} // namespace my_map_server

#endif // MAP_SERVER_HPP__MAP_SERVER_HPP_
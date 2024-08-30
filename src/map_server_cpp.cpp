#include "map_server/map_server.hpp"

my_map_server::MapServerCpp::MapServerCpp() : Node("map_server")
{
  this->declare_parameter<std::string>("yaml_filename", "map.yaml");
  this->get_parameter("yaml_filename", yaml_filename_);
  //publisherのコンストラクタ。第一引数はトピック名、第二引数はキューのサイズ
  // this->は自分自身を表している。多分selfに似たもの
  map_publisher_ = this->create_publisher<nav_msgs::msg::OccupancyGrid>("map", 10);
  manage_map_service_ = this->create_service<my_map_server::srv::ManageMap>("manage_map",
    std::bind(&my_map_server::MapServerCpp::manage_map_callback, this, std::placeholders::_1, std::placeholders::_2));
  yaml_filename_ = "map.yaml";

  if (!loadMapFromFile(yaml_filename_))
  {
    RCLCPP_ERROR(this->get_logger(), "Failed to load map from file %s", yaml_filename_.c_str());
  }
  else 
  {
    publish_map();
  }

  my_map_server::MapServerCpp::loadMapFromFile()
}

my_map_server::MapServerCpp::loadMapFromFile(const std::string &yaml_filename_):
try
{ // ファイルを開く input file stream
  std::ifstream fin(yaml_filename_);
  
  if (!fin)
  {
    RCLCPP_ERROR(this->get_logger(), "Failed to open file %s", yaml_filename_.c_str());
    return false;
  }
  // YAMLファイルを読み込む
  YAML::Node map_config = YAML::LoadFile(yaml_filename_);
  // マップのimageを読み込む(int型)
  std::string image = map_config["image"].as<std::string>();
  // マップの解像度を読み込む(double型)
  double resolution = map_config["resolution"].as<double>();
  // originは配列なのでstd::vector<double>で読み込む
  std::vector<double> origin = map_config["origin"].as<std::vector<double>>();

  cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
  if (image.empty())
    {
      RCLCPP_ERROR(this->get_logger(), "Failed to load image file: %s", image_path.c_str());
      return false;
    }

  
    // OccupancyGridメッセージを作成
    map_.header.frame_id = "map";
    map_.info.resolution = resolution;
    map_.info.width = image.cols;
    map_.info.height = image.rows;
    map_.info.origin.position.x = origin[0];
    map_.info.origin.position.y = origin[1];
    map_.info.origin.position.z = 0.0;
    map_.info.origin.orientation.w = 1.0;

    // マップのデータを格納する配列を作成
    map_.data.resize(map_.info.width * map_.info.height);

    // 画像データをOccupancyGridに変換
    int free_thresh = map_config["free_thresh"].as<int>(205); // デフォルト値を設定
    int occupied_thresh = map_config["occupied_thresh"].as<int>(205);

    

}
catch(const std::exception& e)
{
  std::cerr << e.what() << '\n';
}
{


  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MapServerCpp>());
  rclcpp::shutdown();
  return 0;
}
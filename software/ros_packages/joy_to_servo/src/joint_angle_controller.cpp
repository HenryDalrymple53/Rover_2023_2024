#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "moveit/robot_model_loader/robot_model_loader.hpp"
#include "moveit/planning_interface/planning_interface.hpp"
#include "moveit/planning_scene/planning_scene.hpp"
#include "moveit/kinematic_constraints/utils.hpp"
#include "moveit_msgs/msg/display_trajectory.hpp"
#include "moveit_msgs/msg/planning_scene.hpp"
#include "moveit_visual_tools/moveit_visual_tools.h"
#include "moveit/move_group_interface/move_group_interface.hpp"

using std::placeholders::_1;

class JointAngleController : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("joint_angle_controller")
    {
      joint_angle_subscription_ = this->create_subscription<std_msgs::msg::String>(
      "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const std_msgs::msg::String & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr joint_angle_subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}

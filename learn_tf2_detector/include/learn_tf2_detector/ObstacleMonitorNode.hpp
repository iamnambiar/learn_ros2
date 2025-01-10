#ifndef LEARN_TF2_DETECTOR__OBSTACLEMONITORNODE_HPP_
#define LEARN_TF2_DETECTOR__OBSTACLEMONITORNODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "visualization_msgs/msg/marker.hpp"

namespace learn_tf2_detector
{
    class ObstacleMonitorNode : public rclcpp::Node
    {
    public:
        ObstacleMonitorNode();
    private:
        void control_cycle();

        rclcpp::TimerBase::SharedPtr timer_;
        tf2::BufferCore tf_buffer_;
        tf2_ros::TransformListener tf_listener_;
        rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
    };
}

#endif  // LEARN_TF2_DETECTOR__OBSTACLEMONITORNODE_HPP_
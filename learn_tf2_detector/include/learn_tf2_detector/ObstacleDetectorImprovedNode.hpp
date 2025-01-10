
#ifndef LEARN_TF2_DETECTOR__OBSTACLEDETECTORIMPROVEDNODE_HPP_
#define LEARN_TF2_DETECTOR__OBSTACLEDETECTORIMPROVEDNODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"

namespace learn_tf2_detector
{
    class ObstacleDetectorImprovedNode : public rclcpp::Node
    {
    public:
        ObstacleDetectorImprovedNode();

    private:
        void scan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg);
        
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_sub_;
        std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_broadcaster_;
        tf2::BufferCore tf_buffer_;
        tf2_ros::TransformListener tf_listener_;
    };
} // namespace learn_tf2_detector


#endif // LEARN_TF2_DETECTOR__OBSTACLEDETECTORIMPROVEDNODE_HPP_

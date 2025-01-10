#include "learn_tf2_detector/ObstacleDetectorNode.hpp"

namespace learn_tf2_detector
{
    ObstacleDetectorNode::ObstacleDetectorNode() 
    : Node("obstacle_detector")
    {
        scan_sub_ = create_subscription<sensor_msgs::msg::LaserScan>(
            "input_scan", rclcpp::SensorDataQoS(),
            std::bind(&ObstacleDetectorNode::scan_callback, this, std::placeholders::_1));
        tf_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(*this);
    }

    void ObstacleDetectorNode::scan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg)
    {
        double dist = msg->ranges[msg->ranges.size()/2];

        if (!std::isinf(dist)) {
            geometry_msgs::msg::TransformStamped detection_tf;

            detection_tf.header = msg->header;
            detection_tf.child_frame_id = "detected_obstacle";
            detection_tf.transform.translation.x = msg->ranges[msg->ranges.size() / 2];
            tf_broadcaster_->sendTransform(detection_tf);
        }
    }
}
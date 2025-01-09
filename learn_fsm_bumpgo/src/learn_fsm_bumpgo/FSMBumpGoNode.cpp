#include <utility>
#include "learn_fsm_bumpgo/FSMBumpGoNode.hpp"

namespace learn_fsm_bumpgo
{
    FSMBumpGoNode::FSMBumpGoNode() : Node("fsm_bump_go"), state_(FORWARD)
    {
        scan_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>("input_scan", rclcpp::SensorDataQoS(), std::bind(&FSMBumpGoNode::scan_callback, this, std::placeholders::_1));
        vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("output_vel", 10);
        timer_ = this->create_wall_timer(50ms, std::bind(&FSMBumpGoNode::control_cycle, this));

        state_ts_ = now();
    }

    void FSMBumpGoNode::scan_callback(sensor_msgs::msg::LaserScan::UniquePtr msg)
    {
        last_scan_ = std::move(msg);
    }

    void FSMBumpGoNode::control_cycle()
    {
        if (last_scan_ == nullptr) {
            return;
        }

        geometry_msgs::msg::Twist out_vel;
        
        switch (state_) {
            case FORWARD:
                out_vel.linear.x = SPEED_LINEAR;
                if (check_forward_2_stop()) {
                    go_state(STOP);
                }
                if (check_forward_2_back()) {
                    go_state(BACK);
                }
                break;
            case BACK:
                out_vel.linear.x = -SPEED_LINEAR;
                if (check_back_2_turn()) {
                    go_state(TURN);
                }
                break;
            case TURN:
                out_vel.angular.z = SPEED_ANGULAR;
                if (check_turn_2_forward()) {
                    go_state(FORWARD);
                }
                break;
            case STOP:
                if (check_stop_2_forward()) {
                    go_state(FORWARD);
                }
                break;
            default:
                break;
        }
        vel_pub_->publish(out_vel);
    }

    void FSMBumpGoNode::go_state(int new_state)
    {
        state_ = new_state;
        state_ts_ = now();
    }

    bool FSMBumpGoNode::check_forward_2_back()
    {
        size_t pos = last_scan_->ranges.size() / 2;
        return last_scan_->ranges[pos] < OBSTACLE_DISTANCE;
    }

    bool FSMBumpGoNode::check_forward_2_stop()
    {
        auto elapsed = now() - rclcpp::Time(last_scan_->header.stamp);
        return elapsed > SCAN_TIMEOUT;
    }

    bool FSMBumpGoNode::check_back_2_turn()
    {
        return (now() - state_ts_) > BACKING_TIME;
    }

    bool FSMBumpGoNode::check_turn_2_forward()
    {
        return (now() - state_ts_) > TURNING_TIME;
    }

    bool FSMBumpGoNode::check_stop_2_forward()
    {
        auto elapsed = now() - rclcpp::Time(last_scan_->header.stamp);
        return elapsed < SCAN_TIMEOUT;
    }
}
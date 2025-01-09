#include "rclcpp/rclcpp.hpp"
#include "learn_fsm_bumpgo/FSMBumpGoNode.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<learn_fsm_bumpgo::FSMBumpGoNode>());
    rclcpp::shutdown();
    return 0;
}
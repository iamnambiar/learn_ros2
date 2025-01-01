#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

class SubscriberNode : public rclcpp::Node
{
    public:
        SubscriberNode() : Node("subscriber_node")
        {
            auto callback_fn = [this](std_msgs::msg::Int32::UniquePtr message) -> void {
                RCLCPP_INFO(this->get_logger(), "I heard the number: %d", message->data);
            };
            subscriber_ = this->create_subscription<std_msgs::msg::Int32>("int_topic", 10, callback_fn);
        }
    private:
        rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SubscriberNode>());
    rclcpp::shutdown();
    return 0;
}
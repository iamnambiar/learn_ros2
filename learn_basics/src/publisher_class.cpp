#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

using namespace std::chrono_literals;

class PublisherNode : public rclcpp::Node
{
    public:
        PublisherNode() : Node("publisher_node"), counter_(0)
        {
            publisher_ = this->create_publisher<std_msgs::msg::Int32>("int_topic", 10);
            auto timer_callback = [this]() -> void {
                auto message = std_msgs::msg::Int32();
                message.data = counter_++;
                publisher_->publish(message);
            };
            timer_ = this->create_wall_timer(500ms, timer_callback);
        }
    private:
        rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        int counter_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PublisherNode>());
    rclcpp::shutdown();
    return 0;
}
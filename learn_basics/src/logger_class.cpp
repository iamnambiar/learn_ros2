#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;
class LoggerNode : public rclcpp::Node
{
	public:
		LoggerNode(): Node("logger_node")
		{
			counter_ = 0;
			auto timer_callback = [this]() -> void {
				RCLCPP_INFO(this->get_logger(), "Hello %d", counter_++);
				};
			timer_ = this->create_wall_timer(500ms, timer_callback);
		}

	private:
		rclcpp::TimerBase::SharedPtr timer_;
		int counter_;
};

int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<LoggerNode>());
	rclcpp::shutdown();
	return 0;
}

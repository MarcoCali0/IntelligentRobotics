#include "ros/ros.h"
#include "std_msgs/String.h"
#include "exercise2/Message.h"

void messageCallback(const exercise2::Message::ConstPtr &msg)
{
    ROS_INFO("Current Battery Level: %d %%.\t Room %s (ID %d)", msg->charge_level, msg->room_name.c_str(), msg->room_ID);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "charging_station");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("robot_state", 1000, messageCallback);
    ros::spin();
    return 0;
}
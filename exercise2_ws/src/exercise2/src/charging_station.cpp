#include "ros/ros.h"
#include "std_msgs/String.h"
#include "exercise2/Message.h"
#include "exercise2/Service.h"
#include "std_msgs/Header.h"

uint8_t number_stations = 4;
uint8_t timer_stations[] = {2, 3, 4, 5};

void ask_robot_state(const ros::TimerEvent &event)
{
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<exercise2::Service>("/get_robot_state");
    exercise2::Service srv;

    srv.request.station_ID = 423;

    srv.request.header = std_msgs::Header();
    srv.request.header.stamp = ros::Time::now();
    srv.request.header.frame_id = "charging_station";

    if (client.call(srv))
    {
        ROS_INFO("Current Battery Level: %d %%. Room %s (ID %d)",
                 srv.response.message.charge_level, srv.response.message.room_name.c_str(), srv.response.message.room_ID);
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "charging_station");
    ros::NodeHandle n;

    // Create a timer with the desired period
    ros::Timer timer = n.createTimer(ros::Duration(timer_stations[0]), ask_robot_state);

    ros::spin();
    return 0;
}
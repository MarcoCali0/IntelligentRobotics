#include "ros/ros.h"
#include "std_msgs/String.h"
#include "exercise2/Message.h"
#include "exercise2/Service.h"
#include "std_msgs/Header.h"

// TODO: use a class!
void ask_robot_state(const ros::TimerEvent &event)
{
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<exercise2::Service>("/get_robot_state");
    exercise2::Service srv;

    // generate the header for the service request
    srv.request.header = std_msgs::Header();
    srv.request.header.stamp = ros::Time::now();
    srv.request.header.seq = 0; // TODO: increment it
    // srv.request.header.frame_id = "charging_station";

    // generate the station ID for the service request
    int station_ID;
    if (n.getParam("station_ID", station_ID))
        ROS_INFO("Station ID retrieved: %d", station_ID);
    else
        ROS_ERROR("Cannot retrieve station ID from launch file");
    srv.request.station_ID = station_ID;

    if (client.call(srv))
    {
        // TODO: must print request and response (not very important)
        ROS_INFO("Current Battery Level: %d %%. Room %s (ID %d)",
                 srv.response.message.charge_level, srv.response.message.room_name.c_str(), srv.response.message.room_ID);
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "charging_station");
    ros::NodeHandle n;

    int timer;
    if (n.getParam("timer", timer))
        ROS_INFO("Timer period retrieved: %d", timer);
    else
        ROS_ERROR("Cannot retrieve timer from launch file");

    ros::Timer t = n.createTimer(ros::Duration(timer), ask_robot_state);
    ros::spin();
    return 0;
}
#include "ros/ros.h"
#include "exercise2/Service.h"
#include "std_msgs/Header.h"

class ChargingStation
{
public:
    ChargingStation(int station_ID, int timer)
    {
        this->seq = 0;
        this->station_ID = station_ID;
        this->timer = timer;

        // generate the header for the service request
        this->srv.request.header = std_msgs::Header();

        // generate the station ID for the service request
        this->srv.request.station_ID = this->station_ID;

        // create node for service request
        this->client = n.serviceClient<exercise2::Service>("/get_robot_state");
    }

    void ask_robot_state(const ros::TimerEvent &event)
    {
        // update the header for the service request
        this->srv.request.header.stamp = ros::Time::now();
        this->srv.request.header.seq = this->seq;
        this->seq++;

        if (client.call(this->srv))
        {
            // TODO: must print request and response (not very important)
            ROS_INFO("Current Battery Level: %d %%. Room %s (ID %d)",
                     this->srv.response.message.charge_level, this->srv.response.message.room_name.c_str(), this->srv.response.message.room_ID);
        }
    }

private:
    int seq;
    int station_ID;
    int timer;
    exercise2::Service srv;
    ros::NodeHandle n;
    ros::ServiceClient client;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "charging_station");
    ros::NodeHandle n;

    // Fetch parameters from launch file
    int station_ID, timer;
    n.getParam("station_ID", station_ID);
    n.getParam("timer", timer);

    ChargingStation charging_station(station_ID, timer);
    ros::Timer t = n.createTimer(ros::Duration(timer), &ChargingStation::ask_robot_state, &charging_station);
    ros::spin();
    return 0;
}
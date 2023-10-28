#include "ros/ros.h"
#include "std_msgs/String.h"
#include "exercise2/Message.h"
#include "std_msgs/Header.h"
#include "exercise2/Service.h"
#include <string>

struct room
{
    std::string room_name;
    int8_t ID;
};

room rooms[5] = {
    {"Robot Vision Lab", 1},
    {"SSL Lab", 2},
    {"Neurorobotics Lab", 3},
    {"IAS Lab", 4},
    {"Autonomous Robotics Lab", 5}};

class Robot
{
public:
    Robot(uint8_t initial_battery, room initial_room)
    {
        this->battery = initial_battery;
        this->current_room = initial_room;
        this->seq = 0;
    }

    bool get_robot_state(exercise2::Service::Request &req, exercise2::Service::Response &res)
    {
        ROS_INFO("REQUEST RECEIVED");
        exercise2::Message msg;
        msg.room_name = this->current_room.room_name;
        msg.room_ID = this->current_room.ID;
        msg.charge_level = this->battery;

        std_msgs::Header header;
        res.header = header;
        res.header.stamp = ros::Time::now();
        res.header.frame_id = "charging_station";
        res.header.seq = this->seq;
        res.message = msg;
        this->seq++;
        
        return true;
    }

    void decrease_battery()
    {
        // Reset battery when it's discharged
        this->battery = (this->battery > 0) ? (this->battery - 1) : 100;
    }

private:
    uint8_t battery;
    room current_room;
    int seq;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "cleaner_robot");
    ros::NodeHandle n;

    Robot robot(100, rooms[0]);
    ros::ServiceServer service = n.advertiseService("/get_robot_state", &Robot::get_robot_state, &robot);
    ROS_INFO("Cleaner Robot Node Started");
    ros::spin();
    return 0;
}
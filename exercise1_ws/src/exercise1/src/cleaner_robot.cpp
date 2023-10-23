#include "ros/ros.h"
#include "std_msgs/String.h"
#include "exercise1/Message.h"
#include <string>
#include <random>

struct room
{
    std::string room_name;
    int8_t ID;
};

room rooms[6] = {
    {"Charging Station", 0},
    {"Robot Vision Lab", 1},
    {"SSL Lab", 2},
    {"Neurorobotics Lab", 3},
    {"IAS Lab", 4},
    {"Autonomous Robotics Lab", 5}};

void decrease_battery(uint8_t &battery)
{
    // Reset battery when it's discharged
    battery = (battery > 0) ? (battery - 1) : 100;
}

room change_room()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 5); // Assuming array size is 5

    // Generate a random index
    int random_index = dist(gen);

    return rooms[random_index];
}

void change_room_callback(room &current_room)
{
    current_room = change_room();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "cleaner_robot");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<exercise1::Message>("robot_state", 1000);
    ros::Rate loop_rate(5); // 5 Hz communication

    uint8_t battery = 100;
    ros::Timer battery_level_timer = n.createTimer(ros::Duration(1), [&battery](const ros::TimerEvent &)
                                                   { decrease_battery(battery); });

    room current_room = change_room();
    ros::Timer room_changer_timer = n.createTimer(ros::Duration(10), [&current_room](const ros::TimerEvent &)
                                                  { change_room_callback(current_room); });

    while (ros::ok())
    {
        exercise1::Message msg;

        msg.room_name = current_room.room_name;
        msg.room_ID = current_room.ID;
        msg.charge_level = battery;
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
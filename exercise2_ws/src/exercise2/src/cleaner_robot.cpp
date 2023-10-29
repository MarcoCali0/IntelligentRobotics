#include "exercise2/Message.h"
#include "exercise2/Service.h"
#include "ros/ros.h"
#include "std_msgs/Header.h"

// Define a structure for room information
struct room {
  std::string room_name;
  int8_t ID;
};

// Initialize an array of rooms
room rooms[5] = {{"Robot Vision Lab", 1},
                 {"SSL Lab", 2},
                 {"Neurorobotics Lab", 3},
                 {"IAS Lab", 4},
                 {"Autonomous Robotics Lab", 5}};

// Define a class for the Robot
class Robot {
 public:
  Robot(uint8_t initial_battery, room initial_room) {
    this->battery = initial_battery;    // Initialize battery level
    this->current_room = initial_room;  // Initialize current room
    this->seq = 0;                      // Initialize sequence number
  }

  // Service callback to get the robot's state
  bool get_robot_state(exercise2::Service::Request &req,
                       exercise2::Service::Response &res) {
    // Notice that the request data is not used, but it could be used to
    // discriminate between nodes and send different data.

    // Generate the header of the service response
    res.header = std_msgs::Header();
    res.header.stamp = ros::Time::now();
    res.header.seq = this->seq;
    this->seq++;  // Increment the sequence number

    // Generate the message of the service response
    res.message = exercise2::Message();
    res.message.room_name = this->current_room.room_name;
    res.message.room_ID = this->current_room.ID;
    res.message.charge_level = this->battery;

    return true;
  }

  // Timer callback to update the battery level
  void update_battery(const ros::TimerEvent &event) {
    // Reset the battery when it's discharged
    this->battery = (this->battery > 0) ? (this->battery - 1) : 100;
  }

  // Timer callback to update the current room
  void update_room(const ros::TimerEvent &event) {
    int index_current_room = this->current_room.ID - 1;
    this->current_room = (index_current_room == 4)
                             ? this->current_room = rooms[0]
                             : rooms[index_current_room + 1];
  }

 private:
  uint8_t battery;    // Battery level of the robot
  room current_room;  // Current room the robot is in
  int seq;            // Sequence number for service responses
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "cleaner_robot");
  ros::NodeHandle n;

  ROS_INFO("Cleaner Robot Node Started");

  // Create a Robot instance with an initial battery level and room
  Robot robot(100, rooms[0]);

  // The battery decreases by 1% every 10 seconds
  int battery_life_seconds = 1000;
  ros::Timer update_battery =
      n.createTimer(ros::Duration(battery_life_seconds / 100),
                    &Robot::update_battery, &robot);

  // The robot cleans the same room for 20 seconds
  int duration_cleaning = 20;
  ros::Timer update_room = n.createTimer(ros::Duration(duration_cleaning),
                                         &Robot::update_room, &robot);

  // Create a service server to handle requests for robot state
  ros::ServiceServer service =
      n.advertiseService("/get_robot_state", &Robot::get_robot_state, &robot);

  ros::spin();
  return 0;
}

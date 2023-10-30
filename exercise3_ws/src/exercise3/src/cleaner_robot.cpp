#include <actionlib/server/simple_action_server.h>
#include <exercise3/RechargeAction.h>

#include "exercise3/Message.h"
#include "exercise3/Service.h"
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

class Robot {
 private:
  uint8_t battery;     // Battery level of the robot
  room current_room;   // Current room the robot is in
  bool is_recharging;  // Flag that indicates if robot is recharging
  int seq;             // Sequence number for service responses
  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<exercise3::RechargeAction> as_;
  exercise3::RechargeFeedback feedback_;
  exercise3::RechargeResult result_;

 public:
  Robot(uint8_t initial_battery, room initial_room)
      : as_(nh_, "recharge", boost::bind(&Robot::execute_callback, this, _1),
            false) {
    this->battery = initial_battery;    // Initialize battery level
    this->current_room = initial_room;  // Initialize current room

    this->seq = 0;                // Initialize sequence number
    this->is_recharging = false;  // Assume robot is not recharging
  }

  void execute_callback(const exercise3::RechargeGoalConstPtr &goal) {
    ros::Rate recharge_rate(1);  // loop rate 1 Hz
    bool success = true;

    ROS_INFO("Recharging...");

    while (this->battery < goal->target_battery_level) {
      if (as_.isPreemptRequested() || !ros::ok()) {
        ROS_INFO("Recharge Action: Preempted");
        as_.setPreempted();
        success = false;
        break;
      }
      this->battery++;
      feedback_.current_battery = this->battery;
      as_.publishFeedback(feedback_);
      recharge_rate.sleep();
    }

    if (success) {
      result_.goal_reached = true;
      // ROS_INFO("Completed recharge");
      this->is_recharging = false;
      as_.setSucceeded(result_);
    } else {
      // Set the goal to aborted if it was not successful
      result_.goal_reached = false;
      // ROS_INFO("Recharge Action: Aborted");
      as_.setAborted(result_);
    }

  }

  // Service callback to get the robot's state
  bool get_robot_state(exercise3::Service::Request &req,
                       exercise3::Service::Response &res) {
    // Generate the header of the service response
    res.header = std_msgs::Header();
    if (this->is_recharging == true)
      res.header.frame_id = "recharge_now";
    else
      res.header.frame_id = "cleaning";

    res.header.stamp = ros::Time::now();
    res.header.seq = this->seq;
    this->seq++;  // Increment the sequence number

    // Generate the message of the service response
    res.message = exercise3::Message();
    res.message.room_name = this->current_room.room_name;
    res.message.room_ID = this->current_room.ID;
    res.message.charge_level = this->battery;

    return true;
  }

  // Timer callback to update the battery level
  void update_battery(const ros::TimerEvent &event) {
    if (this->is_recharging == false) this->battery -= 1;

    if (this->battery <= 5) {
      ROS_WARN(
          "Battery Low (%d%%)! Moving towards the (nearest) charging station",
          this->battery);
      this->is_recharging = true;
      this->as_.start();
    }
  }

  // Timer callback to update the current room
  void update_room(const ros::TimerEvent &event) {
    // If the robot is recharging then we room cannot change
    if (!this->is_recharging) {
      int index_current_room = this->current_room.ID - 1;
      this->current_room = (index_current_room == 4)
                               ? this->current_room = rooms[0]
                               : rooms[index_current_room + 1];
    }
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "cleaner_robot");
  ros::NodeHandle n;

  ROS_INFO("Cleaner Robot Node Started");

  int initial_battery_level = 6;
  // Create a Robot instance with an initial battery level and room
  Robot robot(initial_battery_level, rooms[0]);

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

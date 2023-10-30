#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <exercise3/RechargeAction.h>

#include "exercise3/Service.h"
#include "ros/ros.h"
#include "std_msgs/Header.h"

// Define a class for the ChargingStation
class ChargingStation {
 public:
  ChargingStation(int station_ID, int timer) {
    this->seq = 0;                  // Initialize sequence number
    this->station_ID = station_ID;  // Initialize station_ID
    this->timer = timer;            // Initialize timer

    // Generate the header for the service request
    this->srv.request.header = std_msgs::Header();

    // Generate the station ID for the service request
    this->srv.request.station_ID = this->station_ID;

    // Create a ROS service client for the "/get_robot_state" service
    this->client = n.serviceClient<exercise3::Service>("/get_robot_state");
  }

  void recharge_robot() {
    ROS_INFO("Asking for recharge");
    actionlib::SimpleActionClient<exercise3::RechargeAction> recharge_action(
        "recharge", true);
    recharge_action.waitForServer();
    exercise3::RechargeGoal goal;

    // Generate goal
    goal.header = std_msgs::Header();
    goal.header.stamp = ros::Time::now();
    goal.target_battery_level = 10;
    recharge_action.sendGoal(
        goal, boost::bind(&ChargingStation::doneCb, this, _1, _2),
        boost::bind(&ChargingStation::activeCb, this),
        boost::bind(&ChargingStation::feedbackCb, this, _1));

    bool finished_before_timeout =
        recharge_action.waitForResult(ros::Duration(100.0));
    if (finished_before_timeout) {
      actionlib::SimpleClientGoalState state = recharge_action.getState();
      ROS_INFO("Action finished: %s", state.toString().c_str());
    } else {
      ROS_INFO("Action did not finish before the time out.");
    }
  }
  // Function to request robot state from a service
  void ask_robot_state(const ros::TimerEvent &event) {
    // Update header for the service request w/ current time and sequence number
    this->srv.request.header.stamp = ros::Time::now();
    this->srv.request.header.seq = this->seq;
    this->seq++;  // Increment the sequence number

    if (client.call(this->srv)) {
      ROS_INFO(
          "Charging Station %d, Current Battery Level: %d%% - Room %s (ID %d)",
          this->station_ID, this->srv.response.message.charge_level,
          this->srv.response.message.room_name.c_str(),
          this->srv.response.message.room_ID);
    }

    if (this->srv.response.header.frame_id == "recharge_now") recharge_robot();
  }

  void doneCb(const actionlib::SimpleClientGoalState &state,
              const exercise3::RechargeResultConstPtr &result) {}

  void activeCb() {}

  void feedbackCb(const exercise3::RechargeFeedbackConstPtr &feedback) {
    ROS_INFO("Recharging, current battery level %d%%",
             feedback->current_battery);
  }

 private:
  int seq;                    // Sequence number for service requests
  int station_ID;             // ID of the charging station
  int timer;                  // Timer duration for periodic requests
  exercise3::Service srv;     // Service message for the request
  ros::NodeHandle n;          // Node handle for the ChargingStation class
  ros::ServiceClient client;  // Service client to call the  service
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "charging_station");
  ros::NodeHandle n;

  // Fetch parameters from the launch file (station_ID and timer)
  int station_ID = 423;
  int timer = 1;

  // Create a ChargingStation instance with the provided parameters
  ChargingStation charging_station(station_ID, timer);
  ROS_INFO("Charging Station Node Started");

  // Create a timer that periodically calls the ask_robot_state service
  ros::Timer t =
      n.createTimer(ros::Duration(timer), &ChargingStation::ask_robot_state,
                    &charging_station);

  ros::spin();
  return 0;
}

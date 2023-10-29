#include "exercise2/Service.h"
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
    this->client = n.serviceClient<exercise2::Service>("/get_robot_state");
  }

  // Function to request robot state from a service
  void ask_robot_state(const ros::TimerEvent &event) {
    // Update header for the service request w/ current time and sequence number
    this->srv.request.header.stamp = ros::Time::now();
    this->srv.request.header.seq = this->seq;
    this->seq++;  // Increment the sequence number

    if (client.call(this->srv)) {
      ROS_INFO(
          "Charging Station %d, Current Battery Level: %d %%. Room %s (ID %d)",
          this->station_ID, this->srv.response.message.charge_level,
          this->srv.response.message.room_name.c_str(),
          this->srv.response.message.room_ID);
    }
  }

 private:
  int seq;                    // Sequence number for service requests
  int station_ID;             // ID of the charging station
  int timer;                  // Timer duration for periodic requests
  exercise2::Service srv;     // Service message for the request
  ros::NodeHandle n;          // Node handle for the ChargingStation class
  ros::ServiceClient client;  // Service client to call the  service
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "charging_station");
  ros::NodeHandle n;

  // Fetch parameters from the launch file (station_ID and timer)
  int station_ID, timer;
  n.getParam("station_ID", station_ID);
  n.getParam("timer", timer);

  // Create a ChargingStation instance with the provided parameters
  ChargingStation charging_station(station_ID, timer);

  // Create a timer that periodically calls the ask_robot_state service
  ros::Timer t =
      n.createTimer(ros::Duration(timer), &ChargingStation::ask_robot_state,
                    &charging_station);

  ros::spin();
  return 0;
}

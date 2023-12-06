#include <apriltag_ros/AprilTagDetection.h>
#include <apriltag_ros/AprilTagDetectionArray.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include "ros/ros.h"

struct Point3D {
  double x, y, z;
};

void update_mean(Point3D& current_mean, const Point3D& new_point, int size) {
  current_mean.x += 1.0 / size * (new_point.x - current_mean.x);
  current_mean.y += 1.0 / size * (new_point.y - current_mean.y);
  current_mean.z += 1.0 / size * (new_point.z - current_mean.z);
}
Point3D mean_point = {0, 0, 0};
int size = 1;

void callback(const apriltag_ros::AprilTagDetectionArray::ConstPtr& msg) {
  // Access header information
  std::string frame_id = msg->header.frame_id;
  ros::Time timestamp = msg->header.stamp;

  // Access detections (there should be only one)
  for (const auto& detection : msg->detections) {
    // Access pose information
    geometry_msgs::Point position = detection.pose.pose.pose.position;

    Point3D new_point = {position.x, position.y, position.z};
    update_mean(mean_point, new_point, size);

    ROS_INFO("Position: (%f, %f, %f) -> (%f, %f, %f) = Mean Point", position.x,
             position.y, position.z, mean_point.x, mean_point.y, mean_point.z);
  }
  size++;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "MeanPoint");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/tag_detections", 1000, callback);
  ros::spin();
  return 0;
}
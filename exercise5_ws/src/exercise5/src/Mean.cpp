#include <apriltag_ros/AprilTagDetection.h>
#include <apriltag_ros/AprilTagDetectionArray.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include <iostream>

#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "std_msgs/Time.h"

struct Point3D {
  double x, y, z;
};

bool rosbagPlaybackComplete = false;
bool rosbagPlaybackFinished = false;
Point3D mean_point = {0, 0, 0};
int size = 1;

void rosbagPlaybackStatusCallback(const std_msgs::Time& msg) {
  // Check if the received time indicates the end of rosbag playback
  if (msg.data == ros::TIME_MAX) {
    rosbagPlaybackComplete = true;
  }
}
void update_mean(Point3D& current_mean, const Point3D& new_point, int size) {
  current_mean.x += 1.0 / size * (new_point.x - current_mean.x);
  current_mean.y += 1.0 / size * (new_point.y - current_mean.y);
  current_mean.z += 1.0 / size * (new_point.z - current_mean.z);
}

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
  ros::Subscriber playback_status_sub =
      n.subscribe("/clock", 1, rosbagPlaybackStatusCallback);
  ros::Subscriber sub = n.subscribe("/tag_detections", 1000, callback);

  while (ros::ok() && !rosbagPlaybackComplete) {
    ros::spinOnce();
    ros::Duration(0.1).sleep();  // adjust the sleep duration as needed
  }
  // Unsubscribe from topics
  playback_status_sub.shutdown();
  sub.shutdown();
  ros::shutdown();

  // Display in the image
  std::string image_path =
      "/home/marco/IntelligentRobotics/exercise5_ws/src/exercise5/config/"
      "image_final.png";
  cv::Mat image = cv::imread(image_path);

  if (!image.empty()) {
    cv::Mat cameraMatrix =
        (cv::Mat_<double>(3, 3) << 964.3839721679688, 0.0, 1036.046875, 0.0,
         964.080810546875, 789.5423583984375, 0.0, 0.0, 1.0);

    cv::Mat distortionCoeffs =
        (cv::Mat_<double>(14, 1) << 0.7292001247406006, -2.826552152633667,
         0.000509547651745379, -0.0001749787770677358, 1.5794306993484497,
         0.6089710593223572, -2.66420316696167, 1.514512538909912, 0, 0, 0, 0,
         0);

    cv::Mat rvec = (cv::Mat_<double>(3, 1) << 0.0, 0.0, 0.0);
    cv::Mat tvec =
        (cv::Mat_<double>(3, 1) << mean_point.x, mean_point.y, mean_point.z);

    // 3D points in world coordinates
    cv::Point3d worldPoint(mean_point.x, mean_point.y, mean_point.z);

    // Project 3D points to 2D image coordinates
    std::vector<cv::Point2d> imagePoints;
    cv::projectPoints(std::vector<cv::Point3d>{worldPoint}, rvec, tvec,
                      cameraMatrix, distortionCoeffs, imagePoints);

    // Draw projected points on the image
    for (const auto& point : imagePoints) {
      cv::circle(image, point, 5, cv::Scalar(255, 255, 255), -1);
    }

    if (cv::imwrite("ProjectedPoints.png", image))
      std::cout << "Saved final image." << std::endl;

  } else
    std::cout << "Issue with image." << std::endl;

  return 0;
}
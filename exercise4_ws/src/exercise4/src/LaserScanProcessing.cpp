#include <math.h>

#include "dbscan.h"
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

// Structure representing a 2D point used for the threshold-based algorithm
struct Point2D {
  double x;
  double y;
};

// Struct necessary to work with the DBSCAN algorithm
struct vec2f {
  double data[2];
  double operator[](int idx) const { return data[idx]; }
};

class LaserScanProcessor {
 public:
   // Performs DBSCAN
  void DBSCAN_callback(const sensor_msgs::LaserScan::ConstPtr& reading) {
    this->reset();
    processLaserScan(reading);
  }

  // Performs threshold-based clustering algorithm
  void threshold_callback(const sensor_msgs::LaserScan::ConstPtr& reading) {
    this->reset();

    std::vector<float> ranges_data = reading->ranges;

    ROS_INFO("Scan start:");
    for (std::size_t i = 0; i < ranges_data.size(); ++i) {
      if (!std::isinf(ranges_data[i])) {
        int label;
        double angle_rad = i * angle_increment;
        double angle_deg = angle_rad / M_PI * 180;

        // Convert to x,y
        Point2D point;
        polar_to_cartesian(angle_rad, ranges_data[i], point);

        // At the beginning we don't have any clusters, thus this step is
        // mandatory
        if (number_of_clusters == 0) {
          this->clusters_means.push_back(point);
          this->size_of_clusters.push_back(1);
          this->number_of_clusters = 1;
          label = 0;
          this->classification.push_back(label);
        } else {
          // If clusters already exist, sweep through them
          // This flag is used to see if we need to create a new cluster
          bool found_cluster = false;

          for (int j = 0; j < number_of_clusters; j++) {
            if (euclidian_distance(clusters_means[j], point) < threshold) {
              this->size_of_clusters[j]++;
              update_cluster_mean(this->clusters_means[j], point,
                                  this->size_of_clusters[j]);
              found_cluster = true;
              label = j;
              this->classification.push_back(label);
              break;
            }
          }

          if (!found_cluster) {
            this->clusters_means.push_back(point);
            this->size_of_clusters.push_back(1);
            label = this->number_of_clusters;
            this->classification.push_back(label);
            this->number_of_clusters++;
          }
        }
        // ROS_INFO(
        //     "Angle: %.3f deg \t Value: %.3f [m] -> [%.3f, %.3f] \t Cluster: "
        //     "%d",
        //     angle_deg, ranges_data[i], point.x, point.y, label);
      }
    }
    ROS_INFO("Created %d clusters!", this->number_of_clusters);
    for (const auto& cluster : this->clusters_means)
      ROS_INFO("Cluster mean: (%.3f, %.3f)", cluster.x, cluster.y);
  }

 private:
  std::vector<int> classification;
  std::vector<Point2D> clusters_means;
  std::vector<int> size_of_clusters;
  double angle_increment = 0.0087389;
  double threshold = 0.5;
  u_int8_t number_of_clusters = 0;

  void polar_to_cartesian(double theta, double rho, Point2D& position) {
    position.x = rho * std::cos(theta);
    position.y = rho * std::sin(theta);
  }

  double euclidian_distance(Point2D p1, Point2D p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
  }

  void update_cluster_mean(Point2D& current_mean, const Point2D& new_point,
                           int size) {
    current_mean.x += 1.0 / size * (new_point.x - current_mean.x);
    current_mean.y += 1.0 / size * (new_point.y - current_mean.y);
  }
  void reset() {
    this->classification.clear();
    this->clusters_means.clear();
    this->size_of_clusters.clear();
    this->number_of_clusters = 0;
  }

  void processLaserScan(const sensor_msgs::LaserScan::ConstPtr& reading) {
    auto dbscan = DBSCAN<vec2f, double>();

    std::vector<float> ranges_data = reading->ranges;
    std::vector<vec2f> valid_data;

    ROS_INFO("Scan start:");
    for (std::size_t i = 0; i < ranges_data.size(); ++i) {
      if (!std::isinf(ranges_data[i])) {
        double angle_rad = i * angle_increment;
        double angle_deg = angle_rad / M_PI * 180;

        // Convert to x,y
        Point2D point;
        polar_to_cartesian(angle_rad, ranges_data[i], point);
        vec2f point_2f = {point.x, point.y};
        valid_data.push_back(point_2f);
      }
    }

    dbscan.Run(&valid_data, 2, 0.4f, 3);
    processClusters(dbscan, valid_data);
  }

  void processClusters(const DBSCAN<vec2f, double>& dbscan,
                       const std::vector<vec2f>& valid_data) {
    auto clusters = dbscan.Clusters;
    for (auto& cluster : clusters) {
      double mean_x = 0;
      double mean_y = 0;
      int size = 1;
      // Calculate the mean of each cluster
      for (auto& point : cluster) {
        mean_x += 1.0 / size * (valid_data[point][0] - mean_x);
        mean_y += 1.0 / size * (valid_data[point][1] - mean_y);
        size++;
      }
      ROS_INFO("Cluster mean: (%.3f, %.3f)", mean_x, mean_y);
    }
  }
};

int main(int argc, char** argv) {
  ros::init(argc, argv, "laserscan_subscriber");
  ros::NodeHandle n;
  LaserScanProcessor lsp;
  ros::Subscriber sub =
      n.subscribe("/scan", 1000, &LaserScanProcessor::DBSCAN_callback, &lsp);
  ros::spin();
  return 0;
}

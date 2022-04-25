#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>

#include <vector>

#include "math.h"


#define ANGLE_RANGE 270
#define PI 3.1415927

class SubscribeAndPublish {
public:
    SubscribeAndPublish() {
        //Topic you want to publish
        pub_ = n_.advertise<std_msgs::Float32>("/nav", 1000);

        //Topic you want to subscribe
        sub_ = n_.subscribe("/scan", 1000, &SubscribeAndPublish::callback, this);
    }

    

    void find_closest_indx(int start_i, int end_i, int* closest_i) {
        unsigned int closest_i = start_i;
        double closest_distance = 2147483647;
        for (unsigned int i = start_i; i <= end_i; i++) {
            double distance = ranges[i - 2] + ranges[i - 1] + ranges[i] + ranges[i + 1] + ranges[i + 2];
            if (distance < closest_distance) {
                closest_distance = distance;
                closest_i = i;
            }
        }
    }

    void create_safety_bubble(int closest_i, int radius) {
        for (unsigned int i = closest_i - radius; i < closest_i + radius + 1; i++) {
            ranges[i] = 0.0;
        }
    }

    void find_best_point(int start, int end) {

    }

    void find_max_gap(int min_i, int max_i, int* start, int* end) {
        unsigned int current_start = min_i - 1;
        unsigned int duration = 0;
        unsigned int longest_duration = 0;
        for (unsigned int i = min_i; i <= max_i; i++) {
            if (current_start < min_i) {
                if (ranges[i] > 0.0) {
                    current_start = i;
                }
            } else if (ranges[i] <= 0.0) {
                duration = i - current_start;
                if (duration > longest_duration) {
                    longest_duration = duration;
                    start = current_start;
                    end = i - 1;
                }
                current_start = min_i - 1;
            }
        }
        if (current_start >= min_i) {
            duration = max_i + 1 - current_start;
            if (duration > longest_duration) {
                longest_duration = duration;
                start = current_start;
                end = max_i;
            }
        }
    }

    void reactive_control() {
        std_msgs::Float32 angle;
        angle.data = angle;
        pub_.publish(angle);
    }


    void callback(const sensor_msgs::LaserScan& lidar_info) {
        //  Preprocess the LiDAR scan array. Expert implementation includes:
        //  1.Setting each value to the mean over some window
        //  2.Rejecting high values (eg. > 3m)
        ranges = std::vector<double>(std::begin(lidar_info.ranges), std::end(lidar_info.ranges));
        double min_angle = -70 / 180.0 * PI;
        unsigned int min_i = (unsigned int)(std::floor((min_angle - lidar_info.angle_min) / lidar_info.angle_increment));
        double max_angle = 70 / 180.0 * PI;
        unsigned int max_i = (unsigned int)(std::ceil((max_angle - lidar_info.angle_min) / lidar_info.angle_increment));
        for (unsigned int i = min_i; i <= max_i; i++) {
            if (std::isinf(lidar_info.ranges[i]) || std::isnan(lidar_info.ranges[i])) {
                ranges[i] = 0.0;
            } 
        }

        int closest_i;
        int start = min_i;
        int end = min_i;

        SubscribeAndPublish::find_closest_i(min_i, max_i, &closest_i);
        //tune the radius of the safety bubble!
        SubscribeAndPublish::create_safety_bubble(closest_i, 100);
        SubscribeAndPublish::find_max_gap(min_i, max_i, &start, &end)

        
        //Follow the Gap!
        double current_max = 0.0;
        for (unsigned int i = start; i <= end; i++) {
            if (ranges[i] > current_max) {
                current_max = ranges[i];
                angle = lidar_info.angle_min + i * lidar_info.angle_increment;
            } else if (ranges[i] == current_max) {
                if (std::abs(lidar_info.angle_min + i * lidar_info.angle_increment) < std::abs(angle)) {
                    angle = lidar_info.angle_min + i * lidar_info.angle_increment;
                }
            }
        }

        SubscribeAndPublish::reactive_control();
    }

    

private:
    ros::NodeHandle n_;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    double angle;
    std::vector<double> ranges;

};  // End of class SubscribeAndPublish

int main(int argc, char** argv) {
    //Initiate ROS
    ros::init(argc, argv, "reactive_gap_follower");
    SubscribeAndPublish SAPObject;
    ros::spin();

    return 0;
}

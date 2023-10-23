#include "ros/ros.h"
#include "intro_tutorial/msg1.h"
#include <sstream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "example2_a");
    ros::NodeHandle n;
    ros::Publisher pub =
        n.advertise<intro_tutorial::msg1>("message",
                                              1000);

    ros::Rate loop_rate(1);


    while (ros::ok())
    {
        intro_tutorial::msg1 msg;
        msg.A = 1;
        msg.B = 2;
        msg.C = 69;
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
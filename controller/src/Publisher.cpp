//
// Created by wjr on 25-4-10.
//
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char* argv[])
{
    ros::init(argc,argv,"publish_node");
    ros::NodeHandle nh;
    geometry_msgs::Twist twist;
    twist.linear.x=2.0;
    twist.linear.y=0.0;
    twist.linear.z=0.0;
    twist.angular.x=0.0;
    twist.angular.y=0.0;
    twist.angular.z=0.0;
    ros::Publisher publisher=nh.advertise<geometry_msgs::Twist>("/cmd_vel",10);
    ros::Rate rate(5);
    while (ros::ok())
    {
        publisher.publish(twist);
        ros::spinOnce();
        rate.sleep();
    }
}

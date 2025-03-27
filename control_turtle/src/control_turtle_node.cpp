//
// Created by wjr on 25-3-6.
//
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
int main(int argc,char *argv[]) {
    ros::init(argc,argv,"control_turtle_node");
    ros::NodeHandle nh;
    ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    geometry_msgs::Twist twist;
    twist.linear.x=1.0;
    twist.linear.y=0.0;
    twist.linear.z=0.0;
    twist.angular.x=0.0;
    twist.angular.y=0.0;
    twist.angular.z=1.0;
    ros::Rate rate(10);
    while (ros::ok()) {
        pub.publish(twist);
        rate.sleep();
    }
}
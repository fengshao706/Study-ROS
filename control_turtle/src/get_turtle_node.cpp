//
// Created by wjr on 25-3-9.
//
#include "ros/ros.h"
#include "turtlesim/Pose.h"
void get_message(const turtlesim::Pose::ConstPtr &msg) {
    ROS_INFO("the x position is %f%s%f",msg->x,"the y position is",msg->y);
}

int main(int argc,char *argv[]) {
    ros::init(argc,argv,"get_turtle_node");
    ros::NodeHandle nh;
    ros::Subscriber sub=nh.subscribe("/turtle1/pose",10,get_message);
    ros::spin();
}

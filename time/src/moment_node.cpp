//
// Created by wjr on 25-3-9.
//
#include "ros/ros.h"
int main(int argc, char *argv[]) {
    ros::init(argc,argv,"moment_node");
    ros::NodeHandle nh;
    ros::Time right_now=ros::Time::now();
    ROS_INFO("%f",right_now.toSec());//获取距离1970年过去的时间
    ros::Time set(100);
    ROS_INFO("%f",set.toSec());
}

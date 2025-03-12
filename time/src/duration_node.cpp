//
// Created by wjr on 25-3-9.
//
#include "ros/ros.h"

void test(const ros::TimerEvent&timer) {
    ROS_INFO("test");
}

int main(int argc, char *argv[]) {
    ros::init(argc,argv,"duration_node");
    ros::NodeHandle nh;
    ros::Duration duration(5);
    ROS_INFO("%d",duration.sec);
    ROS_INFO("begin to sleep");
    duration.sleep();
    ROS_INFO("stop to sleep");
    ros::Timer timer=nh.createTimer(ros::Duration(2),test);
    ros::spin();
}

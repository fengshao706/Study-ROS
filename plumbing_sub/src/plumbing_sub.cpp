//
// Created by wjr on 25-3-3.
//
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sstream"
void doMsgs(const std_msgs::String::ConstPtr &msg) {//回调函数
    ROS_INFO("The sub data %s",msg->data.c_str());
}

int main(int argc , char *argv[]) {
    ros::init(argc,argv,"plumbing_sub");
    ros::NodeHandle nh;
    ros::Subscriber sub= nh.subscribe("plumbing",10,doMsgs);
    ros::spin();
}

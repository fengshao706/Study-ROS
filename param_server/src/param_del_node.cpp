//
// Created by wjr on 25-3-6.
//
#include "ros/ros.h"

int main(int argc, char *argv[]) {
    ros::init(argc,argv,"param_del_node");
    ros::NodeHandle nh;
    bool test1=nh.deleteParam("radius");
    if (test1==1){
    ROS_INFO("delete successfully!");
    }else {
        ROS_INFO("delete fail");
    }
}

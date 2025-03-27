//
// Created by wjr on 25-3-9.
//
#include "ros/ros.h"
int main(int argc,char *argv[]) {
    ros::init(argc,argv,"set_background_param_node");
    ros::NodeHandle nh;
    nh.setParam("/turtlesim/background_r",255);
    nh.setParam("/turtlesim/background_g",255);//利用参数服务器设置乌龟界面的背景颜色
    nh.setParam("/turtlesim/background_b",255);
    ROS_INFO("ros param is running");

}

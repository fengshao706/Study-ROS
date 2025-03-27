//
// Created by wjr on 25-3-5.
//
#include "ros/ros.h"
int main(int argc,char *argv[]) {
    ros::init(argc,argv,"param_set_node");
    ros::NodeHandle nh;
    nh.setParam("type","robot1");//使用节点句柄设定参数
    nh.setParam("radius",1.86);
    ros::param::set("type_param","robot2");//使用param函数设定参数
    ros::param::set("radius_param",0.8);//要修改就直接用新的设定覆盖之前的操作
    ROS_INFO("param server is running");
}
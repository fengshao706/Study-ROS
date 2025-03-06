//
// Created by wjr on 25-2-26.
//
#include "ros/ros.h"
int main(int argc,char *argv[]) {
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"helloworld_node");
    ROS_INFO("helloworld!哈哈");
    return 0;
}

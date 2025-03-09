//
// Created by wjr on 25-2-26.
//
#include "ros/ros.h"
int main(int argc,char *argv[]) {//argc封装参数个数 argv是封装参数的数组
    setlocale(LC_ALL,"");//定义语言
    ros::init(argc,argv,"helloworld_node");
    ROS_INFO("helloworld!哈哈");
    return 0;
}

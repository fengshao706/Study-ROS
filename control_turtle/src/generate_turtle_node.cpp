//
// Created by wjr on 25-3-9.
//
#include "ros/ros.h"
#include "turtlesim/Spawn.h"
int main(int argc,char *argv[]) {
    ros::init(argc,argv,"generate_turtle_node");
    ros::NodeHandle nh;
    ros::ServiceClient client=nh.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn spawn;
    spawn.request.x=5.0;
    spawn.request.y=3.0;
    spawn.request.theta=1.0;//编辑信息
    spawn.request.name="wjr";
    client.waitForExistence();//等待客户端响应
    bool result=client.call(spawn);//发送信息
    if (result==1) {
        ROS_INFO("generate successfully");
    }else {
        ROS_INFO("generate fail");
    }
}

//
// Created by wjr on 25-3-4.
//
#include "ros/ros.h"
#include "plumbing_sub/self_defined_sub.h"
void doMsg(const plumbing_sub::self_defined_sub::ConstPtr & msg) {
    ROS_INFO("the message is %s,%d,%.2f",msg->name.c_str(),msg->age,msg->height);
}

int main(int argc,char *argv[]) {
    ros::init(argc,argv,"self_defined_sub");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<plumbing_sub::self_defined_sub>("plumbing",10,doMsg);
    ros::spin();
}

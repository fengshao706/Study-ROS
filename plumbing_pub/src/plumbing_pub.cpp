//
// Created by wjr on 25-2-27.
//该文件是测试ROS的话题通信的发布方实现
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
int main(int argc,char *argv[]) {
    ros::init(argc,argv,"plumbing_pub_node");//初始化ROS节点
    ros::NodeHandle nh;//创建节点句柄
    ros::Publisher pub=nh.advertise<std_msgs::String>("plumbing",10);//使用节点句柄创建发布者对象
    ROS_INFO("register successfully");
    std_msgs::String msg;//创建被发布的消息
    ros::Rate rate(1);
    int count =0;
    ros::Duration(2.0).sleep();//在注册的时候让系统休眠，使得订阅者不至于因为发布者没有注册完成导致无法接收到前面的数据
    while (ros::ok()) {
        count ++;
        std::stringstream ss;
        ss <<"hello --->"<< count;
        msg.data = ss.str();//定义要发布的数据
        pub.publish(msg);//发布数据
        rate.sleep();
    }
    return 0;
}

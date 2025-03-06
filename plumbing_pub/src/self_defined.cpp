//
// Created by wjr on 25-3-3.
//
#include "ros/ros.h"
#include "plumbing_pub/self_defined.h"//引入自定义数据类型的头文件
int main(int argc,char *argv[]) {
    ros::init(argc,argv,"self_defined_node");
    ros::NodeHandle nh;
    ros::Publisher pub=nh.advertise<plumbing_pub::self_defined>("plumbing",10);//这里的泛型数据类型是自定义的数据类型
    ROS_INFO("register successfully!");
    plumbing_pub::self_defined msg;//创建数据名称
    msg.name="LiHua";
    msg.age=1;      //为数据赋值
    msg.height=52.1;
    ros::Rate rate(1);//设定发布频率
    ros::Duration(2).sleep();
    while (ros::ok()) {
        pub.publish(msg);
        msg.age+=1;
        rate.sleep();
    }
    return 0;
}

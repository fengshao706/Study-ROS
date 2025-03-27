//
// Created by wjr on 25-3-4.
//
#include "ros/ros.h"
#include "plumbing_server_client/AddInts.h"
int main(int argc,char *argv[]) {
    if (argc!=3) {
        ROS_INFO("Input false");//判断输入的参数是否符合要求
        return 1;
    }
    ros::init(argc,argv,"plumbing_client_node");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<plumbing_server_client::AddInts>("services");
    plumbing_server_client::AddInts add;
    add.request.num1=atoi(argv[1]);
    add.request.num2=atoi(argv[2]);//通过输入的参数为请求数据赋值
    client.waitForExistence();//当服务端未启动时不直接抛出异常而是等待服务器端启动
    bool result = client.call(add);//发送数据
    if (result==1) {
        ROS_INFO("Successfully!Result is %d",add.response.sum);
    }else {
        ROS_INFO("Fail");
    }
}

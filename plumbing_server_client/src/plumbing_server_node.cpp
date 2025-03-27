//
// Created by wjr on 25-3-4.
//
#include "ros/ros.h"
#include "plumbing_server_client/AddInts.h"
bool AddNums( plumbing_server_client::AddInts::Request &request,
            plumbing_server_client::AddInts::Response &response) {
    ROS_INFO("the request data is %d%s%d",request.num1," and ",request.num2);
    int sum=request.num1+request.num2;
    response.sum=sum;
    ROS_INFO("the response data is %d",response.sum);
    return true;
}

int main(int argc,char *argv[]) {
    ros::init(argc,argv,"services");
    ROS_INFO("the server is running...");
    ros::NodeHandle nh;
    ros::ServiceServer server=nh.advertiseService("services",AddNums);
    ros::spin();
}

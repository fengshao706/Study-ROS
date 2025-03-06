//
// Created by wjr on 25-3-5.
//
#include "ros/ros.h"
int main(int argc,char *argv[]) {
    ros::init(argc,argv,"param_get_node");
    ros::NodeHandle nh;
    double radius=nh.param("radius",0.0);//使用nh.param获取参数的值
    ROS_INFO("radius = %.2f",radius);
    double radius_param;
    bool radius_param_get=nh.getParam("radius_param",radius_param);//使用nh.getParam获取参数的值
    if (radius_param_get==1) {//判断是否成功获取到值
        ROS_INFO("radius_param = %.2f",radius_param);
    }else {
        ROS_INFO("can not get radius_param");
    }
    std::vector<std::string> names;
    nh.getParamNames(names);//获取参数的名称
    for (auto && name:names) {
        ROS_INFO("the vector param is %s",name.c_str());//遍历获取到的参数
    }
    
}

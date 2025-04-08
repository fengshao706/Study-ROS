//
// Created by wjr on 25-4-8.
//
#include "ros/ros.h"
#include "controller_manager/controller_manager.h"
#include "hardware_interface/joint_command_interface.h"
#include "hardware_interface/joint_state_interface.h"
#include "hardware_interface/robot_hw.h"
#include "geometry_msgs/Twist.h"

class WheelHardware : public hardware_interface::RobotHW
{
public:
    WheelHardware()
    {
        for (int i=0;i<4;i++)
        {
            std::string joint_name="wheelNum_"+std::to_string(i+1);
            hardware_interface::JointStateHandle joint_state_handle(joint_name,&pos_[i],&vel_[i],&eff_[i]);//定义位置关节句柄
            joint_state_interface_.registerHandle(joint_state_handle);//注册位置关节句柄
            hardware_interface::JointHandle joint_handle(joint_state_interface_.getHandle(joint_name),&cmd_vel_[i]);//定义速度关节句柄
            velocity_joint_interface_.registerHandle(joint_handle);//注册速度关节句柄
        }
        registerInterface(&joint_state_interface_);
        registerInterface(&velocity_joint_interface_);//注册接口到硬件
    }
private:
    hardware_interface::JointStateInterface joint_state_interface_;
    hardware_interface::VelocityJointInterface velocity_joint_interface_;

    double pos_[2]={0.0,0.0};
    double vel_[2]={0.0,0.0};
    double eff_[2]={0.0,0.0};
    double cmd_vel_[2]={0.0,0.0};
};

class velocityController
{
public:
    velocityController() : nh("~")//控制器初始化
    {
        publisher_=nh.advertise<geometry_msgs::Twist>("/cmd_vel",10);
        subscriber_=nh.subscribe("/cmd_vel",10,&velocityController::callBack,this);
    }
    void setVelocity(double x)//设定速度
    {
        geometry_msgs::Twist twist;
        twist.linear.x=x;
        twist.linear.y=0;
        twist.linear.z=0;
        twist.angular.x=0;
        twist.angular.y=0;
        twist.angular.z=0;
        publisher_.publish(twist);
    }
    void callBack(const geometry_msgs::Twist::ConstPtr &msg)
    {
        vel=msg->linear.x;
    }
    void getVelocity()
    {
        ROS_INFO("The velocity is %f",vel);
    }
private:
    ros::Publisher publisher_;
    ros::Subscriber subscriber_;
    double vel;
    ros::NodeHandle nh;
};
int main(int argc, char* argv[])
{
    ros::init(argc,argv,"demo01_node");
    ros::NodeHandle nh;
    WheelHardware wheel_hardware;//创建硬件接口
    controller_manager::ControllerManager controller_manager(&wheel_hardware,nh);
    velocityController velocity_controller;
    ros::Rate rate(2);
    while (ros::ok())
    {
        velocity_controller.setVelocity(2);
        ros::spinOnce();
        velocity_controller.getVelocity();
        rate.sleep();
    }
}



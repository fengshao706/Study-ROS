//
// Created by wjr on 25-4-10.
//
#include <controller_manager/controller_manager.h>
#include <geometry_msgs/Twist.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>

#include "ros/ros.h"
#include "hardware_interface/robot_hw.h"
#include "controller_interface/controller.h"
#include <pluginlib/class_list_macros.h>

class BaseHardwareInterface : public hardware_interface::RobotHW  //创建硬件接口类，使其继承HW类
{
public:
    BaseHardwareInterface() : nh("~")  //构造函数中将一些需要的东西初始化
    {
        hardware_interface::JointStateHandle wheel_1("wheel_1",&pos,&vel,&eff);
        joint_state_interface_.registerHandle(wheel_1);//设置并注册一个名字为wheel_1的关节
        registerInterface(&joint_state_interface_);

        hardware_interface::JointHandle wheel_1_cmd(wheel_1,&cmd_vel_);
        velocity_joint_interface_.registerHandle(wheel_1_cmd);
        registerInterface(&velocity_joint_interface_);
        subscriber_=nh.subscribe("cmd_vel",10,&BaseHardwareInterface::callBack,this);
    }
    void read(const ros::Time&, const ros::Duration&) override
    {
        vel=temp_vel;//将callback函数里面获取到的关节信息传给read函数
    }
    void write(const ros::Time&, const ros::Duration&) override {
        // 将 cmd_vel_ 发送到实际硬件（此处模拟发送）
        ROS_INFO("Command velocity: %f", cmd_vel_);
    }
    double cmd_vel_;
private:
    double pos=0.0;
    double vel=0.0;
    double eff=0.0;
    double temp_vel=0.0;
    hardware_interface::JointStateInterface joint_state_interface_;
    hardware_interface::VelocityJointInterface velocity_joint_interface_;
    ros::Subscriber subscriber_;
    ros::NodeHandle nh;

    void callBack(const geometry_msgs::Twist::ConstPtr &msg)
    {
        temp_vel=msg->linear.x;//获取发布者节点发布的速度消息
    }
};
namespace controller
{
    class VelocityController : public controller_interface::Controller<hardware_interface::VelocityJointInterface>//创建控制器
    {
    public:
        bool init(hardware_interface::VelocityJointInterface* hw, ros::NodeHandle&root_nh, ros::NodeHandle&controller_nh) override
        {
            hw_=hw;//将传入的hw赋给私有的hw_

            if (!hw_)
            {
                ROS_ERROR("HW_ is null");
                return false;
            }

            ROS_INFO("Init");
            return true;
        }
        void starting(const ros::Time&) override
        {
            ROS_INFO("Starting now");
        }
        void stopping(const ros::Time& time)
        {

        }

        void update(const ros::Time& time, const ros::Duration& period) override
        {
            double jointVel=hw_->getHandle("wheel_1").getVelocity();//获取速度
            hw_->getHandle("wheel_1").setCommand(jointVel+0.001);//测试案例，粗暴地将速度加上0.001后传给硬件接口
            ROS_INFO("UPDATE");
        }
        ros::NodeHandle nh;
    private:
        hardware_interface::VelocityJointInterface *hw_;
        hardware_interface::JointStateHandle joint_state_handle_;
    };
}
PLUGINLIB_EXPORT_CLASS(controller::VelocityController, controller_interface::ControllerBase)
int main(int argc, char* argv[])
{
    ros::init(argc,argv,"demo02_node");
    ros::NodeHandle nh;

    BaseHardwareInterface base_hardware_interface;
    controller_manager::ControllerManager cm(&base_hardware_interface);
    std::vector<std::string> start_controllers = {"VelocityController"};
    std::vector<std::string> stop_controllers;
    if (cm.loadController("VelocityController"))
    {
        ROS_INFO("Successful to load VelocityController!");
    }else
    {
        ROS_ERROR("Failed to load VelocityController!");
    }
    ros::Duration(2).sleep();
    ROS_INFO("Starting controller");
    if (!cm.switchController(start_controllers, stop_controllers, controller_manager_msgs::SwitchController::Request::BEST_EFFORT))
    {
        ROS_ERROR("Failed to start VelocityController");
    }else
    {
        ROS_INFO("Successful to start VelocityController");
    }
    ros::Rate rate(20);
    while (ros::ok())
    {
        base_hardware_interface.read(ros::Time::now(),ros::Duration(0.05));
        cm.update(ros::Time::now(),ros::Duration(0.05));
        base_hardware_interface.write(ros::Time::now(),ros::Duration(0.05));
        ros::spinOnce();
        rate.sleep();
    }
}


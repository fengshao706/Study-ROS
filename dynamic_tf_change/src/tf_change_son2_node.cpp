//
// Created by wjr on 25-3-20.
//在ROS的 tf2_ros::Buffer 中，buffer.transform(input_pose,  "target_frame") 方法的作用是将输入的位姿（input_pose）
//从原始坐标系转换到目标坐标系（"target_frame"）下的新位姿
#include "ros/ros.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/PoseStamped.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"


int main(int argc, char *argv[]) {
    ros::init(argc,argv,"tf_change_son2_node");
    ros::NodeHandle nh;
    tf2_ros::TransformBroadcaster transform_broadcaster;//创建广播器
    geometry_msgs::PoseStamped pose_stamped;//创建位姿输入对象
    geometry_msgs::PoseStamped pose_stamped_out;//创建位姿输出对象
    tf2::Quaternion quaternion;//创建欧拉角转换为四元数的数学运算器对象
    tf2_ros::Buffer buffer;//创建缓存对象，目的是存储tf系统中广播出来的位置信息
    tf2_ros::TransformListener transform_listener(buffer);//创建接收器对象
    geometry_msgs::TransformStamped transform_stamped;//创建为了广播坐标的转换器对象
    pose_stamped.header.frame_id="son1";
    pose_stamped.header.stamp=ros::Time(0);
    pose_stamped.pose.position.x=1.3;
    pose_stamped.pose.position.y=0.3;
    pose_stamped.pose.position.z=2.7;//该代码块是设置相对于son1的位姿信息
    quaternion.setRPY(0,0,0);
    pose_stamped.pose.orientation.x=quaternion.getX();
    pose_stamped.pose.orientation.y=quaternion.getY();
    pose_stamped.pose.orientation.z=quaternion.getZ();
    pose_stamped.pose.orientation.w=quaternion.getW();
    ros::Duration(2).sleep();//等待
    pose_stamped_out=buffer.transform(pose_stamped,"world");//将前面相对于son1的坐标转换为相对于world的坐标
    transform_stamped.child_frame_id="son2";
    transform_stamped.header.frame_id="world";
    transform_stamped.transform.translation.x=pose_stamped_out.pose.position.x;
    transform_stamped.transform.translation.y=pose_stamped_out.pose.position.y;
    transform_stamped.transform.translation.z=pose_stamped_out.pose.position.z;
    transform_stamped.transform.rotation.x=pose_stamped_out.pose.orientation.x;//该代码块是设置发布者对象
    transform_stamped.transform.rotation.y=pose_stamped_out.pose.orientation.y;
    transform_stamped.transform.rotation.z=pose_stamped_out.pose.orientation.z;
    transform_stamped.transform.rotation.w=pose_stamped_out.pose.orientation.w;
    ros::Rate rate(1);
    while (ros::ok()) {
        transform_stamped.header.stamp=ros::Time::now();
        transform_broadcaster.sendTransform(transform_stamped);//发布
        rate.sleep();
        ros::spinOnce();
    }
}
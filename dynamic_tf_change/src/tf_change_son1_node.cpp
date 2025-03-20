//
// Created by wjr on 25-3-20.
//
#include "ros/ros.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/Transform.h"
#include "geometry_msgs/TransformStamped.h"

int main(int argc, char *argv[]) {
    ros::init(argc,argv,"tf_change_son1_node");
    ros::NodeHandle nh;
    tf2_ros::TransformBroadcaster transform_broadcaster;
    geometry_msgs::TransformStamped transform_stamped;
    tf2::Quaternion quaternion;
    transform_stamped.header.frame_id="world";
    transform_stamped.child_frame_id="son1";
    transform_stamped.transform.translation.x=1.2;
    transform_stamped.transform.translation.y=1.8;
    transform_stamped.transform.translation.z=0.6;
    quaternion.setRPY(0,0,1);
    transform_stamped.transform.rotation.x=quaternion.getX();
    transform_stamped.transform.rotation.y=quaternion.getY();
    transform_stamped.transform.rotation.z=quaternion.getZ();
    transform_stamped.transform.rotation.w=quaternion.getW();
    ros::Rate rate(1);
    while (ros::ok()) {
        transform_stamped.header.stamp=ros::Time::now();//时间戳需要在循环内部设定，以确保每次使用的都是新的时间戳
        transform_broadcaster.sendTransform(transform_stamped);
        rate.sleep();
        ros::spinOnce();
    }
}

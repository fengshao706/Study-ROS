//
// Created by wjr on 25-3-12.
//
#include "ros/ros.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"

int main(int argc, char *argv[]) {
    ros::init(argc,argv,"static_tf_change_pub_node");
    ros::NodeHandle nh;
    tf2_ros::StaticTransformBroadcaster pub;//创建发布者对象
    geometry_msgs::TransformStamped tfs;//创建坐标标记对象
    tfs.header.stamp =ros::Time::now();//设定时间戳
    tfs.header.frame_id="base_link";//相对坐标系中被参考的那一个
    tfs.child_frame_id="laser";
    tfs.transform.translation.x=0.2;
    tfs.transform.translation.y=0.0;//设置变换的位置坐标
    tfs.transform.translation.z=0.5;
    tf2::Quaternion quaternion;//创建四元数对象
    quaternion.setRPY(0,0,0);
    tfs.transform.rotation.x=quaternion.getX();
    tfs.transform.rotation.y=quaternion.getY();
    tfs.transform.rotation.z=quaternion.getZ();//设置变换的角度坐标
    tfs.transform.rotation.w=quaternion.getW();
    pub.sendTransform(tfs);//话题是/tf_static
    ros::spin();
}


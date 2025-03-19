//
// Created by wjr on 25-3-19.
//
#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"

void getPose(const turtlesim::Pose::ConstPtr &pose) {
    static tf2_ros::TransformBroadcaster transform_broadcaster;
    static geometry_msgs::TransformStamped transform_stamped;
    static tf2::Quaternion quaternion;//实例化对象时使用静态方法，减少资源占用
    transform_stamped.header.frame_id="world";//父世界坐标
    transform_stamped.header.stamp=ros::Time::now();//设定时间戳
    transform_stamped.child_frame_id="turtle1";//子坐标名字
    transform_stamped.transform.translation.x=pose->x;
    transform_stamped.transform.translation.y=pose->y;
    transform_stamped.transform.translation.z=0;
    quaternion.setRPY(0,0,pose->theta);//将欧拉角转换为四元数
    transform_stamped.transform.rotation.x=quaternion.getX();
    transform_stamped.transform.rotation.y=quaternion.getY();
    transform_stamped.transform.rotation.z=quaternion.getZ();
    transform_stamped.transform.rotation.w=quaternion.getW();//获取四元数
    transform_broadcaster.sendTransform(transform_stamped);//发布对象
}

int main(int argc,char * argv[]) {
    ros::init(argc,argv,"dynamic_tf_change_pub_node");
    ros::NodeHandle nh;
    ros::Subscriber subscriber=nh.subscribe("/turtle1/pose",10,getPose);
    ros::spin();
}
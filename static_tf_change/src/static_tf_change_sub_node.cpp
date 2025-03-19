//
// Created by wjr on 25-3-13.
//任务目标：将障碍物的坐标点转换为相对小车底盘的坐标点,即将laser坐标系下的点转换为相对与base_link坐标系的点
#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"//缓存
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

int main(int argc, char *argv[]) {
    ros::init(argc,argv,"static_tf_change_sub_node");
    ros::NodeHandle nh;
    tf2_ros::Buffer buffer;//创建缓存对象，用于存储收到的坐标变换数据
    tf2_ros::TransformListener transform_listener(buffer);//创建接收者对象
    geometry_msgs::PointStamped point_stamped_in;//坐标信息的输入
    geometry_msgs::PointStamped point_stamped_out;//坐标信息的输出
    point_stamped_in.header.frame_id="laser";
    point_stamped_in.header.stamp=ros::Time::now();
    point_stamped_in.point.x=2.0;
    point_stamped_in.point.y=3.0;
    point_stamped_in.point.z=5.0;
    ros::Rate rate(1);
    ros::Duration(2).sleep();//通过休眠使得保证订阅者节点在订阅到坐标系之后再进行转换
    while (ros::ok()) {
        point_stamped_out=buffer.transform(point_stamped_in,"base_link");
        ROS_INFO("The changed coordinates(%f,%f,%f)   The frame_id%s",
            point_stamped_out.point.x,
            point_stamped_out.point.y,
            point_stamped_out.point.z,
            point_stamped_out.header.frame_id.c_str()

        );
        rate.sleep();
        ros::spinOnce();
    }
}


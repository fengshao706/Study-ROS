//
// Created by wjr on 25-3-19.
//
#include "ros/ros.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
int main(int argc, char *argv[]) {
    ros::init(argc,argv,"dynamic_tf_change_sub_node");
    ros::NodeHandle nh;
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener transform_listener(buffer);
    geometry_msgs::PointStamped point_stamped_in;
    geometry_msgs::PointStamped point_stamped_out;
    point_stamped_in.header.frame_id="turtle1";
    point_stamped_in.header.stamp=ros::Time(0);
    point_stamped_in.point.x=0;
    point_stamped_in.point.y=0;
    point_stamped_in.point.z=3;
    ros::Duration(2).sleep();
    ros::Rate rate(1);
    while (ros::ok()) {
        point_stamped_out=buffer.transform(point_stamped_in,"world");
        try {
            ROS_INFO("The changed position %f%s%f%s%f%s",
                point_stamped_out.point.x,"\n",point_stamped_out.point.y,"\n",point_stamped_out.point.z,"\n");
        }catch (const std::exception &e) {
            ROS_INFO("The exception is%s",e.what());
        }
            rate.sleep();
        ros::spinOnce();
    }


}

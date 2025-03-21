//
// Created by wjr on 25-3-21.
//
#include "ros/ros.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/TransformStamped.h"

void transformTF() {
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener transform_listener(buffer);
    geometry_msgs::TransformStamped transform_stamped_oldTurtle;
    geometry_msgs::TransformStamped transform_stamped_newTurtle;
    transform_stamped_oldTurtle=buffer.lookupTransform("world","oldTurtle",ros::Time::now());
    transform_stamped_newTurtle=buffer.lookupTransform("world","newTurtle",ros::Time::now());

}

int main(int argc, char *argv[]) {
    ros::init(argc,argv,"control_turtle_catch_up_node");
    ros::NodeHandle nh;
}

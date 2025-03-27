//
// Created by wjr on 25-3-21.
//
#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Transform.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "turtlesim/Spawn.h"


void publishTF(const turtlesim::Pose &pose,std::string child_frame_id) {
    tf2::Quaternion quaternion;
    static tf2_ros::TransformBroadcaster transform_broadcaster;
    geometry_msgs::TransformStamped transform_stamped;
    transform_stamped.header.frame_id="world";
    transform_stamped.header.stamp=ros::Time::now();
    transform_stamped.child_frame_id=child_frame_id;
    transform_stamped.transform.translation.x=pose.x;
    transform_stamped.transform.translation.y=pose.y;
    transform_stamped.transform.translation.z=0;
    quaternion.setRPY(0,0,pose.theta);
    transform_stamped.transform.rotation.x=quaternion.getX();
    transform_stamped.transform.rotation.y=quaternion.getY();
    transform_stamped.transform.rotation.z=quaternion.getZ();
    transform_stamped.transform.rotation.w=quaternion.getW();
    transform_broadcaster.sendTransform(transform_stamped);
}

void oldTurtleCallback(const turtlesim::Pose &pose) {
    publishTF(pose,"oldTurtle");
}

void newTurtleCallback(const turtlesim::Pose &pose) {
    publishTF(pose,"newTurtle");
}

int main(int argc, char *argv[]) {
    ros::init(argc,argv,"publish_turtle_tf_node");
    ros::NodeHandle nh;
    ros::ServiceClient service_client=nh.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn spawn;
    spawn.request.x=3;
    spawn.request.y=3;
    spawn.request.theta=0;
    spawn.request.name="new";
    ros::Duration(1).sleep();
    bool result=service_client.call(spawn);
    if (result==1) {
        ROS_INFO("successfully!");
    }else {
        ROS_INFO("fail");
    }
    ros::MultiThreadedSpinner spinner(2);
    ros::Subscriber oldTurtleSubscriber=nh.subscribe("/turtle1/pose",10,oldTurtleCallback);
    ros::Subscriber newTurtleSubscriber=nh.subscribe("/new/pose",10,newTurtleCallback);
    spinner.spin();
}

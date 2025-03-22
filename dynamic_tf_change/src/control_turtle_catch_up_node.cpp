//
// Created by wjr on 25-3-21.
//
#include "ros/ros.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "geometry_msgs/Twist.h"

geometry_msgs::TransformStamped transformTFReturnOldTurtle() {
    static tf2_ros::Buffer buffer;
    static tf2_ros::TransformListener transform_listener(buffer);
    geometry_msgs::TransformStamped transform_stamped_oldTurtle;
    ros::Duration(0.5).sleep();
    transform_stamped_oldTurtle=buffer.lookupTransform("world","oldTurtle",ros::Time(0));
    return transform_stamped_oldTurtle;
}

geometry_msgs::TransformStamped transformTFReturnNewTurtle() {
    static tf2_ros::Buffer buffer;
    static tf2_ros::TransformListener transform_listener(buffer);
    geometry_msgs::TransformStamped transform_stamped_newTurtle;
    ros::Duration(0.5).sleep();
    transform_stamped_newTurtle=buffer.lookupTransform("world","newTurtle",ros::Time(0));
    return transform_stamped_newTurtle;
}

geometry_msgs::Twist controller() {
    double kp=0.5f;
    double ki=0.5f;
    double kd=0.5f;
    double oldROLL ,oldPITCH ,oldYAW=0.0f;
    double newROLL ,newPITCH ,newYAW=0.0f;
    double pre_error_x=0.0f,pre_error_y=0.0f,pre_error_z=0.0f,pre_error_t =0.0f;
    double current_error_x,current_error_y,current_error_z,current_error_t=0.0f;
    double i_controller_x_tempData=0.0f;
    double i_controller_y_tempData=0.0f;
    double i_controller_z_tempData=0.0f;
    double i_controller_t_tempData=0.0f;
    tf2::Quaternion oldQuaternion(transformTFReturnOldTurtle().transform.rotation.x,transformTFReturnOldTurtle().transform.rotation.y,transformTFReturnOldTurtle().transform.rotation.z,transformTFReturnOldTurtle().transform.rotation.w);
    tf2::Matrix3x3 oldMatrix(oldQuaternion);
    tf2::Quaternion newQuaternion(transformTFReturnNewTurtle().transform.rotation.x,transformTFReturnNewTurtle().transform.rotation.y,transformTFReturnNewTurtle().transform.rotation.z,transformTFReturnNewTurtle().transform.rotation.w);
    tf2::Matrix3x3 newMatrix(newQuaternion);
    oldMatrix.getRPY(oldROLL,oldPITCH,oldYAW);
    newMatrix.getRPY(newROLL,newPITCH,newYAW);

    double pControllerX=kp*(transformTFReturnNewTurtle().transform.translation.x-transformTFReturnOldTurtle().transform.translation.x);
    double pControllerY=kp*(transformTFReturnNewTurtle().transform.translation.y-transformTFReturnOldTurtle().transform.translation.y);
    double pControllerZ=kp*(transformTFReturnNewTurtle().transform.translation.z-transformTFReturnOldTurtle().transform.translation.z);
    double pControllerT=kp*(newYAW-oldYAW);

    ros::Time last_time=ros::Time::now();
    double dti=(ros::Time::now()-last_time).toSec();

    i_controller_x_tempData+=ki*((transformTFReturnNewTurtle().transform.translation.x-transformTFReturnOldTurtle().transform.translation.x)*dti);
    i_controller_y_tempData+=ki*((transformTFReturnNewTurtle().transform.translation.y-transformTFReturnOldTurtle().transform.translation.y)*dti);
    i_controller_z_tempData+=ki*((transformTFReturnNewTurtle().transform.translation.z-transformTFReturnOldTurtle().transform.translation.z)*dti);
    i_controller_t_tempData+=ki*((newYAW-oldYAW)*dti);
    current_error_x=transformTFReturnNewTurtle().transform.translation.x-transformTFReturnOldTurtle().transform.translation.x;
    current_error_y=transformTFReturnNewTurtle().transform.translation.y-transformTFReturnOldTurtle().transform.translation.y;
    current_error_z=transformTFReturnNewTurtle().transform.translation.z-transformTFReturnOldTurtle().transform.translation.z;
    current_error_t=newYAW-oldYAW;
    double d_controller_x=((current_error_x-pre_error_x)/dti)*kd;
    double d_controller_y=((current_error_y-pre_error_y)/dti)*kd;
    double d_controller_z=((current_error_z-pre_error_z)/dti)*kd;
    double d_controller_t=((current_error_t-pre_error_t)/dti)*kd;
    pre_error_x=current_error_x;
    pre_error_y=current_error_y;
    pre_error_z=current_error_z;
    pre_error_t=current_error_t;
    double real_control_x=pControllerX + i_controller_x_tempData + d_controller_x;
    double real_control_y=pControllerY + i_controller_y_tempData + d_controller_y;
    double real_control_z=pControllerZ + i_controller_z_tempData + d_controller_z;
    double real_control_t=pControllerT + i_controller_t_tempData + d_controller_t;

    geometry_msgs::Twist twist;
    twist.linear.x=real_control_x;
    twist.linear.y=real_control_y;
    twist.linear.z=real_control_z;
    twist.angular.x=0.0;
    twist.angular.y=0.0;
    twist.angular.z=real_control_t;
    return twist;
}

int main(int argc, char *argv[]) {
    ros::init(argc,argv,"control_turtle_catch_up_node");
    ros::NodeHandle nh;
    ros::Rate rate(10);
    ros::Publisher publisher=nh.advertise<geometry_msgs::Twist>("/new/cmd_vel",10);
    publisher.publish(controller());
    while (ros::ok()) {
        ros::spinOnce();
        publisher.publish(controller());
        rate.sleep();
    }
}

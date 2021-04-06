#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h" 
#include <sstream>
#include <iostream>
#include "assignment1/Vel.h"
#include "my_srv2/Random.h"

double target_x = 0,target_y = 0;

/// declare the publisher as global///
ros::Publisher chatter_pub;
ros::ServiceClient client;
ros::Publisher pub2;

void subscriberCallback(const nav_msgs::Odometry::ConstPtr& pose_msg) //  the info of Odometry///
{
   ROS_INFO("Robot position: [%f, %f]", pose_msg->pose.pose.position.x, pose_msg->pose.pose.position.y);
   /// Use the pose_msg to get the current position of Odom ///
   geometry_msgs::Twist vel;
   /// create the instance to call service ///
   my_srv2::Random get_target;
   /// create the variables calculating the distance each of x and y///
   double dx = target_x - pose_msg->pose.pose.position.x;
   double dy = target_y - pose_msg->pose.pose.position.y;
   /// if the distance between target and current position is less than 0.1,change the target///
   if (pow(dx,2)+ pow(dy,2) <= pow(0.1,2)) {
     /// set the range of random value///
     get_target.request.min = -6;
     get_target.request.max = 6;
     /// call service to get the new random target///
     client.call(get_target);
     target_x = get_target.response.x;
     target_y = get_target.response.y;
     /// calculate again to update the distance each of x and y///
     dx = target_x - pose_msg->pose.pose.position.x;
     dy = target_y - pose_msg->pose.pose.position.y;
   }
    /// calculate velocity///
    double k = 1;
    vel.linear.x = k * dx; 
    vel.linear.y = k * dy; 
    /// publish the velocity info to stageros///
    chatter_pub.publish(vel);
    /// publishing the info of velocity as message///
    assignment1::Vel mymsg;
    mymsg.name = "linear"; 
    mymsg.vx = vel.linear.x;
    mymsg.vy = vel.linear.y;
    pub2.publish(mymsg);
}

int main(int argc, char **argv)
{
  ///initialization///
  ros::init(argc, argv, "assignment1");
  ros::NodeHandle n;
  /// set clients to connect service of random_target_creater ///
  client = n.serviceClient<my_srv2::Random>("/random_target");
  /// set publisher for sending info of velocity to /stageros///
  chatter_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  pub2 = n.advertise<assignment1::Vel>("linear", 1000);
  /// set subscriber for getting current position from /stageros///
  ros::Subscriber pose_sub = n.subscribe("odom", 1000, subscriberCallback);
  ros::spin();
    return 0;
}

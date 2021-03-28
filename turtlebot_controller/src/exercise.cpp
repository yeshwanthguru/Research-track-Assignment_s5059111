#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "turtlesim/Kill.h"
#include "turtlesim/Spawn.h"
#include <sstream>
#include <iostream>
#include "std_srvs/Empty.h"
#include "turtlesim/TeleportAbsolute.h"
#include "turtlebot_controller/Vel.h"
#include "my_srv/Velocity.h"


//TODO declare the publisher as global
ros::Publisher chatter_pub;
ros::Publisher pub2;
ros::ServiceClient client5;
int count = 10;
void subscriberCallback(const turtlesim::Pose::ConstPtr& pose_msg)
{
   ROS_INFO("Robot position: [%f, %f]", pose_msg->x, pose_msg->y);
   //TODO! Use the pose_msg to control the turtle (i.e., to publish the correct velocity command)
   geometry_msgs::Twist vel;
   my_srv::Velocity rec_vel;
    if (pose_msg->x > 9.0 ){
      vel.linear.x = 0.1;
      vel.angular.z = 0.1;     
    } else if (pose_msg->x < 1.5) {
      vel.linear.x = 0.1;
      vel.angular.z = -0.1;
    } else {
      rec_vel.request.x = pose_msg->x;
      client5.call(rec_vel); 
      vel.linear.x=rec_vel.response.x; 
    }
    chatter_pub.publish(vel);
    if ((pose_msg->y >8.9))
    {
	ros::shutdown();
    }
    turtlebot_controller::Vel mymsg;
    mymsg.name = "linear"; 
    mymsg.vel = vel.linear.x;
    pub2.publish(mymsg);
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "turtlebot_exercise");
  ros::NodeHandle n;

  ros::ServiceClient client1 = n.serviceClient<turtlesim::Kill>("/kill");
  ros::ServiceClient client2 = n.serviceClient<turtlesim::Spawn>("/spawn");
  ros::ServiceClient client3 = n.serviceClient<std_srvs::Empty>("/clear");
  ros::ServiceClient client4 = n.serviceClient<turtlesim::TeleportAbsolute>("/rt_turtle/teleport_absolute");
  
  turtlesim::Kill srv1;
  srv1.request.name = "turtle1";

  client1.call(srv1);

  turtlesim::Spawn srv2;

  srv2.request.x=5.0;
  srv2.request.y=5.0;
  srv2.request.theta=0.0;
  srv2.request.name="rt_turtle";

  client2.call(srv2);
  //TODO! call the service clear (optional) and rt_turtle/teleport_absolute
  std_srvs::Empty srv3;
  turtlesim::TeleportAbsolute srv4;

  srv4.request.x=2.0;
  srv4.request.y=1.0;
  srv4.request.theta=0.0;

  client4.call(srv4);
  sleep(1);
  client3.call(srv3);
  sleep(1);
  client5 = n.serviceClient<my_srv::Velocity>("/velocity");
  ros::Subscriber pose_sub = n.subscribe("/rt_turtle/pose", 1000, subscriberCallback);
  //TODO Initialize the publisher
  chatter_pub = n.advertise<geometry_msgs::Twist>("/rt_turtle/cmd_vel", 1000);
  pub2 = n.advertise<turtlebot_controller::Vel>("/rt_turtle/linear", 1000);
  ros::spin();

  return 0;
}



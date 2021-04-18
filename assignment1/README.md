                               # Research Track I - first assignment #
                                    Student ID:s5059111
                                      Name: Yeshwanth guru Krishnakumar

## Assignment 1-------------->structure description
The nodes are composed of `/assignment1`, `/random_target_server` and `/stageros`(which is already completed node and I don't make any change)
the system of connection is indicated like the computational graph of system (rqt_graph).
 The node `/assignment1` is subscribing the information of current position of robot as the topic `/odom` and publishing the information of calculated velocity to the node `/stageros` as the topic `/cmd_vel`. The node of `/assignment1` is keeping infomation of the position of target.
And regarding service nodes, the node `/assignmet1` requests generating new random targets from the service node `/random_target_server` when the distance between current position and target position is less than 0.1. the service node `random_target_server` is generating the new random target each for x and y when it's called from the client of the node `assignment1`.

## instructions about how to run the code




             $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
             $$$$$$$$$$$$$$$$$$$$$$$$$$$$roscore(master)$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
             $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
             $rosrun stage_ros stageros $(rospack find assignment1)/world/exercise.world$
             $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
             $$$$$$$$$$$$$$$$$$$$rosrun my_srv2 random_target$$$$$$$$$$$$$$$$$$$$$$$$$$$$
             $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
             $$$$$$$$$$$$$$$$$$$$$rosrun assignment1 assignment1$$$$$$$$$$$$$$$$$$$$$$$$$
             $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 



![rosgraph](https://user-images.githubusercontent.com/72270080/115137937-8969be80-a018-11eb-9177-011835c3f22a.png)

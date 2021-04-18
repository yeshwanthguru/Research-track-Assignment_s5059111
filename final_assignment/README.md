                                   Research Track I - final assignment
                                          Student ID:5059111
                                   Name: Yeshwanth guru krishnakumar

## the  Requirements to the structure
The non holonomic robot(gazebo) should be working as following below,
1.  move randomly in the environment , by choosing 1 out of 6 possible target positions:[(4, 3);(4,2);(4,7);(5, 7);(5, 3);(5,1)], implementing a random position service as in the assignment 1
2. directly ask the user for the next target position (checking that the position is one of the possible six ) and reach it
3. start following the external walls
4. stop in the last position
## Robot function option
#### state0 -  set random target#####
#### state1 -  ask user interface#####
#### state2 -  start following the external walls#####
#### state3 -  stop in the last positio#####

0. `/Controller` node calls for `/random_target` in order to get random target position among [(-4,-3),(-4,2),(-4,7),(5,-7),(5,-3),(5,1)], and publishes the target position for `/move_base`. After that, the robot starts to move for target.

1. When the robot arrives the target, node calls for `/human_machine_interface`. Next, `/human_machine _interface .( node asks the request on command line. and check if the request position is feasible(among [(-4,-3),(-4,2),(-4,7),(5,-7),(5,-3),(5,1)]) or not. And if it is ok, updates the target position and publishes the target position for `/move_base`. (If it's not feasible target, `/final_user_interface` asks again) After that, the robot starts to move for target same as state 0.

2. When the robot arrives the target,  node calls for `wall_follower`. and after the robot run around the map, it switches to state3.

3. When the robot arrives the target `/human_machine_interface` gave, the robot stops.

## Software architecture
The blue part is user interface. By using this module, I can interact with the robot controller by setting some parameters (in this caes, setting the target position).

The red parts are the ones which implements the actulal robot controller. it processes the inputs comming from gazebo(`/odom`,`/scan`)&user interface and it set a resulting linear and angular velocity for the robot(`/cmd_vel`). And  node is managing  current position and target position. In detail, the robot gets the map by using SLAM and plans the path from the current position to the target position by grobal Path planning(dijkstra) and the robot is moving while avoiding obstacles by using local path planning.

All the green components represent the section of the system which simulate the robot and its physical interaction with the environment.
The simulation is done in following steps:

1.For the first step, human_machine_interface.py node requests my_srv for a random target position between the range of 1 to 6.Then,the main node publishes the target positions to /move_base/goal and check thes the status of goal by subscribing to the topic /move_base/status.When the robot reaches the target and the status of robot is displayed, the main node requests the user to input again.

2.For the second step, the user chooses one out of six possible target positions and publishes it to /move_base/goal.

3.For the third step,the wall_follower service is generated through initialization of a service client to allow the robot to follow the external walls.

4.For the fourth step, the node stops all actions and stops the robot by publishing commands of zero velocity in topic /cmd_vel.

In steps 3 and 4,The interface also allows the user to enter the same or different request at any point in this state.

## System’s limitations and possible improvements

1. Possiblity of changing path on the way

In this system,the robot is moving for target while creating the map by SLAM algorithm, so the path created when the robot is in the initial position is not always optimal path because there is a possibility the robot doesn't notice obstacles. So the robot sometimes changes path, in some case it contributes to detour. And the point is that we already know how the map is. That's why I think I can improve creating optimal path by using amcl which estimate the current position by pattern matching with pre-existing maps and lasar data. 

2. Limited to static environment

In this system, the robot cannot avoid moving obstacles. But in real environments, we always need to consider moving obstacles. So I have to learn the algorithm and technique which enables robot to move safely even in dynamic environments.

## Instructions about how to run the code
                 ASSIGNMENT 2
These are all the codes flow chart to run the over all process:


             $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
             $$$$$roslaunch final_assignment simulation_gmapping.launch$$$$$
             $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
             $$$$$   roslaunch final_assignment move_base.launch       $$$$$
             $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
             $$$$$ rosrun final_assignment wall_follow_service_m.py    $$$$$
             $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
             $$$$$       rosrun my_srv finalassignment_server          $$$$$
             $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ 
             $$$$$ rosrun final_assignment human_machine_interface.py  $$$$$
             $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ 
       
 To get the computational graph of the process which takes place in the system and i have attached the screenshots of it for the reference.   
               
                $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ 
                $$$$$$$$ For computational graph of the system$$$$$$$$$$$$$$$$$
                $                                                             $
                $             rosrun rqt_graph rqt_graph                      $
                $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

And for the human_machine_interface.py example i have attached for the initial understanding purpose to knew the interface model for initial users.


Hi XXX the machine gonna start


  
                    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                    $$$$$$$Mobile robot controller interface options$$$$$$      
                    $$(1) Robot random movements among given coordinates$$
                    $$(2) user input to move along coordinates          $$
                    $$(3) Robot moves along the walls                   $$
                    $$(4) Robot stops in the last position              $$
                    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

click on the robot controller interface: 1

New Target: (5, -3)

Robot is on way to the target position.

Robot has reached the target position.

  
                    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                    $$$$$$$Mobile robot controller interface options$$$$$$      
                    $$(1) Robot random movements among given coordinates$$
                    $$(2) user input to move along coordinates          $$
                    $$(3) Robot moves along the walls                   $$
                    $$(4) Robot stops in the last position              $$
                    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

click on the robot controller interface: 2

  
                       $$$$$$$$$$$$$$$$$$$$
                       $$$$GIVEN TARGETS:$$
                       $$1$   (-4,-3)    $$
                       $$2$   (-4,2)     $$
                       $$3$   (-4,7)     $$
                       $$4$   (5,-7)     $$
                       $$5$   (5,-3)     $$
                       $$6$   (5,1)      $$
                       $$$$$$$$$$$$$$$$$$$$

user input selection in given coordinates: 5

 new target position is (5, -3)

Robot is on the way to target position.

Robot has reached the target position.

  
                    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                    $$$$$$$Mobile robot controller interface options$$$$$$      
                    $$(1) Robot random movements among given coordinates$$
                    $$(2) user input to move along coordinates          $$
                    $$(3) Robot moves along the walls                   $$
                    $$(4) Robot stops in the last position              $$
                    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

click on the robot controller interface: 3

Robot is following the wall.

  
                    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
                    $$$$$$$Mobile robot controller interface options$$$$$$      
                    $$(1) Robot random movements among given coordinates$$
                    $$(2) user input to move along coordinates          $$
                    $$(3) Robot moves along the walls                   $$
                    $$(4) Robot stops in the last position              $$
                    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

click on the robot controller interface: 4

Robot  finished.




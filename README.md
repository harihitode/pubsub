# ROS2 Pub/Sub Essentials

This is a sample code for ROS2 pub/sub.
This program includes latency check.

## build & setup

``
source /opt/ros/eloquent/setup.bash
cd pubsub/
colcon build
source install/setup.bash
``

## execution

1. normal pub/sub (using default rmw)

``
ros2 run comm publisher
``

on other terminal
``
ros2 run comm subscriber
``

2. intra-process pointer passing pub/sub 

``
ros2 run comm pubsub
``

That is all ;)


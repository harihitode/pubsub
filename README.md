# ROS2 Pub/Sub Essentials

This is a sample code for ROS2 pub/sub.
This program includes latency check.

## build & setup

```
source /opt/ros/${ROS_DISTRO}/setup.bash
cd pubsub/
colcon build
source install/setup.bash
```

## execution

1. normal pub/sub (using default rmw)

``
ros2 run comm publisher
``

on other terminal

``
ros2 run comm subscriber
``

or kicking launch file

```
ros2 launch launch/inter_process_pubsub.launch.py
```

2. intra-process pointer passing pub/sub 

``
ros2 launch launch/intra_process_pubsub.launch.py
``

That is all, thank you ;)


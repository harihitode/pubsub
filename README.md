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

1. launch

  * inter-process (using default rmw)
  
``
ros2 launch comm inter_process_pubsub.launch.py blob_size:=1000
``

  * intra-process (pointer passing)

``
ros2 launch comm intra_process_pubsub.launch.py blob_size:=1000
``

2. start the publish routine

``
ros2 service call /publish_loop comm/srv/PublishLoop '{count: 100}'
``

for publish 100 times


That is all, thank you ;)

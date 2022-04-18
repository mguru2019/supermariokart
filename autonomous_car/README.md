## 1. Read LiDAR Scans 
The following instructions are for Hokuyo UTM-30LX. Ensure ROS is installed on Ubuntu with the urg_node package.
+ Ensure rw permissions are enabled for your device by running ```ls -l /dev/ttyACMx``` where x is the device number (default is 0). If not, run ```sudo chmod a+rw \dev\ttyACMx```
+ cd to your catkin workspace and connect to source
+ Ensure that ROS can detect the device by running ```rosrun urg_node getID /dev/ttyACMx```. If not, make sure the laser is detected in the USB port by running ```lsusb```
+ Start ROS by running ```roscore```
+ In a new tab, run ```rosrun urg_node urg_node```
+ Finally, in another tab, run ```rostopic echo /scan```. You should be able to see LiDAR data being sent to the scan topic.

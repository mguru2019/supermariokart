This repository contains main execution files for each of the ROS nodes in the autonomous car setup. All include files for the car are within the RC car directory, since the only file that differs is main.c

This project was done entirely in Ubuntu OS 20.04 with ROS Noetic, however any distribution will work as long as the urg_node and rosserial_arduino packages can be installed.

## 1. Read LiDAR Scans 
The following instructions are for Hokuyo UTM-30LX. Ensure ROS is installed on Ubuntu with the urg_node package.
+ Ensure rw permissions are enabled for your device by running ```ls -l /dev/ttyACMx``` where x is the device number (default is 0). If not, run ```sudo chmod a+rw /dev/ttyACMx```
+ cd to your catkin workspace and connect to source
+ Ensure that ROS can detect the device by running ```rosrun urg_node getID /dev/ttyACMx```. If not, make sure the laser is detected in the USB port by running ```lsusb```
+ Start ROS master node by running ```roscore```
+ In a new tab, run ```rosrun urg_node urg_node _serial_port:=/dev/ttyACMx```
+ Finally, in another tab, run ```rostopic echo /scan```. You should be able to see LiDAR data being sent to the scan topic.
## 2. Ensure Ubuntu can locate Arduino
+ Run ```lsusb```. If you can see the Arduino listed, you're all set! If not, run the following: 
+ ```sudo groupadd vboxusers```
+ ```sudo usermod -a -G vboxusers $USER```
+ ```sudo reboot```
## 3. Run follow_the_gap node
+ Clone the autonomous_car directory into your catkin_ws and remove the atmega2560 and atmega328p folders
+ Compile your catkin_ws in its root directory by running catkin_make. Makefile is provided in this repository
+ Then, connect to source and run ```rosrun follow_the_gap reactive_gap_follow```
+ In a new terminal, if you connect to source again and run ```rostopic echo nav``` you should see the stream printing steering angle data.
## 4. Run Arduino sketch to read from rostopic
+ Compile and upload the Arduino sketch with the subscriber node
+ In terminal, run ```roscore```
+ In a new tab, connect to source and run ```rosrun rosserial_python serial_node.py /dev/ttyACMx```
+ If data is being sent to the channel the Arduino is subscribed to, it should be able to detect it now

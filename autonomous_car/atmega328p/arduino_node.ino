#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandel nh;

void callback(const std_msgs::Float32& angle) {
  int degree = (angle.data * 180)/PI;
  if (degree <= 15 && degree >= -15) {
    //tested what was a small enough angle to ignore and just go straight
    digitalWrite(14, LOW);
    digitalWrite(15, LOW);
    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
  }
  if (degree > 0) {
    //degree greater than 0, we are moving to the right
    digitalWrite(14, LOW);
  }
  if (degree < 0) {
    //degree less than 0, we are moving to the left
    digitalWrite(14, HIGH);
    //multiply by -1 if negative so we can case on absolute value
    degree = degree * -1;
    
  }
  // angle of orientation
  if (degree >= 15 && degree < 30) {
    digitalWrite(15, HIGH);
    digitalWrite(16, LOW);
    digitalWrite(17, LOW);
  }
  if (degree >= 30 && degree < 50) {
    digitalWrite(15, LOW);
    digitalWrite(16, HIGH);
    digitalWrite(17, LOW);
  }
  if (degree >= 50) {
    digitalWrite(15, LOW);
    digitalWrite(16, LOW);
    digitalWrite(17, HIGH);
  }
}

ros::Subscriber<std_msgs::Float32> sub("\nav", &callback);


void setup() {
  //direction pin, tells us right or left
  pinMode(14, OUTPUT);
  // 15 to 30 degree turn
  pinMode(15, OUTPUT);
  // 30 to 50 degree turn
  pinMode(16, OUTPUT);
  // 50+ degree turn (capped at 70 in follow the gap node)
  pinMode(17, OUTPUT);
  
  //create node handler object
  nh.init_node();
  //create subscription in node handler
  nh.subscribe(sub);
  
}

void loop() {
  nh.spinOnce();
  delay(1);
}

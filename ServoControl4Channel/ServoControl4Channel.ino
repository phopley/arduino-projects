/*
 * Based on the rosserial Servo Control Example
 * This version controls upto four RC Servos
 * The node subscribes to the servo topic and acts on a rodney_msgs::servo_array message.
 * This message contains two elements, index and angle. Index references the servos 0-3 and 
 * angle is the angle to set the servo to 0-180.
 *
 */

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <servo_msgs/servo_array.h>

/* Define the PWM pins that the servos are connected to */
#define SERVO_0 9
#define SERVO_1 6
#define SERVO_2 5
#define SERVO_3 3

ros::NodeHandle  nh;

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;

void servo_cb( const servo_msgs::servo_array& cmd_msg){
  
  /* Which servo to drive */
  switch(cmd_msg.index)
  {
    case 0:
      nh.logdebug("Servo 0 ");
      servo0.write(cmd_msg.angle); //set servo 0 angle, should be from 0-180
      break;

    case 1:
      nh.logdebug("Servo 1 ");
      servo1.write(cmd_msg.angle); //set servo 1 angle, should be from 0-180
      break;

    case 2:
      nh.logdebug("Servo 2 ");
      servo2.write(cmd_msg.angle); //set servo 2 angle, should be from 0-180
      break;

    case 3:
      nh.logdebug("Servo 3 ");
      servo3.write(cmd_msg.angle); //set servo 3 angle, should be from 0-180
      break;
      
    default:
      nh.logdebug("No Servo");
      break;
  }
    
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}

ros::Subscriber<servo_msgs::servo_array> sub("servo", servo_cb);

void setup(){
  pinMode(13, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
  
  
  servo0.attach(SERVO_0); //attach it to the pin
  servo1.attach(SERVO_1);
  servo2.attach(SERVO_2);
  servo3.attach(SERVO_3);
}

void loop(){
  nh.spinOnce();
  delay(1);
}

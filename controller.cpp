#include "Arduino.h"
//#include <math.h>
#include "controller.h"

namespace koyo {
namespace controller {
controller::controller()
  : dt_L_(0),
    dt_R_(0),
    dt_kick_(0),
    dt_max_(1),
    pwm_max_((0xFF)),
    pwm_pin_L_(3),
      pwm_pin_R_(9),
      pwm_pin_kick_(11),
      motor_pin_L1_(2),
      motor_pin_L2_(4),
      motor_pin_R1_(8),
      motor_pin_R2_(10),
      motor_pin_kick1_(13),
      motor_pin_kick2_(5)
    /*
      //for A's driver
      pwm_pin_L_(0),
      pwm_pin_R_(1),
      pwm_pin_kick_(2)
    */
    /*
      //for B's hyper
      pwm_pin_L_(3),
      pwm_pin_R_(9),
      pwm_pin_kick_(10),
      motor_pin_L1_(2),
      motor_pin_L2_(4),
      motor_pin_R1_(8),
      motor_pin_R2_(7),
      motor_pin_kick1_(6),
      motor_pin_kick2_(5)
    */
{

  pinMode(pwm_pin_L_, OUTPUT);
  pinMode(pwm_pin_R_, OUTPUT);
  pinMode(pwm_pin_kick_, OUTPUT);
  pinMode(motor_pin_L1_, OUTPUT);
  pinMode(motor_pin_L2_, OUTPUT);
  pinMode(motor_pin_R1_, OUTPUT);
  pinMode(motor_pin_R2_, OUTPUT);
  pinMode(motor_pin_kick1_, OUTPUT);
  pinMode(motor_pin_kick2_, OUTPUT);
  before_.vel = 0.0;
  before_.omega = 0.0;
  before_.weapon = 0.0;
  bias_.vel = 0.05;
  bias_.omega = 0.05;
  bias_.weapon = 0.05;
  /*//for B's hyper
    digitalWrite(motor_pin_L2_, HIGH);
    digitalWrite(motor_pin_R2_, HIGH);
    digitalWrite(motor_pin_kick2_, HIGH);
  */
}

data_list::command controller::execute() {

  before_.vel += bias_.vel * (command_.vel - before_.vel);
  before_.omega += bias_.omega * (command_.omega - before_.omega);
  before_.weapon += bias_.weapon * (command_.weapon - before_.weapon);

  if (command_.vel == 0.0 && fabs(before_.vel) < (data_list::vel_max * 0.1) )before_.vel = 0.0; //10%以下カット
  if (command_.omega == 0.0 && fabs(before_.omega) < (data_list::omega_max * 0.1) )before_.omega = 0.0; //10%以下カット
  if (command_.weapon == 0.0 && fabs(before_.weapon) < (data_list::weapon_max * 0.1) )before_.weapon = 0.0; //10%以下カット

  dt_R_ = (before_.omega > 0) ? dt_max_ * before_.vel / data_list::vel_max
          : dt_max_ * before_.vel / data_list::vel_max *
          (1 + before_.omega / data_list::omega_max);//test
  dt_L_ = (before_.omega < 0) ? dt_max_ * before_.vel / data_list::vel_max
          : dt_max_ * before_.vel / data_list::vel_max *
          (1 - before_.omega / data_list::omega_max);//test
  dt_kick_ = before_.weapon / data_list::weapon_max;


  // motor_left
  if (dt_L_ > 0) {
    digitalWrite(motor_pin_L1_, HIGH);
    //delay?
    digitalWrite(motor_pin_L2_, LOW);

    analogWrite(pwm_pin_L_, (int)(pwm_max_ * dt_L_));
  } else if (dt_L_ < 0) {
    digitalWrite(motor_pin_L1_, LOW);
    //delay?
    digitalWrite(motor_pin_L2_, HIGH);

    analogWrite(pwm_pin_L_, (int)(pwm_max_ * (-dt_L_)));
  } else {
    digitalWrite(motor_pin_L1_, LOW);
    //delay?
    digitalWrite(motor_pin_L2_, LOW);

    digitalWrite(pwm_pin_L_, LOW);
  }

  // motor_right
  if (dt_R_ > 0) {
    digitalWrite(motor_pin_R1_, LOW);
    //delay?
    digitalWrite(motor_pin_R2_, HIGH);

    analogWrite(pwm_pin_R_, (int)(pwm_max_ * dt_R_));
  } else if (dt_R_ < 0) {
    digitalWrite(motor_pin_R1_, HIGH);
    //delay?
    digitalWrite(motor_pin_R2_, LOW);

    analogWrite(pwm_pin_R_, (int)(pwm_max_ * (-dt_R_)));
  } else {
    digitalWrite(motor_pin_R1_, LOW);
    //delay?
    digitalWrite(motor_pin_R2_, LOW);

    digitalWrite(pwm_pin_R_, LOW);
  }

  // motor_kick
  if (dt_kick_ > 0) {
    digitalWrite(motor_pin_kick1_, HIGH);
    //delay?
    digitalWrite(motor_pin_kick2_, LOW);

    analogWrite(pwm_pin_kick_, (int)(pwm_max_ * dt_kick_));
  } else {
    digitalWrite(motor_pin_kick1_, LOW);
    //delay?
    digitalWrite(motor_pin_kick2_, LOW);

    digitalWrite(pwm_pin_kick_, LOW);
  }
  /*
    //for A's driver
    char buf[20]={"\0"};
    sprintf(buf, "sel %d", pwm_pin_L_ + 16);
    Serial.println(buf);
    Serial.flush();
    sprintf(buf, "dt %d", (int)(100 * dt_L_));
    Serial.println(buf);
    Serial.flush();

    sprintf(buf, "sel %d", pwm_pin_R_ + 16);
    Serial.println(buf);
    Serial.flush();
    sprintf(buf, "dt %d", (int)(100 * dt_R_));
    Serial.println(buf);
    Serial.flush();


    sprintf(buf, "sel %d", pwm_pin_kick_ + 16);
    Serial.println(buf);
    Serial.flush();
    sprintf(buf, "dt %d", (int)(100 * dt_kick_));
    Serial.println(buf);
    Serial.flush();
  */


  /* //for B's hyper
    // motor_left
    if (dt_L_ > 0) {
      digitalWrite(motor_pin_L1_, LOW);
      analogWrite(pwm_pin_L_, (int)(pwm_max_ * dt_L_));
    } else if (dt_L_ < 0) {
      digitalWrite(motor_pin_L1_, HIGH);
      analogWrite(pwm_pin_L_, (int)(pwm_max_ * (-dt_L_)));
    } else {
      digitalWrite(motor_pin_L1_, LOW);
      digitalWrite(pwm_pin_L_, LOW);
    }

    // motor_right
    if (dt_R_ > 0) {
      digitalWrite(motor_pin_R1_, HIGH);
      analogWrite(pwm_pin_R_, (int)(pwm_max_ * dt_R_));
    } else if (dt_R_ < 0) {
      digitalWrite(motor_pin_R1_, LOW);
      analogWrite(pwm_pin_R_, (int)(pwm_max_ * (-dt_R_)));
    } else {
      digitalWrite(motor_pin_R1_, LOW);
      digitalWrite(pwm_pin_R_, LOW);
    }

    // motor_kick
    if (dt_kick_ > 0) {
      digitalWrite(motor_pin_kick1_, LOW);
      analogWrite(pwm_pin_kick_, (int)(pwm_max_ * dt_kick_));
    } else {
      digitalWrite(motor_pin_kick1_, LOW);
      digitalWrite(pwm_pin_kick_, LOW);
    }
  */
  return command_;
}

void controller::set_command(const data_list::command command) {
  command_ = command;
}
}  // namespace controller
}  // namespace koyo

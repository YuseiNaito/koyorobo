#include "Arduino.h"

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
      pwm_pin_R_(10),
      pwm_pin_kick_(5),
      motor_pin_L1_(2),
      motor_pin_L2_(4),
      motor_pin_R1_(7),
      motor_pin_R2_(8),
      motor_pin_kick1_(12),
      motor_pin_kick2_(13) 
      {
      pinMode(motor_pin_L1_, OUTPUT);
      pinMode(motor_pin_L2_, OUTPUT);
      pinMode(motor_pin_R1_, OUTPUT);
      pinMode(motor_pin_R2_, OUTPUT);  
      pinMode(motor_pin_kick1_, OUTPUT);  
      pinMode(motor_pin_kick2_, OUTPUT);  
      }

data_list::command controller::execute() {
  dt_L_ = (command_.omega > 0) ? dt_max_ * command_.vel / data_list::vel_max
                             : dt_max_ * command_.vel / data_list::vel_max *
                                   (1 + command_.omega / data_list::omega_max);
  dt_R_ = (command_.omega < 0) ? dt_max_ * command_.vel / data_list::vel_max
                             : dt_max_ * command_.vel / data_list::vel_max *
                                   (1 - command_.omega / data_list::omega_max);
  dt_kick_ = (int)(pwm_max_ * command_.weapon / data_list::weapon_max);

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
    digitalWrite(motor_pin_L1_, HIGH);
    //delay?
    digitalWrite(motor_pin_L2_, HIGH);
    
    analogWrite(pwm_pin_L_, 0);
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
    digitalWrite(motor_pin_R1_, HIGH);
    //delay?
    digitalWrite(motor_pin_R2_, HIGH);
    
    analogWrite(pwm_pin_R_, 0);
  }

  // motor_kick
  if (dt_kick_ > 0) {
    digitalWrite(motor_pin_kick1_, HIGH);
    //delay?
    digitalWrite(motor_pin_kick2_, LOW);
    
    analogWrite(pwm_pin_kick_, dt_kick_);
  } else {
    digitalWrite(motor_pin_kick1_, HIGH);
    //delay?
    digitalWrite(motor_pin_kick2_, HIGH);
    
    analogWrite(pwm_pin_kick_, 0);
  }

  return command_;
}

void controller::set_command(const data_list::command command) {
  command_ = command;
}
}  // namespace controller
}  // namespace koyo

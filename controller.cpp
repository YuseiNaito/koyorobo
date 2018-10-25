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
    pwm_pin_R_(11),//before 10
    pwm_pin_kick_(10),//before 5
    motor_pin_L1_(2),
    motor_pin_L2_(4),
    motor_pin_R1_(7),
    motor_pin_R2_(8),
    motor_pin_kick1_(12),
    motor_pin_kick2_(13),
    bias_vel(0.05),
    bias_omega(0.05),
    bias_weapon(0.05)
{
  
    // fast PWM mode:pwm_pin_L_&pwm_pin_R_
    /*
    TCCR0A = _BV(COM0A1)|_BV(WGM01)|_BV(WGM00); // TCCR0A = B10000011;
    TCCR0B = _BV(CS00); // TCCR0B = B00000001;
    */
    TCCR2A = _BV(COM0A1)|_BV(WGM01)|_BV(WGM00); // TCCR0A = B10000011;
    TCCR2B = _BV(CS00); // TCCR0B = B00000001;
    
    // 動作クロックは分周なしの8MHz
    // PWMキャリア波の周波数は8MHz/256=31.25kHz
    TCCR1A = _BV(COM0A1)|_BV(WGM01)|_BV(WGM00); // TCCR0A = B10000011;
    TCCR1B = _BV(CS00); // TCCR0B = B00000001;
    // fast PWM mode:pwm_pin_kick_
    // 動作クロックは分周なしの16MHz
    // PWMキャリア波の周波数は16MHz/256=62.5kHz
  
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
}

data_list::command controller::execute() {

  before_.vel += bias_vel * (command_.vel - before_.vel);
  before_.omega += bias_omega * (command_.omega - before_.omega);
  before_.weapon += bias_weapon * (command_.weapon - before_.weapon);

  if (command_.vel == 0.0 && before_.vel < (data_list::vel_max * 0.03) )before_.vel = 0.0; //3%以下カット
  if (command_.omega == 0.0 && before_.omega < (data_list::omega_max * 0.03) )before_.omega = 0.0; //3%以下カット
  if (command_.weapon == 0.0 && before_.weapon < (data_list::weapon_max * 0.03) )before_.weapon = 0.0; //3%以下カット

  dt_L_ = (command_.omega > 0) ? dt_max_ * before_.vel / data_list::vel_max
          : dt_max_ * before_.vel / data_list::vel_max *
          (1 + before_.omega / data_list::omega_max);//test
  dt_R_ = (command_.omega < 0) ? dt_max_ * before_.vel / data_list::vel_max
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
    digitalWrite(motor_pin_L1_, HIGH);
    //delay?
    digitalWrite(motor_pin_L2_, HIGH);

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
    digitalWrite(motor_pin_R1_, HIGH);
    //delay?
    digitalWrite(motor_pin_R2_, HIGH);

    digitalWrite(pwm_pin_R_, LOW);
  }

  // motor_kick
  if (dt_kick_ > 0) {
    digitalWrite(motor_pin_kick1_, HIGH);
    //delay?
    digitalWrite(motor_pin_kick2_, LOW);

    analogWrite(pwm_pin_kick_, (int)(pwm_max_ * dt_kick_));
  } else {
    digitalWrite(motor_pin_kick1_, HIGH);
    //delay?
    digitalWrite(motor_pin_kick2_, HIGH);

    digitalWrite(pwm_pin_kick_, LOW);
  }

  return command_;
}

void controller::set_command(const data_list::command command) {
  command_ = command;
}
}  // namespace controller
}  // namespace koyo

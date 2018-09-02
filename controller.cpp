#include "Arduino.h"

#include "controller.h"

namespace koyo {
namespace controller {
controller::controller()
    : dt1_(0),
      dt2_(0),
      dt_max_(1),
      pwm_max_((0xFF)),
      pwmpin_L1_(5),
      pwmpin_L2_(6),
      pwmpin_R1_(9),
      pwmpin_R2_(10),
      pwmpin_kick_(11) {}

data_list::command controller::execute() {
  // PWM出力が可能なポートにつながっている場合
  dt1_ = (command_.omega > 0) ? dt_max_ * command_.vel / data_list::vel_max
                             : dt_max_ * command_.vel / data_list::vel_max *
                                   (1 + command_.omega / data_list::omega_max);
  dt2_ = (command_.omega < 0) ? dt_max_ * command_.vel / data_list::vel_max
                             : dt_max_ * command_.vel / data_list::vel_max *
                                   (1 - command_.omega / data_list::omega_max);
  // motor_left
  if (dt1_ > 0) {
    analogWrite(pwmpin_L1_, 0);
    // delay(50); // デッドタイムがいるならディレイ
    analogWrite(pwmpin_L2_, (int)(pwm_max_ * dt1_));
  } else if (dt1_ < 0) {
    analogWrite(pwmpin_L2_, 0);
    // delay(50);
    analogWrite(pwmpin_L1_, (int)(pwm_max_ * (-dt1_)));
  } else {
    analogWrite(pwmpin_L1_, 0);
    analogWrite(pwmpin_L2_, 0);
  }

  // motor_right
  if (dt2_ > 0) {
    analogWrite(pwmpin_R1_, 0);
    // delay(50);
    analogWrite(pwmpin_R2_, (int)(pwm_max_ * dt2_));
  } else if (dt2_ < 0) {
    analogWrite(pwmpin_R2_, 0);
    // delay(50);
    analogWrite(pwmpin_R1_, (int)(pwm_max_ * (-dt2_)));
  } else {
    analogWrite(pwmpin_R1_, 0);
    analogWrite(pwmpin_R2_, 0);
  }

  // motor_kick
  if (command_.weapon > 0) {
    analogWrite(pwmpin_kick_,
                (int)(pwm_max_ * command_.weapon / data_list::weapon_max));
  } else {
    analogWrite(pwmpin_kick_, 0);
  }

  return command_;
}

void controller::set_command(const data_list::command command) {
  command_ = command;
}
}  // namespace controller
}  // namespace koyo

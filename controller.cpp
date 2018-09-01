#include "Arduino.h"

#include "controller.h"

namespace koyo {
namespace controller {
controller::controller() {}

data_list::command controller::execute() {
  // PWM出力が可能なポートにつながっている場合
  dt1 = (command_.omega > 0) ? dt_max * command_.vel / vel_max
                             : dt_max * command_.vel / vel_max *
                                   (1 + command_.omega / omega_max);
  dt2 = (command_.omega < 0) ? dt_max * command_.vel / vel_max
                             : dt_max * command_.vel / vel_max *
                                   (1 - command_.omega / omega_max);
  // motor_left
  if (dt1 > 0) {
    analogWrite(pwmpin_L1, 0);
    // delay(50); // デッドタイムがいるならディレイ
    analogWrite(pwmpin_L2, (int)(pwm_max * dt1));
  } else if (dt1 < 0) {
    analogWrite(pwmpin_L2, 0);
    // delay(50);
    analogWrite(pwmpin_L1, (int)(pwm_max * (-dt1)));
  } else if (dt1 == 0) {
    analogWrite(pwmpin_L1, 0);
    analogWrite(pwmpin_L2, 0);
  }

  // motor_right
  if (dt2 > 0) {
    analogWrite(pwmpin_R1, 0);
    // delay(50);
    analogWrite(pwmpin_R2, (int)(pwm_max * dt2));
  } else if (dt2 < 0) {
    analogWrite(pwmpin_R2, 0);
    // delay(50);
    analogWrite(pwmpin_R1, (int)(pwm_max * (-dt2)));
  } else if (dt2 == 0) {
    analogWrite(pwmpin_R1, 0);
    analogWrite(pwmpin_R2, 0);
  }

  // motor_kick
  if (command_.weapon > 0) {
    analogWrite(pwmpin_kick, (int)(pwm_max * command_.weapon / weapon_max));
  } else {
    analogWrite(pwmpin_kick, 0);
  }

  return command_;
}

void controller::set_command(const data_list::command command) {
  command_ = command;
}
}  // namespace controller
}  // namespace koyo

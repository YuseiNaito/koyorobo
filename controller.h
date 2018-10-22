#ifndef KOYO_CONTROLLER_H
#define KOYO_CONTROLLER_H
#include "arduino.h"
#include "data_list.h"

namespace koyo {
namespace controller {
class controller {
 public:
  controller();
  data_list::command execute();
  void set_command(const data_list::command command);

 private:
  data_list::command command_;
  // test
  double dt_L_;
  double dt_R_;
  double dt_kick_;

  const double dt_max_;
  const int pwm_max_;
  
  const int pwm_pin_L_;
  const int pwm_pin_R_;
  const int pwm_pin_kick_;

  const int motor_pin_L1_;
  const int motor_pin_L2_;
  const int motor_pin_R1_;
  const int motor_pin_R2_;
  const int motor_pin_kick1_;
  const int motor_pin_kick2_;

  struct before {
  double vel;
  double omega;
  double weapon;
} before_;
  double bias_vel;
  double bias_omega;
  double bias_weapon;
};
}  // namespace controller
}  // namespace koyo

#endif

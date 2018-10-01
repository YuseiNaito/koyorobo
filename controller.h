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

  bool motor_pin_L1_;
  bool motor_pin_L2_;
  bool motor_pin_R1_;
  bool motor_pin_R2_;
  bool motor_pin_kick1_;
  bool motor_pin_kick2_;
  
};
}  // namespace controller
}  // namespace koyo

#endif

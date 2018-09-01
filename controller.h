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
  double dt1 = 0;
  double dt2 = 0;

  const double dt_max = 1;
  const double vel_max = (0xFF) * 100;
  const double omega_max = (0xFF) * 3.14;
  const double weapon_max = 120 * 2;

  const int pwm_max = (0xFF);
  const int pwmpin_L1 = 5;
  const int pwmpin_L2 = 6;
  const int pwmpin_R1 = 9;
  const int pwmpin_R2 = 10;
  const int pwmpin_kick = 11;
};
}  // namespace controller
}  // namespace koyo

#endif

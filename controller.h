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
  double dt1_;
  double dt2_;

  const double dt_max_;

  const int pwm_max_;
  const int pwmpin_L1_;
  const int pwmpin_L2_;
  const int pwmpin_R1_;
  const int pwmpin_R2_;
  const int pwmpin_kick_;
};
}  // namespace controller
}  // namespace koyo

#endif

#include "action_normal.h"

namespace koyo {
namespace action {
data_list::command normal::execute() {
  // �ő呬�x��70%
  constexpr double vel_coef =
    0.7 * data_list::vel_max / data_list::stick_res_max;
  constexpr double omega_coef = data_list::omega_max / data_list::stick_res_max;

  command_.vel = signal_.vartical * vel_coef;
  command_.omega = signal_.horizontal * omega_coef;
  command_.weapon = 0.6 * signal_.button0 * data_list::weapon_max;
  return command_;
}
}  // namespace action
}  // namespace koyo

#include "action_normal.h"

namespace koyo {
namespace action {
data_list::command normal::execute() {
  command_.vel = signal_.vartical * 100;
  command_.omega = signal_.horizontal * 3.14;
  command_.weapon = 120 * signal_.button0;
  return command_;
}
}  // namespace action
}  // namespace koyo
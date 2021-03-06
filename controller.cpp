#include "Arduino.h"

#include "controller.h"

namespace koyo {
namespace controller {
controller::controller() {}

data_list::command controller::execute() {
  // sample
  command_.test_data *= 2;

  // sample
  Serial.println(command_.test_data);

  return command_;
}

void controller::set_command(const data_list::command command) {
  command_ = command;
}
}  // namespace controller
}  // namespace koyo

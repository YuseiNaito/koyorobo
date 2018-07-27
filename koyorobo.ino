#include "controller.h"
#include "data_list.h"
#include "receiver.h"
#include "state_switcher.h"

bool run_flag;

koyo::controller::controller controller;
koyo::receiver::receiver receiver;
koyo::state_switcher::state_switcher switcher;

void setup() {
  run_flag = true;
}

void loop() {
  if (run_flag) {
	switcher.set_signal(receiver.execute());
    auto sw_ptr = switcher.execute();
    controller.set_command(sw_ptr->execute());
    controller.execute();
    delete sw_ptr;
  }
}

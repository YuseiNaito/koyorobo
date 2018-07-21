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

  // sample
  Serial.begin(9600);
}

void loop() {
  if (run_flag) {
    auto sw_ptr = switcher.execute(receiver.execute());
    controller.set_command(sw_ptr->execute());
    auto returned_command = controller.execute();

    // sample
    Serial.println(returned_command.test_data);

    delete sw_ptr;
  }
}

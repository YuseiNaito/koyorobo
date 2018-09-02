#include "action_base.h"
#include "action_normal.h"
#include "controller.h"
#include "data_list.h"
#include "receiver.h"
#include "state_switcher.h"

#include <new.h>

bool run_flag;

unsigned long now{0};
unsigned long before{0};

koyo::controller::controller controller;
koyo::receiver::receiver receiver;
koyo::state_switcher::state_switcher switcher;

void setup() {
  Serial.begin(9600);
}

void loop() {
  switcher.set_signal(receiver.execute());
  controller.set_command(switcher.execute()->execute());
  controller.execute();

  // output fps
  now = millis();
  auto fps{1000.0 / (now - before)};
  before = now;
  Serial.println(fps);
}

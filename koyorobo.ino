#include "action_base.h"
#include "action_normal.h"
#include "controller.h"
#include "data_list.h"
#include "receiver.h"
#include "state_switcher.h"

bool run_flag;

koyo::controller::controller controller;
koyo::receiver::receiver receiver;
koyo::data_list::signal signal = receiver.execute();
koyo::state_switcher::state_switcher switcher(signal);

void setup() {
  Serial.begin(9600);
}

void loop() {
  signal = receiver.execute();

  /*
  Serial.print(" vartical=");
  Serial.print(signal.vartical);
  Serial.print(" horizontal=");
  Serial.print(signal.horizontal);
  Serial.print(" button0=");
  Serial.println(signal.button0);*/

  controller.set_command(switcher.execute()->execute());
  controller.execute();
  delay(50); // 遅延時間は実機で調整
}

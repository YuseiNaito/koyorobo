#include "controller.h"
#include "data_list.h"
#include "receiver.h"
#include "state_switcher.h"

int max_time;//連続動作時間
int m;//回復
int n;//遅延
int time;//持ち時間

koyo::controller::controller controller;
koyo::receiver::receiver receiver;
koyo::data_list::signal signal = receiver.execute();
koyo::state_switcher::state_switcher switcher(signal);

void setup() {
	Serial.begin(9600);
	max_time = 3000;
	time = max_time;
	n = 50;
	m = 25;
}

void loop() {
	signal = receiver.execute();

	if (signal.button0 > 0) {
		if (time > 0) time -= n;
		else time = 0;
	}
	else {
		if (time > max_time) time = max_time;
		else time += m;
	}
	//if (time<=0) button_0 =0;
	controller.set_command(switcher.execute()->execute());
	controller.execute();
	delay(n);//遅延時間は実機で調整

}

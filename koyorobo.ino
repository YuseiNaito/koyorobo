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
  
    /*
     * 
    TCCR0A = _BV(COM0A1)|_BV(WGM01)|_BV(WGM00); // TCCR0A = B10000011;
    TCCR0B = _BV(CS00); // TCCR0B = B00000001;
    
    TCCR2A = _BV(COM0A1)|_BV(WGM01)|_BV(WGM00); // TCCR0A = B10000011;
    TCCR2B = _BV(CS00); // TCCR0B = B00000001;
    
    // 動作クロックは分周なしの8MHz
    // PWMキャリア波の周波数は8MHz/256=31.25kHz
    TCCR1A = _BV(COM0A1)|_BV(WGM01)|_BV(WGM00); // TCCR0A = B10000011;
    TCCR1B = _BV(CS00); // TCCR0B = B00000001;
    // fast PWM mode:pwm_pin_kick_
    // 動作クロックは分周なしの16MHz
    // PWMキャリア波の周波数は16MHz/256=62.5kHz
    */
    // fast PWM mode:pwm_pin_L_&pwm_pin_R_
    //TCCR2A = _BV(COM0A1)|_BV(WGM01)|_BV(WGM00); // TCCR0A = B10000011;
    TCCR2B = _BV(CS00); // TCCR0B = B00000001;
    
    // 動作クロックは分周なしの8MHz
    // PWMキャリア波の周波数は8MHz/256=31.25kHz
    //TCCR1A = _BV(COM0A1)|_BV(WGM01)|_BV(WGM00); // TCCR0A = B10000011;
    TCCR1B = _BV(CS00); // TCCR0B = B00000001;
    // fast PWM mode:pwm_pin_kick_
    // 動作クロックは分周なしの16MHz
    // PWMキャリア波の周波数は16MHz/256=62.5kHz
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

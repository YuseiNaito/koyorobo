// シリアル通信してない時signalは全部0

#include "arduino.h"
#include "receiver.h"

namespace koyo {
namespace receiver {
receiver::receiver() {}

data_list::signal receiver::execute() {
  char a = '\0', b = '\0';
  raw_vartical_ = '\0';
  raw_horizontal_ = '\0';
  raw_button0_ == '\0';

  while (Serial.available() > 0) {
    char v = Serial.read();
    if (v == '$') {
      a = Serial.read();
      raw_vartical_ = Serial.read();
    }
    if (v == '%') {
      b = Serial.read();
      raw_horizontal_ = Serial.read();
    }
    if (v == '&') {
      raw_button0_ = Serial.read();
    }
  }

  if (raw_vartical_ >= '0' && raw_vartical_ <= '9')
    ;
  else
    return signal_;

  if (raw_horizontal_ >= '0' && raw_horizontal_ <= '9')
    ;
  else
    return signal_;

  if (raw_button0_ == '0' || raw_button0_ == '1')
    ;
  else
    return signal_;

  signal_.vartical = raw_vartical_ - '0';
  if (a == '-') signal_.vartical *= -1;

  signal_.horizontal = raw_horizontal_ - '0';
  if (b == '-') signal_.horizontal *= -1;

  signal_.button0 = (raw_button0_ == '1') ? true : false;
  return signal_;
}
}  // namespace receiver
}  // namespace koyo

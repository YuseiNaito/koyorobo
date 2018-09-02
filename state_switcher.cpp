#include "action_normal.h"

#include "state_switcher.h"

#include <new.h>

namespace koyo {
namespace state_switcher {
state_switcher::state_switcher() {}

action::base* state_switcher::execute() {
  constexpr unsigned int signals_length{sizeof(signals_) /
                                        sizeof(data_list::signal)};
  for (int i = 0; i < signals_length - 1; i++) {
    signals_[i + 1] = signals_[i];
  }
  signals_[0] = signal_;

  // set current state
  current_state_ = state_switcher::state_switcher::state::normal;

  // set action
  switch (current_state_) {
    default:
      return_action_ = &normal_;
  }

  // set signal
  return_action_->set_signal(signal_);

  return return_action_;
}

void state_switcher::set_signal(const data_list::signal& signal) {
  // update signal
  signal_ = signal;
}
}  // namespace state_switcher
}  // namespace koyo

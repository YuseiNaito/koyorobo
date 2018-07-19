#include "action_normal.h"

#include "state_switcher.h"

namespace koyo {
namespace state_switcher {
state_switcher::state_switcher() {}

action::base* state_switcher::execute(const datail::signal& signal) {
  // update signal
  signal_ = signal;
  
  for (int i = 0; i < 9; i++) {
    signals_[i + 1] = signals_[i];
  }
  signals_[0] = signal_;

  // set current_state_
  current_state_ = state_switcher::state_switcher::state::normal;

  // set action
  switch (current_state_) {
    default:
      return_action_ = new action::normal(signal_);
  }

  return return_action_;
}
}
}

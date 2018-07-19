#ifndef KOYO_STATE_SWITCHER_H
#define KOYO_STATE_SWITCHER_H
#include "action_base.h"
#include "datail.h"

namespace koyo {
namespace state_switcher {
class state_switcher {
public:
  action::base* return_action_;
  datail::signal signals_[10];
  enum class state{normal};
  state_switcher::state_switcher::state current_state_;

  state_switcher();
  action::base* execute(const datail::signal& signal);
private:
    datail::signal& signal_;
};
}
}

#endif

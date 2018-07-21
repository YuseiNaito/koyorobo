#ifndef KOYO_STATE_SWITCHER_H
#define KOYO_STATE_SWITCHER_H
#include "action_base.h"
#include "data_list.h"

namespace koyo {
namespace state_switcher {
class state_switcher {
public:
  action::base* return_action_;
  data_list::signal signals_[10];
  enum class state{normal};
  state_switcher::state_switcher::state current_state_;

  state_switcher();
  action::base* execute(const data_list::signal& signal);
private:
    data_list::signal& signal_;
};
}
}

#endif

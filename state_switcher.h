#ifndef KOYO_STATE_SWITCHER_H
#define KOYO_STATE_SWITCHER_H

#include "action_base.h"
#include "action_normal.h"
#include "data_list.h"

namespace koyo {
namespace state_switcher {
class state_switcher {
 public:
  action::base* return_action_;
  enum class state { normal };
  state_switcher::state_switcher::state current_state_;

  state_switcher(const data_list::signal& signal);
  ~state_switcher();
  action::base* execute();

 private:
  const data_list::signal& signal_;
  data_list::signal signals_[10];

  action::normal* normal_;
};
}  // namespace state_switcher
}  // namespace koyo

#endif

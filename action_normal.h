#ifndef KOYO_ACTION_NORMAL_H
#define KOYO_ACTION_NORMAL_H

#include "action_base.h"
#include "data_list.h"

namespace koyo {
namespace action {
class normal : public base {
 public:
  // using base constructor
  using base::base;

  // for return
  data_list::command command_;

  data_list::command execute();
};
}  // namespace action
}  // namespace koyo

#endif

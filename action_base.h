#ifndef KOYO_ACTION_BASE_H
#define KOYO_ACTION_BASE_H
#include "data_list.h"

namespace koyo {
namespace action {
class base {
 public:
  explicit base();
  virtual ~base();
  void set_signal(const data_list::signal& signal);
  virtual data_list::command execute() = 0;
  const data_list::signal& signal_;
};
}  // namespace action
}  // namespace koyo

#endif

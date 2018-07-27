#ifndef KOYO_ACTION_BASE_H
#define KOYO_ACTION_BASE_H
#include "data_list.h"

namespace koyo {
namespace action {
class base {
 public:
  explicit base(const data_list::signal& signal);
  virtual ~base();
  virtual data_list::command execute() = 0;
  const data_list::signal& signal_;
};
}  // namespace action
}  // namespace koyo

#endif

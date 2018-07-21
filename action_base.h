#ifndef KOYO_ACTION_BASE_H
#define KOYO_ACTION_BASE_H
#include "data_list.h"

namespace koyo {
namespace action {
class base {
public:
  base(data_list::signal& signal) ;
  virtual data_list::command execute() = 0;
  data_list::signal& signal_;
};
}
}

#endif

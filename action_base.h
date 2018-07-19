#ifndef KOYO_ACTION_BASE_H
#define KOYO_ACTION_BASE_H
#include "datail.h"

namespace koyo {
namespace action {
class base {
public:
  base(datail::signal& signal) ;
  virtual datail::command execute() = 0;
  datail::signal& signal_;
};
}
}

#endif

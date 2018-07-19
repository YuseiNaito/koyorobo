#ifndef KOYO_ACTION_NORMAL_H
#define KOYO_ACTION_NORMAL_H
#include "action_base.h"
#include "datail.h"

namespace koyo {
namespace action {
class normal : public base {
public:
  // using base constructor
  using base::base;

  // for return
  datail::command command_;

  datail::command execute();
};
}
}

#endif

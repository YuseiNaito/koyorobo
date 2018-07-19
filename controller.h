#ifndef KOYO_CONTROLLER_H
#define KOYO_CONTROLLER_H
#include "datail.h"

namespace koyo {
namespace controller {
class controller {
public:
  datail::command command_;

  controller();
  datail::command execute();
  void set_command(const datail::command command);
};
}
}

#endif

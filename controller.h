#ifndef KOYO_CONTROLLER_H
#define KOYO_CONTROLLER_H
#include "data_list.h"

namespace koyo {
namespace controller {
class controller {
 public:
  controller();
  data_list::command execute();
  void set_command(const data_list::command command);

 private:
  data_list::command command_;
};
}  // namespace controller
}  // namespace koyo

#endif

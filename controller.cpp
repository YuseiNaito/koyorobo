#include "controller.h"

namespace koyo {
namespace controller {
  controller::controller() {}

  datail::command controller::execute() {
    // sample
    command_.test_data *= 2;

    return command_;
  }

  void controller::set_command(const datail::command command){
    command_ = command;
  }
}
}

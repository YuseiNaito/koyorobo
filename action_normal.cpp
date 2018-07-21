#include "action_normal.h"

namespace koyo {
namespace action {
  data_list::command normal::execute() {
    // sample
    command_.test_data = 2 * signal_.test_data;

    return command_;
  }
}
}

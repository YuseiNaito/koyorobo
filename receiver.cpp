#include "receiver.h"

namespace koyo {
namespace receiver {
  receiver::receiver() {}

  data_list::signal receiver::execute() {
    // sample
    signal_.test_data = 39;

    return signal_;
  }

}
}

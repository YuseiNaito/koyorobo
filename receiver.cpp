#include "receiver.h"

namespace koyo {
namespace receiver {
  receiver::receiver() {}

  datail::signal receiver::execute() {
    // sample
    signal_.test_data = 39;

    return signal_;
  }

}
}

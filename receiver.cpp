#include "receiver.h"

namespace koyo {
namespace receiver {
  receiver::receiver() {}

  data_list::signal receiver::execute() {
    return signal_;
  }

}
}

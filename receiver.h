#ifndef KOYO_RECEIVER_H
#define KOYO_RECEIVER_H
#include "data_list.h"

namespace koyo {
namespace receiver {
class receiver {
public:
  // for return
  data_list::signal signal_;

  receiver();
  data_list::signal execute();
};
}
}

#endif

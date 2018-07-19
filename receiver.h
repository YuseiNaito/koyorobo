#ifndef KOYO_RECEIVER_H
#define KOYO_RECEIVER_H
#include "datail.h"

namespace koyo {
namespace receiver {
class receiver {
public:
  // for return
  datail::signal signal_;

  receiver();
  datail::signal execute();
};
}
}

#endif

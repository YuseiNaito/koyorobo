#ifndef KOYO_RECEIVER_H
#define KOYO_RECEIVER_H

#include "data_list.h"

namespace koyo {
namespace receiver {
class receiver {
 public:
  // for return
  data_list::signal signal_;
  char raw_vartical_;
  char raw_horizontal_;
  char raw_button0_;

  receiver();
  data_list::signal execute();
};
}  // namespace receiver
}  // namespace koyo

#endif

#include "action_base.h"

namespace koyo {
namespace action {
base::base() {}
base::~base() {}
void base::set_signal(const data_list::signal& signal) { signal_ = signal; }
}  // namespace action
}  // namespace koyo

#ifndef KOYO_DATA_LIST_H
#define KOYO_DATA_LIST_H

#define _USE_MATH_DEFINES

#include "F710.h"

#include <math.h>

namespace koyo {
namespace data_list {
// for input
struct signal {
  double vartical;
  double horizontal;
  bool button0;
};

// for output
struct command {
  double vel;
  double omega;
  double weapon;
};

constexpr double wheel_radius{25.0};

constexpr double vel_max{100.0 * 2 * M_PI * wheel_radius};
constexpr double omega_max{M_PI};
constexpr double weapon_max{100.0};
constexpr double stick_res_max{F710::stick_res_max};
}  // namespace data_list
}  // namespace koyo

#endif
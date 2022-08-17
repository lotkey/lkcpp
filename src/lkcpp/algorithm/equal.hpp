////////////////////////////////////////////////////////////////////////////////
/// Written by Lotkey
/// https://www.github.com/lotkey
/// https://www.synthchris.com/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "lkcpp/def.hpp"

namespace lkcpp {
/// Compares a range of values
/// Compares [begin1, end1) to [begin2, end1 - begin1 + begin2)
/// Modeled after std::equal
/// @param begin1 Start of the first range
/// @param end1 End of the first range
/// @param begin2 Start of the second range
template<class T1, class T2>
bool equal(T1 begin1, T1 end1, T2 begin2)
{
  for (lkcpp::size_t i = 0; i < (end1 - begin1); i++) {
    if (begin1[i] != begin2[i]) { return false; }
  }
  return true;
}
} // namespace lkcpp
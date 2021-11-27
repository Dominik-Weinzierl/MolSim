#pragma once

#include "Physics.h"

template<typename T, size_t dim, typename std::enable_if<std::is_base_of<PhysicsType, T>::value, bool>::type = true>
class LinkedCell : public Physics<T, dim> {

};
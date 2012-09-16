#pragma once

#include <stddef.h>
#include <stdint.h>

namespace slib {

extern uint32_t Hash(const char* data, size_t n, uint32_t seed);

}
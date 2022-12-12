#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <stdlib.h>
#include <inttypes.h>

uint32_t Jenkins_one_at_a_time_hash(const char *str, size_t len);

#endif
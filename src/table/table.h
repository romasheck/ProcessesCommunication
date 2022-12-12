#ifndef TABLE_H_INCLUDED
#define TABLE_H_INLUDED

#include <stdlib.h>
#include <inttypes.h>

#define TABLE_LIMIT 100

typedef uint32_t type_t;

enum TABLE_STATUSES
{
    FULL,
    EMPTY,
    NOT_ENF
};

int         StartTableWork          ();

int         TableStatus             ();

int         WaitingWhileTableFull   ();

int         WaitingWhileTableEmpty  ();

int         PutDish                 (const type_t type);

type_t      TakeDish                ();

#endif
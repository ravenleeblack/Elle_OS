#ifndef _port_hub_h_
#define _port_hub_h_
#include "types.h"


// 8-bit port I/O
den read_den(bay port);
void write_den(bay port, den data);

// 16-bit port I/O
bay read_bay(bay port);
void write_bay(bay port, bay data);

// 32-bit port I/O
aisle read_aisle(bay port);
void write_aisle(bay port, aisle data);

#endif
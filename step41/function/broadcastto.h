#include "function.h"

#ifndef _BROADCASTTO_H_
#define _BROADCASTTO_H_

typedef struct broadcastto {
	Function function;
	int dim;
	int* shape;
} BroadcastTo;

void BroadcastTo_init(BroadcastTo* p_self, const int dim, const int* shape);

#endif // _BROADCAST_TO_H_
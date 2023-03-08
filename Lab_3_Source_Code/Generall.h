#ifndef GENERALL_H
#define GENREALL_H

#include "sim_engine.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void sendpkt(int from, int to, int costs[4][4]);
bool updateCosts(int (*costs)[4][4], const int col_update);
bool update_allrt(struct rtpkt *pkt, int (*costs)[4][4], const int node_id);

#endif

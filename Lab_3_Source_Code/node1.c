#include <stdio.h>

#include "sim_engine.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table {
  int costs[4][4];
} dt1;


/* Students to write the following two routines, and maybe some others */

void rtinit1() {
  /* TODO */
}

void rtupdate1(struct rtpkt *rcvdpkt) {
    /* TODO */
}

void printdt1(struct distance_table *dtptr) {
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);
}

void linkhandler1(int linkid, int newcost) {
  /* DON'T CHANGE */
}



#include <stdio.h>

#include "sim_engine.h"
#include "Generall.h"

extern int TRACE;
extern int YES;
extern int NO;

#define INF 999

struct distance_table {
  int costs[4][4];
} dt1;

void printdt1(struct distance_table *dtptr) {
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);
}
/* Students to write the following two routines, and maybe some others */

void rtinit1() {
  /* TODO */

  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      dt1.costs[i][j] = INF;
    }
  }

  dt1.costs[0][1] = 1; //cost mellan nod 0 och 1
  dt1.costs[1][1] = 0; //cost från 1 till 1
  dt1.costs[2][1] = 1; //cost mellan nod 1 och 2
  dt1.costs[3][1] = INF; // nod 3 och 1 har ingen koppling så vi sätter den till INF, (999)
  printdt1(&dt1);

  sendpkt(1, 0, dt1.costs);
  sendpkt(1, 2, dt1.costs);
}

void rtupdate1(struct rtpkt *rcvdpkt) {
    /* TODO */

 printf("\t\033[0;32mRTUPDATE1\n\n");
  printdt1(&dt1);

  if(update_all(rcvdpkt, &dt1.costs, 1)){
    sendpkt(1, 0, dt1.costs);
    sendpkt(1, 2, dt1.costs);
  }
  printdt1(&dt1);
   printf("\t-----------------\n\033[0m");
}

void linkhandler1(int linkid, int newcost) {
  /* DON'T CHANGE */
}



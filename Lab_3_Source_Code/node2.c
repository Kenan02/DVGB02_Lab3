#include <stdio.h>

#include "sim_engine.h"
#include "Generall.h"

extern int TRACE;
extern int YES;
extern int NO;
#define INF 999

struct distance_table
{
  int costs[4][4];
} dt2;

void printdt2(struct distance_table *dtptr)
{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n", dtptr->costs[0][0],
         dtptr->costs[0][1], dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n", dtptr->costs[1][0],
         dtptr->costs[1][1], dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][0],
         dtptr->costs[3][1], dtptr->costs[3][3]);
}

/* Students to write the following two routines, and maybe some others */

void rtinit2()
{
  /* TODO */

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt2.costs[i][j] = INF;
    }
  }

  dt2.costs[0][2] = 3;
  dt2.costs[1][2] = 1;
  dt2.costs[2][2] = 0;
  dt2.costs[3][2] = 2;
  printdt2(&dt2);

  sendpkt(2, 0, dt2.costs);
  sendpkt(2, 1, dt2.costs);
  sendpkt(2, 3, dt2.costs);
}

void rtupdate2(struct rtpkt *rcvdpkt)
{
  /* TODO */

  printf("\t\033[0;32mRTUPDATE2\n\n");
  printdt2(&dt2);

  if (update_all(rcvdpkt, &dt2.costs, 2))
  {
    sendpkt(2, 0, dt2.costs);
    sendpkt(2, 1, dt2.costs);
    sendpkt(2, 3, dt2.costs);
  }
  printdt2(&dt2);
  printf("\t-----------------\n\033[0m");
}

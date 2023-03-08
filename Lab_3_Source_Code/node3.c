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
} dt3;

void printdt3(struct distance_table *dtptr)
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
}
/* Students to write the following two routines, and maybe some others */

void rtinit3()
{
  /* TODO */

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt3.costs[i][j] = INF;
    }
  }

  dt3.costs[0][3] = 7;
  dt3.costs[1][3] = INF;
  dt3.costs[2][3] = 2;
  dt3.costs[3][3] = 0;
  // printdt3(&dt3);

  sendpkt(3, 0, dt3.costs);
  sendpkt(3, 2, dt3.costs);
}

void rtupdate3(struct rtpkt *rcvdpkt)
{
  /* TODO */

  printf("\t\033[0;32mRTUPDATE3\n\n");
  printdt3(&dt3);

  if (update_all(rcvdpkt, &dt3.costs, 3))
  {
    sendpkt(3, 0, dt3.costs);
    sendpkt(3, 2, dt3.costs);
  }
  printdt3(&dt3);
  printf("\t-----------------\n\033[0m");
}

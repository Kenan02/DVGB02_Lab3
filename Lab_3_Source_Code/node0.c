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
} dt0;

void printdt0(struct distance_table *dtptr)
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n", dtptr->costs[1][1],
         dtptr->costs[1][2], dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n", dtptr->costs[2][1],
         dtptr->costs[2][2], dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][1],
         dtptr->costs[3][2], dtptr->costs[3][3]);
}

/* Students to write the following two routines, and maybe some others */

void rtinit0()
{
  /* TODO */

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt0.costs[i][j] = INF;
    }
  }

  dt0.costs[0][0] = 0;
  dt0.costs[1][0] = 1; // cost till nod 1
  dt0.costs[2][0] = 3; // cost till nod 2
  dt0.costs[3][0] = 7; // cost till nod 3
  printdt0(&dt0);

  sendpkt(0, 1, dt0.costs);
  sendpkt(0, 2, dt0.costs);
  sendpkt(0, 3, dt0.costs);
}

void rtupdate0(struct rtpkt *rcvdpkt)
{
  /* TODO */
  printf("  \t\033[0;32mRTUPDATE0\n\n");
  printdt0(&dt0);

  if (update_all(rcvdpkt, &dt0.costs, 0))
  {
    sendpkt(0, 1, dt0.costs);
    sendpkt(0, 2, dt0.costs);
    sendpkt(0, 3, dt0.costs);
  }

  printdt0(&dt0);
  printf("\t-----------------\n\033[0m");
}

void linkhandler0(int linkid, int newcost)
{
  /* DON'T CHANGE */
}

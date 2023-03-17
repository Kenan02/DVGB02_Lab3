// LABB GENOMFÖRD AV KENAN SAHINOVIC OCH OLIVER RANER

#include <stdio.h>

#include "sim_engine.h"

extern int TRACE;
extern int YES;
extern int NO;

#define INF 999

struct distance_table
{
  int costs[4][4];
} dt0;

int minCost0[4], linkcost0[4];

void printdt0(struct distance_table *dtptr)
{
  printf("              cost to   \n");
  printf("   D0 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n", dt0.costs[0][0], dt0.costs[0][1], dt0.costs[0][2], dt0.costs[0][3]);
  printf("     1|  %3d   %3d   %3d  %3d\n", dt0.costs[1][0], dt0.costs[1][1], dt0.costs[1][2], dt0.costs[1][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n", dt0.costs[2][0], dt0.costs[2][1], dt0.costs[2][2], dt0.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n", dt0.costs[3][0], dt0.costs[3][1], dt0.costs[3][2], dt0.costs[3][3]);
}

/* Students to write the following two routines, and maybe some others */

void rtinit0()
{
  struct rtpkt pkt;
  int i, j, src = 0;
  linkcost0[0] = 0, linkcost0[1] = 1, linkcost0[2] = 3, linkcost0[3] = 7;

  // initialisera distance table
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      dt0.costs[i][j] = INF;
    }
  }

  for (i = 0; i < 4; i++)
  {
    dt0.costs[src][i] = linkcost0[i];
    minCost0[i] = dt0.costs[src][i];
  }

  creatertpkt(pkt, 0, 1, minCost0);
  creatertpkt(pkt, 0, 2, minCost0);
  creatertpkt(pkt, 0, 3, minCost0);
}

void rtupdate0(struct rtpkt *rcvdpkt)
{

  struct rtpkt pktsend;

  int i, j, sourceid, v, minVal, source = 0;

  source = rcvdpkt->sourceid;

  for (j = 0; j < 4; j++)
  {
    dt0.costs[sourceid][j] = rcvdpkt->mincost[j];
  }

  int tmp[4], flag = 0;

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      tmp[j] = linkcost0[j] + dt0.costs[j][i];
    }

    minVal = INF;

    for (j = 0; j < 4; j++)
    {
      if (minVal > tmp[j])
      {
        minVal = tmp[j];
      }
    }

    if (i != source && minVal != minCost0[i])
    {
      flag = 1;
      minCost0[i] = minVal;
      dt0.costs[source][i] = minVal;
    }
  }

  if (flag == 1)
  {
    printdt0(&dt0);

    creatertpkt(pktsend, 0, 1, minCost0);
    creatertpkt(pktsend, 0, 2, minCost0);
    creatertpkt(pktsend, 0, 3, minCost0);
  }
  else
  {
    printf("Node 0 recieved update from %d", sourceid);
    printdt0(&dt0);
  }
}

void linkhandler0(int linkid, int newcost)
{
  /* DON'T CHANGE */
}

//LABB GENOMFÖRD AV KENAN SAHINOVIC OCH OLIVER RANER

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

int minCost0[4], linkcost0[0];
struct rtpkt pkt;

void printdt0(struct distance_table *dtptr) {
  printf("              cost to   \n");
  printf("   D3 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n",dt0.costs[0][0], dt0.costs[0][1], dt0.costs[0][2],dt0.costs[0][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n",dt0.costs[2][0], dt0.costs[2][1], dt0.costs[2][2],dt0.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n",dt0.costs[3][0], dt0.costs[3][1], dt0.costs[3][2],dt0.costs[3][3]);
}

/* Students to write the following two routines, and maybe some others */

void rtinit0()
{
  int i, j;
  linkcost0[0] = 0, linkcost0[1] = 1, linkcost0[2] = 3, linkcost0[3] = 7;

  //initialisera distance table
  for (j = 0; j < 4; j++) dt0.costs[0][j] = linkcost0[j];
  for (j = 0; j < 4; j++) dt0.costs[1][j] = INF;
  for (j = 0; j < 4; j++) dt0.costs[2][j] = INF;
  for (j = 0; j < 4; j++) dt0.costs[3][j] = INF;

  printdt0(&dt0);

  for (i = 0; i < 4; i++) minCost0[i] = dt0.costs[0][i];
  creatertpkt(pkt, 0, 1, minCost0);
  creatertpkt(pkt, 0, 2, minCost0);
  creatertpkt(pkt, 0, 3, minCost0);
  
}

void rtupdate0(struct rtpkt *rcvdpkt) 
{
  struct rtpkt rcvpkt;
  int i, j, k, n, sourceid, minVal;

  //börja med att uppdatera distance vector för srcID

  sourceid = rcvpkt.sourceid;
  for (j = 0; j < 4; j++)
    dt0.costs[sourceid][j] = rcvpkt.mincost[j];

  //kolla om noden behöver uppdatera sin distance vector
  int tmpcost[4], flag = 0;

  for (k = 0; k < 4; k++){
    tmpcost[k] = linkcost0[k] + dt0.costs[k][n];
  }

  minVal = INF;
  for (n = 0; n < 4; n++){
      if(minVal > tmpcost[n])
        minVal = tmpcost[n];
  }
  if(k != 0 && minVal != minCost0[k]){
    //Om villkoret uppfylls så har distance vector ändrats, skicka ut update
      flag = 1;
      minCost0[k] = minVal;
      dt0.costs[0][k] = minVal;
  }

  if(flag == 1){
      printdt0(&dt0);
      creatertpkt(rcvpkt, 0, 1, minCost0);
      creatertpkt(rcvpkt, 0, 2, minCost0);
      creatertpkt(rcvpkt, 0, 3, minCost0);
  }else{
      printf("Node 0 received update from node %d\n", sourceid);
      printdt0(&dt0);
  }
}

void linkhandler0(int linkid, int newcost)
{
  /* DON'T CHANGE */
}

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
} dt2;

int minCost2[4], linkCost2[4];
struct rtpkt pkt;

void printdt2(struct distance_table *dtptr) {
  printf("              cost to   \n");
  printf("   D3 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n",dt2.costs[0][0], dt2.costs[0][1], dt2.costs[0][2],dt2.costs[0][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n",dt2.costs[2][0], dt2.costs[2][1], dt2.costs[2][2],dt2.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n",dt2.costs[3][0], dt2.costs[3][1], dt2.costs[3][2],dt2.costs[3][3]);
}

/* Students to write the following two routines, and maybe some others */

void rtinit2()
{
  
   int i, j;
  linkCost2[0] = 3, linkCost2[1] = 1, linkCost2[2] = 0, linkCost2[3] = 2;

  //initialisera distance table
  for (j = 0; j < 4; j++) dt2.costs[0][j] = INF;
  for (j = 0; j < 4; j++) dt2.costs[1][j] = INF;
  for (j = 0; j < 4; j++) dt2.costs[2][j] = linkCost2[j];
  for (j = 0; j < 4; j++) dt2.costs[3][j] = INF;

  printdt0(&dt2);

  for (i = 0; i < 4; i++) minCost2[i] = dt2.costs[2][i];
  creatertpkt(pkt, 2, 0, minCost2);
  creatertpkt(pkt, 2, 1, minCost2);
  creatertpkt(pkt, 2, 3, minCost2);
  
}

void rtupdate2(struct rtpkt *rcvdpkt)
{
  struct rtpkt rcvpkt;
  int i, j, k, n, sourceid, minVal;

  //börja med att uppdatera distance vector för srcID

  sourceid = rcvpkt.sourceid;
  for (j = 0; j < 4; j++)
    dt2.costs[sourceid][j] = rcvpkt.mincost[j];

  //kolla om noden behöver uppdatera sin distance vector
  int tmpcost[4], flag = 0;

  for (k = 0; k < 4; k++){
    tmpcost[k] = linkCost2[k] + dt2.costs[k][n];
  }

  minVal = INF;
  for (n = 0; n < 4; n++){
      if(minVal > tmpcost[n])
        minVal = tmpcost[n];
  }
  if(k != 2 && minVal != minCost2[k]){
    //Om villkoret uppfylls så har distance vector ändrats, skicka ut update
      flag = 1;
      minCost2[k] = minVal;
      dt2.costs[2][k] = minVal;
  }

  if(flag == 1){
      printdt2(&dt2);
      creatertpkt(rcvpkt, 0, 1, minCost2);
      creatertpkt(rcvpkt, 0, 2, minCost2);
      creatertpkt(rcvpkt, 0, 3, minCost2);
  }else{
      printf("Node 2 received update from node %d\n", sourceid);
      printdt0(&dt2);
  }
  
}

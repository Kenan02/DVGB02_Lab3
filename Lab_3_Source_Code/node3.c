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
} dt3;

int minCost3[4], linkCost3[4];
struct rtpkt pkt;

void printdt3(struct distance_table *dtptr) {
  printf("              cost to   \n");
  printf("   D3 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n",dt3.costs[0][0], dt3.costs[0][1], dt3.costs[0][2],dt3.costs[0][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n",dt3.costs[2][0], dt3.costs[2][1], dt3.costs[2][2],dt3.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n",dt3.costs[3][0], dt3.costs[3][1], dt3.costs[3][2],dt3.costs[3][3]);
}
/* Students to write the following two routines, and maybe some others */

void rtinit3()
{
  int i, j;
  linkCost3[0] = 7, linkCost3[1] = INF, linkCost3[2] = 2, linkCost3[3] = 0;

  //initialisera distance table
  for (j = 0; j < 4; j++) dt3.costs[0][j] = INF;
  for (j = 0; j < 4; j++) dt3.costs[1][j] = INF;
  for (j = 0; j < 4; j++) dt3.costs[2][j] = linkCost3[j];
  for (j = 0; j < 4; j++) dt3.costs[3][j] = INF;

  printdt3(&dt3);

  for (i = 0; i < 4; i++) minCost3[i] = dt3.costs[3][i];
  creatertpkt(pkt, 3, 0, minCost3);
  creatertpkt(pkt, 3, 2, minCost3);
  

  
}

void rtupdate3(struct rtpkt *rcvdpkt)
{
 struct rtpkt rcvpkt;
  int i, j, k, n, sourceid, minVal;

  //börja med att uppdatera distance vector för srcID

  sourceid = rcvpkt.sourceid;
  for (j = 0; j < 4; j++)
    dt3.costs[sourceid][j] = rcvpkt.mincost[j];

  //kolla om noden behöver uppdatera sin distance vector
  int tmpcost[4], flag = 0;

  for (k = 0; k < 4; k++){
    tmpcost[k] = linkCost3[k] + dt3.costs[k][n];
  }

  minVal = INF;
  for (n = 0; n < 4; n++){
      if(minVal > tmpcost[n])
        minVal = tmpcost[n];
  }
  if(k != 3 && minVal != minCost3[k]){
    //Om villkoret uppfylls så har distance vector ändrats, skicka ut update
      flag = 1;
      minCost3[k] = minVal;
      dt3.costs[3][k] = minVal;
  }

  if(flag == 1){
      printdt3(&dt3);
      creatertpkt(rcvpkt, 0, 1, minCost3);
      creatertpkt(rcvpkt, 0, 2, minCost3);
      creatertpkt(rcvpkt, 0, 3, minCost3);
  }else{
      printf("Node 2 received update from node %d\n", sourceid);
      printdt3(&dt3);
  }
}

//LABB GENOMFÖRD AV KENAN SAHINOVIC OCH OLIVER RANER

#include <stdio.h>

#include "sim_engine.h"


extern int TRACE;
extern int YES;
extern int NO;

#define INF 999

struct distance_table {
  int costs[4][4];
} dt1;

int minCost1[4], linkcost1[4];
struct rtpkt pkt;

void printdt1(struct distance_table *dtptr) {
  printf("              cost to   \n");
  printf("   D3 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n",dt1.costs[0][0], dt1.costs[0][1], dt1.costs[0][2],dt1.costs[0][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n",dt1.costs[2][0], dt1.costs[2][1], dt1.costs[2][2],dt1.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n",dt1.costs[3][0], dt1.costs[3][1], dt1.costs[3][2],dt1.costs[3][3]);
}
/* Students to write the following two routines, and maybe some others */

void rtinit1() {

   int i, j;
  linkcost1[0] = 0, linkcost1[1] = 1, linkcost1[2] = 3, linkcost1[3] = 7;

  //initialisera distance table
  for (j = 0; j < 4; j++) dt1.costs[0][j] = INF;
  for (j = 0; j < 4; j++) dt1.costs[1][j] = linkcost1[j];
  for (j = 0; j < 4; j++) dt1.costs[2][j] = INF;
  for (j = 0; j < 4; j++) dt1.costs[3][j] = INF;

  printdt1(&dt1);

  for (i = 0; i < 4; i++) minCost1[i] = dt1.costs[1][i];
  creatertpkt(pkt, 1, 0, minCost1);
  creatertpkt(pkt, 1, 2, minCost1);
  
}

void rtupdate1(struct rtpkt *rcvdpkt) {
  struct rtpkt rcvpkt;
  int i, j, k, n, sourceid, minVal;

  //börja med att uppdatera distance vector för srcID

  sourceid = rcvpkt.sourceid;
  for (j = 0; j < 4; j++)
    dt1.costs[sourceid][j] = rcvpkt.mincost[j];

  //kolla om noden behöver uppdatera sin distance vector
  int tmpcost[4], flag = 0;

  for (k = 0; k < 4; k++){
    tmpcost[k] = linkcost1[k] + dt1.costs[k][n];
  }

  minVal = INF;
  for (n = 0; n < 4; n++){
      if(minVal > tmpcost[n])
        minVal = tmpcost[n];
  }
  if(k != 1 && minVal != minCost1[k]){
    //Om villkoret uppfylls så har distance vector ändrats, skicka ut update
      flag = 1;
      minCost1[k] = minVal;
      dt1.costs[1][k] = minVal;
  }

  if(flag == 1){
      printdt1(&dt1);
      creatertpkt(rcvpkt, 1, 0, minCost1);
      creatertpkt(rcvpkt, 1, 2, minCost1);
      
  }else{
      printf("Node 1 received update from node %d\n", sourceid);
      printdt1(&dt1);
  }
 
}

void linkhandler1(int linkid, int newcost) {
  /* DON'T CHANGE */
}



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
} dt2;

int minCost2[4], linkcost2[4];


void printdt2(struct distance_table *dtptr)
{
  printf("              cost to   \n");
  printf("   D2 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n", dt2.costs[0][0], dt2.costs[0][1], dt2.costs[0][2], dt2.costs[0][3]);
  printf("     1|  %3d   %3d   %3d  %3d\n", dt2.costs[1][0], dt2.costs[1][1], dt2.costs[1][2], dt2.costs[1][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n", dt2.costs[2][0], dt2.costs[2][1], dt2.costs[2][2], dt2.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n", dt2.costs[3][0], dt2.costs[3][1], dt2.costs[3][2], dt2.costs[3][3]);
}

/* Students to write the following two routines, and maybe some others */

void rtinit2()
{
  struct rtpkt pkt;
  int i, j, source = 1;
  linkcost2[0] = 1, linkcost2[1] = 0, linkcost2[2] = 1, linkcost2[3] = INF;

  //initialisera distance table
  for(i = 0; i < 4; i++) {
    for(j = 0; j < 4; j++) {
      dt2.costs[i][j] = INF;
    }
  }

	for(i = 0; i < 4; i++) {
    	dt2.costs[source][i]=linkcost2[i];
    	minCost2[i] = dt2.costs[source][i];
  	}

    printdt2(&dt2);

    creatertpkt(pkt, 2, 0, minCost2);
    creatertpkt(pkt, 2, 1, minCost2);
    creatertpkt(pkt, 2, 3, minCost2);
}

void rtupdate2(struct rtpkt *rcvdpkt) {
  
struct rtpkt pktsend;

  int i, j, sourceid, v, minVal, source = 2;

  source = rcvdpkt->sourceid;

  for (j = 0; j < 4; j++){
    dt2.costs[sourceid][j] = rcvdpkt->mincost[j];
  }

  int tmp[4], flag = 0;

  for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      tmp[j] = linkcost2[j] + dt2.costs[j][i];
    }

    minVal = INF;

    for (j = 0; j < 4; j++){
      if(minVal > tmp[j]){
        minVal = tmp[j];
      }
    }

    if(i != source && minVal != minCost2[i])
      {flag = 1;
          minCost2[i] = minVal;
          dt2.costs[source][i] = minVal;
      }
  }

  if(flag == 1){
      printdt2(&dt2);

      creatertpkt(pktsend, 1, 0, minCost2);
      creatertpkt(pktsend, 1, 2, minCost2);
      
  }else{
      printf("Node 1 recieved update from %d", sourceid);
      printdt2(&dt2);
  }
}

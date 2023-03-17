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


void printdt1(struct distance_table *dtptr) {
  printf("              cost to   \n");
  printf("   D1 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n",dt1.costs[0][0], dt1.costs[0][1], dt1.costs[0][2],dt1.costs[0][3]);
  printf("     1|  %3d   %3d   %3d  %3d\n",dt1.costs[1][0], dt1.costs[1][1], dt1.costs[1][2],dt1.costs[1][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n",dt1.costs[2][0], dt1.costs[2][1], dt1.costs[2][2],dt1.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n",dt1.costs[3][0], dt1.costs[3][1], dt1.costs[3][2],dt1.costs[3][3]);
}
/* Students to write the following two routines, and maybe some others */

void rtinit1() {
  struct rtpkt pkt;
  int i, j, source = 1;
  linkcost1[0] = 1, linkcost1[1] = 0, linkcost1[2] = 1, linkcost1[3] = INF;

  //initialisera distance table
  for(i = 0; i < 4; i++) {
    for(j = 0; j < 4; j++) {
      dt1.costs[i][j] = INF;
    }
  }

	for(i = 0; i < 4; i++) {
    	dt1.costs[source][i]=linkcost1[i];
    	minCost1[i] = dt1.costs[source][i];
  	}

    printdt1(&dt1);

    creatertpkt(pkt, 1, 0, minCost1);
    creatertpkt(pkt, 1, 2, minCost1);
  
}

void rtupdate1(struct rtpkt *rcvdpkt) {
  
struct rtpkt pktsend;

  int i, j, sourceid, v, minVal, source = 1;

  source = rcvdpkt->sourceid;

  for (j = 0; j < 4; j++){
    dt1.costs[sourceid][j] = rcvdpkt->mincost[j];
  }

  int tmp[4], flag = 0;

  for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      tmp[j] = linkcost1[j] + dt1.costs[j][i];
    }

    minVal = INF;

    for (j = 0; j < 4; j++){
      if(minVal > tmp[j]){
        minVal = tmp[j];
      }
    }

    if(i != source && minVal != minCost1[i])
      {flag = 1;
          minCost1[i] = minVal;
          dt1.costs[source][i] = minVal;
      }
  }

  if(flag == 1){
      printdt1(&dt1);

      creatertpkt(pktsend, 1, 0, minCost1);
      creatertpkt(pktsend, 1, 2, minCost1);
      
  }else{
      printf("Node 1 recieved update from %d", sourceid);
      printdt1(&dt1);
  }
 
}

void linkhandler1(int linkid, int newcost) {
  /* DON'T CHANGE */
}



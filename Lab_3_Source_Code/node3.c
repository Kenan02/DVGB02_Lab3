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



void printdt3(struct distance_table *dtptr) {
   printf("              cost to   \n");
  printf("   D3 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n", dt3.costs[0][0], dt3.costs[0][1], dt3.costs[0][2], dt3.costs[0][3]);
  printf("     1|  %3d   %3d   %3d  %3d\n", dt3.costs[1][0], dt3.costs[1][1], dt3.costs[1][2], dt3.costs[1][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n", dt3.costs[2][0], dt3.costs[2][1], dt3.costs[2][2], dt3.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n", dt3.costs[3][0], dt3.costs[3][1], dt3.costs[3][2], dt3.costs[3][3]);
}
/* Students to write the following two routines, and maybe some others */

void rtinit3()
{
  struct rtpkt pkt;
  int i, j, source = 3;
  linkCost3[0] = 7, linkCost3[1] = INF, linkCost3[2] = 2, linkCost3[3] = 0;

  //initialisera distance table
    for(i = 0; i < 4; i++) {
    for(j = 0; j < 4; j++) {
      dt3.costs[i][j] = INF;
    }
  }

	for(i = 0; i < 4; i++) {
    dt3.costs[source][i]=linkCost3[i];
    minCost3[i] = dt3.costs[source][i];
  }
  creatertpkt(pkt, 3, 0, minCost3);
  creatertpkt(pkt, 3, 2, minCost3);
  

  
}

void rtupdate3(struct rtpkt *rcvdpkt)
{
  
  struct rtpkt pktsend;

  int i, j, sourceid, v, minVal, source = 3;

  source = rcvdpkt->sourceid;

  for (j = 0; j < 4; j++){
    dt3.costs[sourceid][j] = rcvdpkt->mincost[j];
  }

  int tmp[4], flag = 0;

  for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      tmp[j] = linkCost3[j] + dt3.costs[j][i];
    }

    minVal = INF;

    for (j = 0; j < 4; j++){
      if(minVal > tmp[j]){
        minVal = tmp[j];
      }
    }

    if(i != source && minVal != minCost3[i])
      {flag = 1;
          minCost3[i] = minVal;
          dt3.costs[source][i] = minVal;
      }
  }

  if(flag == 1){
      printdt3(&dt3);

      creatertpkt(pktsend, 1, 0, minCost3);
      creatertpkt(pktsend, 1, 2, minCost3);
      
  }else{
      printf("Node 1 recieved update from %d", sourceid);
      printdt3(&dt3);
  }
}

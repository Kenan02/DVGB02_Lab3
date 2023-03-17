#include <stdio.h>

#include "sim_engine.h"

#define INF 999


extern int TRACE;
extern int YES;
extern int NO;

struct distance_table {
  int costs[4][4];
} dt3;

/* Students to write the following two routines, and maybe some others */
void printdt3(struct distance_table *dtptr);
int minCost3[4];
int linkCost3[4];

void rtinit3() {
  struct rtpkt sendpkt;
	int i,j, source = 3;
	linkCost3[0]=7; linkCost3[1]=INF; linkCost3[2] =2; linkCost3[3] = 0;

  for(i = 0; i < 4; i++) {
    for(j = 0; j < 4; j++) {
      dt3.costs[i][j] = INF;
    }
  }

	for(i = 0; i < 4; i++) {
    dt3.costs[source][i]=linkCost3[i];
    minCost3[i] = dt3.costs[source][i];
  }

  creatertpkt(sendpkt, 3, 0, minCost3);
  creatertpkt(sendpkt, 3, 2, minCost3);
}


void rtupdate3(struct rtpkt *rcvdpkt) {
  struct rtpkt sendpkt;
	int i,j, sourceid,v, minV, source = 3;
	sourceid = rcvdpkt->sourceid;

	for(j = 0; j < 4; j++){
    dt3.costs[sourceid][j] = rcvdpkt->mincost[j];
  }

	int temp[4], flag;
	flag = 0;

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++) {
			temp[j] = linkCost3[j]+dt3.costs[j][i];
    }

		minV = INF;
		for(j = 0; j < 4; j++) {
			if(minV > temp[j]) {
        minV = temp[j];
      }
    }
		if (i != source && minV != minCost3[i]){
			flag = 1; 
			minCost3[i] = minV;
			dt3.costs[source][i] = minV;
		}
	}
  if(flag == 1) {
    printdt3(&dt3);
    
    creatertpkt(sendpkt, 3, 0, minCost3);
    creatertpkt(sendpkt, 3, 2, minCost3);
  } else {
    printf("Node 3 recive update from node %d\n", sourceid);
    printdt3(&dt3);
  }
}

void printdt3(struct distance_table *dtptr) {
  printf("              cost to   \n");
  printf("   D3 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n",dt3.costs[0][0], dt3.costs[0][1], dt3.costs[0][2],dt3.costs[0][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n",dt3.costs[2][0], dt3.costs[2][1], dt3.costs[2][2],dt3.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n",dt3.costs[3][0], dt3.costs[3][1], dt3.costs[3][2],dt3.costs[3][3]);
}

//LABB GENOMFÖRD AV KENAN SAHINOVIC OCH OLIVER RANER

#include <stdio.h>

#include "sim_engine.h"

#define INF 999


extern int TRACE;
extern int YES;
extern int NO;

struct distance_table {
  int costs[4][4];
} dt2;

/* Students to write the following two routines, and maybe some others */
void printdt2(struct distance_table *dtptr);
int minCost2[4];
int linkCost2[4];

void rtinit2() {
  struct rtpkt sendpkt;
	int i,j, source = 2;
	linkCost2[0]=3; linkCost2[1]=1; linkCost2[2] =0; linkCost2[3] = 2;

  for(i = 0; i < 4; i++) {
    for(j = 0; j < 4; j++) {
      dt2.costs[i][j] = INF;
    }
  }

	for(i = 0; i < 4; i++) {
    dt2.costs[source][i]=linkCost2[i];
    minCost2[i] = dt2.costs[source][i];
  }

  creatertpkt(sendpkt, 2, 0, minCost2);
  creatertpkt(sendpkt, 2, 1, minCost2);
  creatertpkt(sendpkt, 2, 3, minCost2);
}

void rtupdate2(struct rtpkt *rcvdpkt) {
  struct rtpkt sendpkt;
	int i,j, sourceid,v, minV, source = 2;
	sourceid = rcvdpkt->sourceid;

	for(j = 0; j < 4; j++){
    dt2.costs[sourceid][j] = rcvdpkt->mincost[j];
  }

	int temp[4], flag;
	flag = 0;

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++) {
			temp[j] = linkCost2[j]+dt2.costs[j][i];
    }

		minV = INF;
		for(j = 0; j < 4; j++) {
			if(minV > temp[j]) {
        minV = temp[j];
      }
    }
		if (i != source && minV != minCost2[i]){
			flag = 1; 
			minCost2[i] = minV;
			dt2.costs[source][i] = minV;
		}
	}
  if(flag == 1) {
    printdt2(&dt2);

    creatertpkt(sendpkt, 2, 0, minCost2);
    creatertpkt(sendpkt, 2, 1, minCost2);
    creatertpkt(sendpkt, 2, 3, minCost2);
  } else {
    printf("Node 2 recive update from node %d\n", sourceid);
    printdt2(&dt2);
  }
}

void printdt2(struct distance_table *dtptr) {
  printf("              cost to   \n");
  printf("   D2 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n",dt2.costs[0][0], dt2.costs[0][1], dt2.costs[0][2],dt2.costs[0][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n",dt2.costs[2][0], dt2.costs[2][1], dt2.costs[2][2],dt2.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n",dt2.costs[3][0], dt2.costs[3][1], dt2.costs[3][2],dt2.costs[3][3]);
}
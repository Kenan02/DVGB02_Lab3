//LABB GENOMFÖRD AV KENAN SAHINOVIC OCH OLIVER RANER

#include <stdio.h>

#include "sim_engine.h"

#define INF 999


extern int TRACE;
extern int YES;
extern int NO;

struct distance_table {
  int costs[4][4];
} dt1;

/* Students to write the following two routines, and maybe some others */
void printdt1(struct distance_table *dtptr);
int minCost1[4];
int linkCost1[4];

void rtinit1() {
  struct rtpkt sendpkt;
	int i,j, source = 1;
	linkCost1[0]=1; linkCost1[1]=0; linkCost1[2] =1; linkCost1[3] = INF;

  for(i = 0; i < 4; i++) {
    for(j = 0; j < 4; j++) {
      dt1.costs[i][j] = INF;
    }
  }

	for(i = 0; i < 4; i++) {
    	dt1.costs[source][i]=linkCost1[i];
    	minCost1[i] = dt1.costs[source][i];
  	}

  creatertpkt(sendpkt, 1, 0, minCost1);
  creatertpkt(sendpkt, 1, 2, minCost1);
}

void rtupdate1(struct rtpkt *rcvdpkt) {
  struct rtpkt sendpkt;
	int i,j, sourceid,v, minV, source = 1;
	sourceid = rcvdpkt->sourceid;

	for(j = 0; j < 4; j++){
		dt1.costs[sourceid][j] = rcvdpkt->mincost[j];
	}

	int temp[4], flag;
	flag = 0;

	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			temp[j] = linkCost1[j]+dt1.costs[j][i];
    	}

		minV = INF;
		for(j = 0; j < 4; j++) {
			if(minV > temp[j]) {
				minV = temp[j];
			}
		}
		if(i != source && minV != minCost1[i]){
			flag = 1; 
			minCost1[i] = minV;
			dt1.costs[source][i] = minV;
		}
	}
  	if(flag == 1) {
    	printdt1(&dt1);
    	creatertpkt(sendpkt, 1, 0, minCost1);
    	creatertpkt(sendpkt, 1, 2, minCost1);
  	} else {
    	printf("Node 1 recive update from node %d\n", sourceid);
    	printdt1(&dt1);
  }
}

void printdt1(struct distance_table *dtptr) {
  printf("              cost to   \n");
  printf("   D1 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n",dt1.costs[0][0], dt1.costs[0][1], dt1.costs[0][2],dt1.costs[0][3]);
  printf("     1|  %3d   %3d   %3d  %3d\n",dt1.costs[1][0], dt1.costs[1][1], dt1.costs[1][2],dt1.costs[1][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n",dt1.costs[2][0], dt1.costs[2][1], dt1.costs[2][2],dt1.costs[2][3]);
}

void linkhandler1(int linkid, int newcost) {
  /* DON'T CHANGE */
}


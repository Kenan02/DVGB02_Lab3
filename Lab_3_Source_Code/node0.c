//LABB GENOMFÖRD AV KENAN SAHINOVIC OCH OLIVER RANER

#include <stdio.h>

#include "sim_engine.h"

#define INF 999


extern int TRACE;
extern int YES;
extern int NO;

struct distance_table {
  int costs[4][4];
} dt0;


/* Students to write the following two routines, and maybe some others */
void printdt0(struct distance_table *dtprt);
int minCost0[4];
int linkCost0[4];

void rtinit0() {
  struct rtpkt sendpkt;
	int i,j, source = 0;
	linkCost0[0] = 0; linkCost0[1] = 1; linkCost0[2] = 3; linkCost0[3] = 7;

  for(i = 0; i < 4; i++) {
    for(j = 0; j < 4; j++) {
      dt0.costs[i][j] = INF;
    }
  }

	for(i = 0; i < 4; i++) {
    dt0.costs[source][i]=linkCost0[i];
    minCost0[i] = dt0.costs[source][i];
  }

  creatertpkt(sendpkt, 0, 1, minCost0);
  creatertpkt(sendpkt, 0, 2, minCost0);
  creatertpkt(sendpkt, 0, 3, minCost0);
}

void rtupdate0(struct rtpkt *rcvdpkt) {
  struct rtpkt sendpkt;
	int i,j, sourceid,v, minV, source = 0;
	sourceid = rcvdpkt->sourceid;

	for(j = 0; j < 4; j++){
    dt0.costs[sourceid][j] = rcvdpkt->mincost[j];
  }

	int temp[4], flag;
	flag = 0;

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++) {
			temp[j] = linkCost0[j]+dt0.costs[j][i];
    }

		minV = INF;
		for(j = 0; j < 4; j++) {
			if(minV > temp[j]) {
        minV = temp[j];
      }
    }
		if (i != source && minV != minCost0[i]){
			flag = 1; 
			minCost0[i] = minV;
			dt0.costs[source][i] = minV;
		}
	}
  if(flag == 1) {
    printdt0(&dt0);

    creatertpkt(sendpkt, 0, 1, minCost0);
    creatertpkt(sendpkt, 0, 2, minCost0);
    creatertpkt(sendpkt, 0, 3, minCost0);
  } else {
    printf("Node 0 recive update from node %d\n", sourceid);
    printdt0(&dt0);
  }
}


void printdt0(struct distance_table *dtptr) {
  printf("              cost to   \n");
  printf("   D0 |    0    1     2    3 \n");
  printf("  ----|----------------------\n");
  printf("     0|  %3d   %3d   %3d  %3d\n",dt0.costs[0][0], dt0.costs[0][1], dt0.costs[0][2],dt0.costs[0][3]);
  printf("     1|  %3d   %3d   %3d  %3d\n",dt0.costs[1][0], dt0.costs[1][1], dt0.costs[1][2],dt0.costs[1][3]);
  printf("from 2|  %3d   %3d   %3d  %3d\n",dt0.costs[2][0], dt0.costs[2][1], dt0.costs[2][2],dt0.costs[2][3]);
  printf("     3|  %3d   %3d   %3d  %3d\n",dt0.costs[3][0], dt0.costs[3][1], dt0.costs[3][2],dt0.costs[3][3]);
}

void linkhandler0(int linkid, int newcost) {
  /* DON'T CHANGE */
}
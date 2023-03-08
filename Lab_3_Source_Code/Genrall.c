#include "Generall.h"
#include "sim_engine.h"

void sendpkt(int from, int to, int costs[4][4])
{
  struct rtpkt pkt;
  pkt.sourceid = from;
  pkt.destid = to;

  pkt.mincost[0] = costs[0][from];
  pkt.mincost[1] = costs[1][from];
  pkt.mincost[2] = costs[2][from];
  pkt.mincost[3] = costs[3][from];

  tolayer2(pkt);
}

bool symmetric_check(int (*costs)[4][4])
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if ((*costs)[i][j] != (*costs)[j][i])
      {
        if ((*costs)[i][j] > (*costs)[j][i])
        {
          (*costs)[i][j] = (*costs)[j][i];
        }
        else
        {
          return false;
        }
      }
    }
  }
  return true;
}

bool updateCosts(int (*costs)[4][4], const int col_update)
{
  bool val = false;

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      const int k = col_update;
      const int n = (*costs)[i][k];
      const int new_n = (*costs)[i][j] + (*costs)[j][k];
      if (new_n < n)
      {
        (*costs)[i][k] = new_n;
        val = true;
      }
    }
  }
  return val;
}

bool update_allrt(struct rtpkt *pkt, int (*costs)[4][4], const int node_id)
{
  if (pkt->destid != node_id)
  {
    printf("INVALID ID RECIEVED");
    exit(1);
  }
  if (pkt->sourceid == node_id)
  {
    printf("Packet sent");
    exit(1);
  }

  bool val = false;
  for (int i = 0; i < 4; i++)
  {
    const int new = pkt->mincost[i];
    const int old = (*costs)[pkt->sourceid][i];

    if (new > old)
    {
      val = true;
      printf("Node %d cost increased from %d to %d with packet from %d to %d\n", node_id, old, new, pkt->sourceid, pkt->destid);
    }
    if (new < old)
    {
      (*costs)[pkt->sourceid][i] = pkt->mincost[i];
      val = true;
    }
  }
  updateCosts(costs, node_id);

  if (symmetric_check(costs) == true)
  {
    printf("Symetrisk\n");
  }
  else
  {
    printf("Ej Symetrisk\n");
  }
  return val;
}

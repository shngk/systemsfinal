/* header. contains k_node class */

#ifndef KFUNCTIONS_H
#define KFUNCTIONS_H

using namespace std;
using std::vector;

// class for representing each iris data point
class k_node {
 public:
  double sep_len;
  double sep_wid;
  double pet_len;
  double pet_wid;

  std :: string species;
};

class centroid;

// functions used in k-means algorithm
centroid * get_random_centroid(int x_max, int y_max);

void assign_pts(vector<vector<string> > data, centroid c1, centroid c2, centroid c3, int x, int y);

centroid * calculate_centroid(centroid *c, int x, int y, int x_max, int y_max);

// function for comparing two centroids
// returns 0 if true, -1 if false
int compare(centroid *c1, centroid *c2);

void print_cluster(centroid * c);

#endif

/* implements function prototypes declared in kfunctions.h
 */

#include <iostream>
#include "kfunctions.h"
#include <math.h>

using namespace std;
using std::vector;

class centroid{
public:
  double x;
  double y;
  vector<vector<string> > elements;

  //  int compare(centroid c2)
    // returns 0 (true) if this centroid is the same as c2

    // 
 
};

centroid* get_random_centroid(){
  double x; // represents petal length, range from 0-7
  double y; // represents petal width, range from 0-3

  x = rand() % 8;
  y = rand() % 4;

  centroid *cent = new centroid();
  cent->x = x;
  cent->y = y;

  return cent;
}
/*DEBUG: well, this lil bitch prints -nan after the first run through the function
instead of the distance it's supposed to calculate.  */
void assign_pts(vector<vector<string> > data, centroid *c1, centroid *c2, centroid *c3){
  // for each item in data, calculate its distance from each centroid and
  // add that item to the vector contained in the centroid it is closest to
  unsigned int i;

  for(i = 0; i < data.size() - 1; i++){
    double d1;
    double d2;
    double d3;
    
    // calculate distance from each centroid
    printf("data[%d][2] = %s, data[%d][3] = %s\n", i, data[i][2].c_str(), i, data[i][3].c_str());  //DEBUG


    double len = atof(data[i][2].c_str());
    double wid = atof(data[i][3].c_str());

    d1 = sqrt(pow((len - c1->x), 2) + pow((wid - c1->y), 2));
    d2 = sqrt(pow((len - c2->x), 2) + pow((wid - c2->y), 2));
    d3 = sqrt(pow((len - c3->x), 2) + pow((wid - c3->y), 2));
    printf("calculated lengths: %f, %f, %f\n", d1, d2, d3); //DEBUG
    // check which distance has the smallest value
    // add the item to the appropriate centroid
    if (d1 <= d2 && d1 <= d3){
      cout << "added to d1\n";
      c1->elements.push_back(data[i]);
    }
    else if(d2 <= d1 && d2 <= d3){
      cout << "added to d2\n";
      c2->elements.push_back(data[i]);
    }
    else if(d3 <= d1 && d3 <= d2){
      cout << "added to d3\n";
      c3->elements.push_back(data[i]);
    }
  }
}

centroid * calculate_centroid(centroid *c){
  // iterate through each centroids elements and average
  // their x values and y values to get the new centroid
  centroid *cent = new centroid();
  double x_mean = 0;
  double y_mean = 0;
  unsigned int i;

  for(i = 0; i < c->elements.size(); i++){
    x_mean += atof(c->elements[i][2].c_str());
    y_mean += atof(c->elements[i][3].c_str());
  }
  x_mean = (x_mean / c->elements.size());
  y_mean = (y_mean / c->elements.size());
  cent->x = x_mean;
  cent->y = y_mean;

  // return the new centroid
  return cent;
}

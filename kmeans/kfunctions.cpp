/* implements function prototypes declared in kfunctions.h
 */

#include <iostream>
#include "kfunctions.h"
#include <math.h>
#include <algorithm> 

using namespace std;
using std::vector;

class centroid{
public:
  double x;
  double y;
  //  double l;
  //  double w;
  
  vector<vector<string> > elements; 
};


/* GET_RANDOM CENTROID: Returns a random centroid within
the plane of data 
~~(CURRENTLY HARD-CODED TO iris.data PARAMS)~~ */
centroid* get_random_centroid(){
  double x; // represents petal length, range from 0-7
  double y; // represents petal width, range from 0-3
  //  double l; // represetns sepal length, ranges from 0-8
  //  double w; // represents sepal width, ranges from 0-5
  
  x = rand() % 8;
  y = rand() % 4;
  //  l = rand() % 9;
  //  w = rand() % 6;
  
  centroid *cent = new centroid();
  cent->x = x;
  cent->y = y;
  //  cent->l = l;
  //  cent->w = w;

  return cent;
}

/* ASSIGN_PTS: takes the vector of data and three centroids
and assigns each item in the vector to one of the 3 centroids */
void assign_pts(vector<vector<string> > data, centroid *c1, centroid *c2, centroid *c3){
  // for each item in data, calculate its distance from each centroid and
  // add that item to the vector contained in the centroid it is closest to
  unsigned int i;

  
  for(i = 0; i < data.size() - 1; i++){
    double d1;
    double d2;
    double d3;
    
    // calculate distance from each centroid
    double pet_len = atof(data[i][2].c_str());
    double pet_wid = atof(data[i][3].c_str());
    //    double sep_len = atof(data[i][0].c_str());
    //    double sep_wid = atof(data[i][0].c_str());
    
    d1 = sqrt(pow((pet_len - c1->x), 2) + pow((pet_wid - c1->y), 2));// +
    //	      pow((sep_len - c1->l), 2) + pow((sep_wid - c1->w), 2));
    d2 = sqrt(pow((pet_len - c2->x), 2) + pow((pet_wid - c2->y), 2));// +
    //	      pow((sep_len - c2->l), 2) + pow((sep_wid - c2->w), 2));
    d3 = sqrt(pow((pet_len - c3->x), 2) + pow((pet_wid - c3->y), 2));// +
    //	      pow((sep_len - c3->l), 2) + pow((pet_len - c3->w), 2));

    // check which distance has the smallest value
    // add the item to the appropriate centroid
    if (d1 <= d2 && d1 <= d3){
      c1->elements.push_back(data[i]);
    }
    else if(d2 <= d1 && d2 <= d3){
      c2->elements.push_back(data[i]);
    }
    else if(d3 <= d1 && d3 <= d2){
      c3->elements.push_back(data[i]);
    }
  }
}


/* CALCULATE_CENTROID: averages the x and y coordinates of each
data element in the list of the previous centroid passed. If a 
centroid has no elements it will call get_random_centroid() */
centroid * calculate_centroid(centroid *c){
  // iterate through each centroids elements and average
  // their x values and y values to get the new centroid
  centroid *cent = new centroid();
  double x_mean = 0;
  double y_mean = 0;
  //  double l_mean = 0;
  //  double w_mean = 0;

  unsigned int i;
  unsigned int c_size = c->elements.size();

  for(i = 0; i < c_size; i++){
    //    l_mean += atof(c->elements[i][0].c_str());
    //    w_mean += atof(c->elements[i][1].c_str());
    x_mean += atof(c->elements[i][2].c_str());
    y_mean += atof(c->elements[i][3].c_str());
  }
  
  //If no data in a centroid
  if(c->elements.size() == 0){
    centroid * temp = get_random_centroid();
    x_mean = temp->x;
    y_mean = temp->y;
    //    l_mean = temp->l;
    //    w_mean = temp->w;
  }
  else{
    x_mean = (x_mean / c_size);
    y_mean = (y_mean / c_size);
    //    l_mean = (l_mean / c_size);
    //    w_mean = (w_mean / c_size);
  }
  cent->x = x_mean;
  cent->y = y_mean;
  //  cent->l = l_mean;
  //  cent->w = w_mean;
  printf("centroid = %f : %f\n", cent->x, cent->y);

  // return the new centroid
  return cent;
}


void print_cluster(centroid * c){
  unsigned int i;
  unsigned int j;

  if(c->elements.size() == 0){
    printf("Sorry! No elements\n");
  }
  
  for(i = 0; i < c->elements.size(); i++){
    for(j = 0; j < c->elements[i].size(); j++){
      printf("%s ", c->elements[i][j].c_str());
    }
    printf("\n");
  }
}

int compare(centroid *c1, centroid *c2){
  vector<string> list1;
  vector<string> list2;
  
  // copy id #s from c1->elements into list1
  for(int i = 0; i < c1->elements.size(); i++){
    list1.push_back(c1->elements[i][5]);
  }

  // copy id #s from c1->elements into list2
  for(int i = 0; i < c2->elements.size(); i++){
    list2.push_back(c2->elements[i][5]);
  }

  // sort lists
  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());

  // comment this out when done:
  // printing the sorted lists to check that this method works correctly:
  for(int i = 0; i < list1.size(); i++){
    cout << "list1: \n";
    cout << list1[i];
    cout << "\n";
  }
  
  // compare the lists
  if(list1 == list2){
    // return 0 if true
    return 0;
  }

  // return -1 if false
  return -1;
}

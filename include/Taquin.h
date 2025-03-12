#ifndef TAQUIN_H
#define TAQUIN_H

#include <iostream>
#include <vector>

using namespace std;

class Taquin {
private:
  vector<unsigned int> T = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  vector<unsigned int> heuristic;
  vector<int> moves;

public:
  Taquin();
  unsigned int where_is_0();
};

#endif
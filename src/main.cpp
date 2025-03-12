#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Taquin {
private:
  vector<unsigned int> T = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  vector<unsigned int> heuristic;
  vector<int> moves;

public:
  Taquin() { heuristic.resize(9, 0); }

  unsigned int where_is_0() {
    for (unsigned int i = 0; i < T.size(); i++) {
      if (T[i] == 0) {
        return i;
      }
    }
  }

  void shuffle_once() {
    unsigned int pos_0 = where_is_0();

    vector<int> possible_moves;

    // Can we move up ? (0 is not in the top row)
    if (pos_0 >= 3) {
      possible_moves.push_back(-3);
    }

    // Can we move right ? (0 is not in the rightmost column)
    if (pos_0 % 3 != 2) {
      possible_moves.push_back(1);
    }

    // Can we move down ? (0 is not in the bottom row)
    if (pos_0 < 6) {
      possible_moves.push_back(3);
    }

    // Can we move left ? (0 is not in the leftmost column)
    if (pos_0 % 3 != 0) {
      possible_moves.push_back(-1);
    }

    // Choose a random move from possible moves
    int move = possible_moves[rand() % possible_moves.size()];

    swap(T[pos_0], T[pos_0 + move]);
  }

  void shuffle(unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
      shuffle_once();
    }
  }

  pair<unsigned int, vector<int>> &possible_moves() {
    unsigned int pos_0 = where_is_0();
    vector<int> possible_moves;
    // Can we move up ? (0 is not in the top row)
    if (pos_0 >= 3) {
      possible_moves.push_back(-3);
    }

    // Can we move right ? (0 is not in the rightmost column)
    if (pos_0 % 3 != 2) {
      possible_moves.push_back(1);
    }

    // Can we move down ? (0 is not in the bottom row)
    if (pos_0 < 6) {
      possible_moves.push_back(3);
    }

    // Can we move left ? (0 is not in the leftmost column)
    if (pos_0 % 3 != 0) {
      possible_moves.push_back(-1);
    }
    pair p(pos_0, possible_moves);
    return p;
  }

  void display() {
    for (unsigned int i = 0; i < T.size(); i++) {
      if (i % 3 == 0) {
        if (i != 0) {
          cout << endl;
        }
      }
      cout << T[i] << " ";
    }
    cout << endl << endl;
  }

  // bool is_solved() {
  //   for (unsigned int i = 0; i < T.size(); i++) {
  //     if (T[i] != i) {
  //       return false;
  //     }
  //   }
  //   return true;
  // }

  void create_heuristic() {
    for (unsigned int i = 0; i < T.size(); i++) {
      if (T[i] != 0) {
        // Current position of a number
        int curr_row = i / 3;
        int curr_col = i % 3;

        // Target position of this number in the original taquin
        int target_row = T[i] / 3;
        int target_col = T[i] % 3;

        // Add Manhattan distance for this tile
        heuristic[i] += abs(curr_row - target_row) + abs(curr_col - target_col);
      }
    }
  }

  void display_heuristic() {
    for (unsigned int i = 0; i < heuristic.size(); i++) {
      if (i % 3 == 0) {
        if (i != 0) {
          cout << endl;
        }
      }
      cout << heuristic[i] << " ";
    }
    cout << endl << endl;
  }

  unsigned int get_heuristic() {
    unsigned int sum = 0;
    for (unsigned int i = 0; i < heuristic.size(); i++) {
      sum += heuristic[i];
    }
    return sum;
  }
};

typedef multimap<unsigned int, Taquin> myMultiMap;
typedef myMultiMap::const_iterator myIterator;

int main() {
  srand(time(0)); // seed for random number generation

  myMultiMap open_list; // multimap to store the taquins linked to the different
                        // f-values
  Taquin t_initial;
  t_initial.shuffle(10);

  cout << "Taquin brassé d'origine:" << endl;
  t_initial.display();

  open_list.insert(pair(t_initial.get_heuristic(), t_initial));

  myIterator it = open_list.begin();

  while (true) {
    Taquin t = it->second;
    open_list.erase(it);

    cout << "Taquin actuel:" << endl;
    t.display();

    if (t.get_heuristic() == 0) {
      cout << "Taquin résolu!" << endl;
      break;
    }

    t.create_heuristic();
    t.display_heuristic();

    t.shuffle_once();
    open_list.insert(make_pair(t.get_heuristic(), t));
  }

  return 0;
}
#include <iostream>
#include "../ship/ship.h"
#include <vector>

using namespace std;

class GameBoard {
    protected:
        vector<WarShip> ships;
        pair<int, int> size;
        vector<vector<char>> squares;
    public:
        // Constructor
        // Setters
        // Getters
        void draw();
        void getShoot(pair<int, int>);
        bool checkVictory();
};
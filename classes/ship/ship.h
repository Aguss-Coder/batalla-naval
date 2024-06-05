#include <iostream>
#include <vector>

using namespace std;

class WarShip {
    protected:
        int size;
        vector<pair<int, int>> coordinates;
        bool sunk;
        bool damaged;
    public:
        // Constructor
        // Setters
        // Getters
        void takeShoot(vector<pair<int, int>>);
        bool isSunk();
};
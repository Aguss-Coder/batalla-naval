#include <iostream>
#include "../board/gameBoard.h"
#include "../ship/ship.h"
#include <vector>

using namespace std;

class Player {
    protected:
        string name;
        GameBoard board;
        vector<WarShip> ships;
        vector<pair<int, int>> shoot;
        bool turn;
    public:
        Player(string, GameBoard, vector<WarShip>, vector<pair<int, int>>, bool);
        void setName();
        void setBoard();
        void setShips();
        void setShoot();
        void setTurn();
        string getName();
        GameBoard getBoard();
        vector<WarShip> getShips();
        vector<pair<int, int>> getShoot();
        bool getTurn();
        void showBoard();
        void locateShip(WarShip);
        pair<int, int> makeShoot();
        bool isSunk();
        void changeTurn();
};
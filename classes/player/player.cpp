#include "player.h"
#include <iostream>

using namespace std;

// Constructors
Player::Player()
{
  name = "Player";
  turn = false;
}
Player::Player(string _name, GameBoard _board, vector<WarShip> _ships, vector<pair<int, int>> _shoot, bool _turn)
{
  name = _name;
  board = _board;
  ships = _ships;
  shoot = _shoot;
  turn = _turn;
}

// Setters
void Player::setName()
{
  cin >> name;
}
void Player::setBoard()
{
  board = GameBoard();
}
void Player::setShips()
{
  ships = vector<WarShip>(5);
}
void Player::setShoot()
{
  shoot = vector<pair<int, int>>(2);
}
void Player::setTurn()
{
  turn = false;
}

// Getters
string Player::getName()
{
  return name;
}
GameBoard Player::getBoard()
{
  return board;
}
vector<WarShip> Player::getShips()
{
  return ships;
}
vector<pair<int, int>> Player::getShoot()
{
  return shoot;
}
bool Player::getTurn()
{
  return turn;
}

// Methods
void Player::showBoard()
{
  board.draw();
}

pair<int, int> Player::makeShoot()
{
}

bool Player::isSunk()
{
}

void Player::changeTurn()
{
  turn = !turn;
}

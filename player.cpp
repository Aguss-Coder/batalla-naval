#include "player.h"
#include <iostream>

using namespace std;

// Constructors
Player::Player()
{
  name = "Player";
  turn = false;
}
Player::Player(string _name, GameBoard _board, pair<int, int> _shoot, bool _turn)
{
  name = _name;
  board = _board;
  shoot = _shoot;
  turn = _turn;

  vector<WarShip> _ships(10);

  _ships.push_back(WarShip(4, 'A'));

  _ships.push_back(WarShip(3, 'B'));
  _ships.push_back(WarShip(3, 'B'));

  _ships.push_back(WarShip(2, 'C'));
  _ships.push_back(WarShip(2, 'C'));
  _ships.push_back(WarShip(2, 'C'));

  _ships.push_back(WarShip(1, 'D'));
  _ships.push_back(WarShip(1, 'D'));
  _ships.push_back(WarShip(1, 'D'));
  _ships.push_back(WarShip(1, 'D'));

  ships = _ships;
}

// Setters
void Player::setName(string _name)
{
  name = _name;
}
void Player::setBoard()
{
  board = GameBoard();
}
void Player::setShoot()
{
  shoot = make_pair(0, 0);
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
GameBoard &Player::getBoard()
{
  return board;
}
vector<WarShip> &Player::getShips()
{
  return ships;
}
pair<int, int> Player::getShoot()
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

pair<int, int> Player::makeShoot(pair<int, int> _coordinates)
{
  shoot = _coordinates;
  return shoot;
}

void Player::changeTurn()
{
  turn = !turn;
}

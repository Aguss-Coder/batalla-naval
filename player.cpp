#include "player.h"
#include <iostream>

using namespace std;

// Constructors
Player::Player()
{
  name = "Player";
  turn = false;
}
Player::Player(string _name, GameBoard _playerBoard, pair<int, int> _shot, bool _turn)
{
  name = _name;
  playerBoard = _playerBoard;
  shot = _shot;
  turn = _turn;
}

// Setters
void Player::setName(string _name)
{
  name = _name;
}
void Player::setPlayerBoard()
{
  playerBoard = GameBoard();
}
void Player::setEnemyBoard()
{
  enemyBoard = GameBoard();
}
void Player::setShips(vector<WarShip> _ships)
{
  ships = _ships;
}
void Player::setShot(pair<int, int> _shot)
{
  shot = _shot;
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
GameBoard &Player::getPlayerBoard()
{
  return playerBoard;
}
GameBoard &Player::getEnemyBoard()
{
  return enemyBoard;
}
vector<WarShip> &Player::getShips()
{
  return ships;
}
pair<int, int> Player::getShot()
{
  return shot;
}
bool Player::getTurn()
{
  return turn;
}

// Methods
void Player::showPlayerBoard()
{
  playerBoard.draw();
}

void Player::showEnemyBoard()
{
  enemyBoard.draw();
}

bool Player::makeShot()
{
  return getEnemyBoard().receiveShot(shot);
}

void Player::changeTurn()
{
  turn = !turn;
}

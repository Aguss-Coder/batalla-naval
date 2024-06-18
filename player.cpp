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
void Player::setOpponentBoard()
{
  opponentBoard = GameBoard();
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
GameBoard &Player::getOpponentBoard()
{
  return opponentBoard;
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
  opponentBoard.draw();
}

bool Player::makeShot()
{
  return getOpponentBoard().receiveShot(shot);
}

void Player::changeTurn()
{
  turn = !turn;
}

void Player::placeShips(vector<WarShip> &ships)
{
  vector<pair<int, int>> coordinates;
  int row, col;
  for (WarShip &ship : ships)
  {
    bool validPlacement = false;
    while (!validPlacement)
    {
      cout << getName() << ", enter the coordinates of the ship " << ship.getSymbol() << endl;
      cout << "Enter the row: ";
      cin >> row;
      cout << "Enter the column: ";
      cin >> col;

      if (ship.getSize() == 1)
      {
        if (!getPlayerBoard().checkCoordinates(make_pair(row, col)))
        {
          cout << "Invalid coordinates. Please try again." << endl;
          continue; // Salta al siguiente ciclo del bucle while
        }
        coordinates.push_back(make_pair(row, col));
        validPlacement = true;
        continue;
      }

      if (!getPlayerBoard().checkCoordinates(make_pair(row, col)))
      {
        cout << "Invalid coordinates. Please try again." << endl;
        continue; // Salta al siguiente ciclo del bucle while
      }

      char direction;
      if (ship.getOrientation() == 'V')
      {
        cout << "Where do you want to place the ship? Up (U) or Down (D): ";
        cin >> direction;
        direction = toupper(direction);
      }
      else if (ship.getOrientation() == 'H')
      {
        cout << "Where do you want to place the ship? Left (L) or Right (R): ";
        cin >> direction;
        direction = toupper(direction);
      }

      validPlacement = true; // Asume que la colocación es válida inicialmente
      for (int i = 0; i < ship.getSize(); i++)
      {
        pair<int, int> newCoord;
        if (ship.getOrientation() == 'V')
        {
          newCoord = (direction == 'U') ? make_pair(row - i, col) : make_pair(row + i, col);
        }
        else // Orientación horizontal
        {
          newCoord = (direction == 'L') ? make_pair(row, col - i) : make_pair(row, col + i);
        }

        if (!getPlayerBoard().checkCoordinates(newCoord))
        {
          cout << "Invalid coordinates for part of the ship. Please try again." << endl;
          validPlacement = false;
          break; // Sale del bucle for y vuelve a solicitar la colocación
        }
        coordinates.push_back(newCoord);
      }

      if (!validPlacement)
      {
        coordinates.clear(); // Limpia las coordenadas para el nuevo intento
      }
    }
    ship.setCoordinates(coordinates);
    coordinates.clear();
  }

  getPlayerBoard().setShips(ships);
  getOpponentBoard().setShips(ships);
}
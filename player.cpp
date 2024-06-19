#include "player.h"
#include <iostream>

using namespace std;

// Constructors
Player::Player()
{
  name = "Player";
  turn = false;
  isPlaying = false;
}
Player::Player(string _name, GameBoard _playerBoard, pair<int, int> _shot, bool _turn)
{
  name = _name;
  playerBoard = _playerBoard;
  shot = _shot;
  turn = _turn;
  isPlaying = false;
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
void Player::setCoordinatesShoted(vector<pair<int, int>> _coordinatesShoted)
{
  coordinatesShoted = _coordinatesShoted;
}
void Player::setShips(vector<WarShip> _ships)
{
  ships = _ships;
}
void Player::setShot(pair<int, int> _shot)
{
  shot = _shot;
}
void Player::setTurn(bool _turn)
{
  turn = _turn;
}
void Player::setIsPlaying(bool _isPlaying)
{
  isPlaying = _isPlaying;
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
vector<pair<int, int>> &Player::getCoordinatesShoted()
{
  return coordinatesShoted;
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
bool Player::getIsPlaying()
{
  return isPlaying;
}

// Methods
void Player::showPlayerBoard()
{
  playerBoard.draw();
}

bool Player::makeShot()
{
  return getPlayerBoard().receiveShot(shot);
}

void Player::changeTurn()
{
  turn = !turn;
}

void Player::placeShips(vector<WarShip> &ships)
{
  vector<pair<int, int>> coordinates;
  vector<pair<int, int>> savedCoordinates;
  int row, col;
  for (WarShip &ship : ships)
  {
    bool validPlacement = false;
    while (!validPlacement)
    {
      bool validInput = false;

      while (!validInput)
      {
        string rowInput, colInput;

        try
        {
          cout << getName() << ", enter the coordinates of the ship " << ship.getSymbol() << endl;
          cout << "Enter the row: ";
          cin >> rowInput;
          cout << "Enter the column: ";
          cin >> colInput;

          row = stoi(rowInput);
          col = stoi(colInput);

          validInput = true;
        }
        catch (const invalid_argument &e)
        {
          cout << "Invalid input. Please try again." << endl;
        }
      }

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

      // verifica si hay un barco en las coordenadas ingresadas

      /* if (savedCoordinates.size() == 0)
      {
        validPlacement = true;
      }
      else
      {
        for (pair<int, int> coord : savedCoordinates)
        {
          if (coord == make_pair(row, col))
          {
            cout << "There is already a ship in this position. Please try again." << endl;
            validPlacement = false;
            break; // Sale del bucle for y vuelve a solicitar la colocación
          }
        }
        validPlacement = true;
      }

      if (!validPlacement)
      {
        continue; // Salta al siguiente ciclo del bucle while
      } */

      validPlacement = true;
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
        savedCoordinates.push_back(newCoord);
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
}
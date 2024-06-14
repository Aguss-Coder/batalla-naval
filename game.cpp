#include <iostream>
#include <fstream>
#include "game.h"
#include "human.h"
#include "bot.h"
#include <limits>

using namespace std;

void Game::choosePlayer()
{
  int choice;
  bool validChoice = false;

  while (!validChoice)
  {
    cout << "Choose your player:" << endl;
    cout << "1. Human" << endl;
    cout << "2. Bot" << endl;

    if (cin >> choice)
    {
      if (choice == 1)
      {
        humanGameplay();
        validChoice = true;
      }
      else if (choice == 2)
      {
        botGameplay();
        validChoice = true;
      }
      else
      {
        cout << "Invalid choice. Please try again." << endl;
      }
    }
    else
    {
      cout << "Invalid choice. Please try again." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}

void Game::newGame()
{
  cout << "Starting new game..." << endl;
  choosePlayer();
}

void Game::loadGame()
{
  cout << "Loading game..." << endl;
  try
  {
    ifstream file("savedGame.txt");

    if (!file.is_open())
    {
      throw runtime_error("Error opening file");
    }

    // function to read the content of the file to the object
  }
  catch (const exception &e)
  {
    cout << "An error ocurred: " << e.what() << '\n';
  }
}

void Game::humanGameplay()
{
  pair<int, int> boardSize;
  string name;
  Human player1;
  Human Player2;

  cout << "set the board size" << endl;
  cout << "Enter the number of rows: ";
  cin >> boardSize.first;
  cout << "Enter the number of columns: ";
  cin >> boardSize.second;

  player1.setBoard();
  Player2.setBoard();

  player1.getBoard().setSize(boardSize);
  Player2.getBoard().setSize(boardSize);

  // set names

  cout << "Enter player 1 name: ";
  cin >> name;
  player1.setName(name);

  cout << "Enter player 2 name: ";
  cin >> name;
  Player2.setName(name);

  // settear la direccion de los barcos

  char orientation;

  for (size_t i = 0; i < player1.getShips().size(); i++)
  {
    cout << player1.getShips()[i].getSymbol() << " orientation" << endl;
    cout << player1.getName() << " enter the orientation of the ship " << player1.getShips()[i].getSymbol() << endl;
    cout << "Enter the orientation (H for horizontal, V for vertical): ";
    cin >> orientation;

    player1.getShips()[i].setOrientation(orientation);
  }

  // set coordinates

  /* vector<pair<int, int>> coordinates;
  int row, col;

  for (WarShip &ship : ships1)
  {
    cout << player1.getName() << " enter the coordinates of the ship " << ship.getSymbol() << endl;

    for (int i = 0; i < ship.getSize(); i++)
    {
      cout << "Enter the row: ";
      cin >> row;
      cout << "Enter the column: ";
      cin >> col;

      coordinates.push_back(make_pair(row, col));
    }

    ship.setCoordinates(coordinates);
    coordinates.clear();
  }

  for (WarShip &ship : ships2)
  {
    cout << Player2.getName() << " enter the coordinates of the ship " << ship.getSymbol() << endl;

    for (int i = 0; i < ship.getSize(); i++)
    {
      cout << "Enter the row: ";
      cin >> row;
      cout << "Enter the column: ";
      cin >> col;

      coordinates.push_back(make_pair(row, col));
    }

    ship.setCoordinates(coordinates);
    coordinates.clear();
  }

  // set squares

  pair<int, int> size = player1.getBoard().getSize();

  player1.getBoard().setSquares({}, ships1, size);
  Player2.getBoard().setSquares({}, ships2, size);

  // draw boards

  cout << player1.getName() << " board:" << endl;
  player1.getBoard().draw();
  cout << endl;

  cout << Player2.getName() << " board:" << endl;
  Player2.getBoard().draw();
  cout << endl; */
}

void Game::botGameplay()
{
  Human player1;
  Bot bot;
}
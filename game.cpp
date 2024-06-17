#include "game.h"
#include "human.h"
#include "bot.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

void Game::clearScreen()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

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

void Game::setHumanGameSettings(Human &player1, Human &player2)
{
  pair<int, int> playerBoardSize;
  string name;

  cout << "set the playerBoard size" << endl;
  cout << "Enter the number of rows: ";
  cin >> playerBoardSize.first;
  cout << "Enter the number of columns: ";
  cin >> playerBoardSize.second;

  player1.setPlayerBoard();
  player1.setEnemyBoard();
  player2.setPlayerBoard();
  player2.setEnemyBoard();

  player1.getPlayerBoard().setSize(playerBoardSize);
  player1.getEnemyBoard().setSize(playerBoardSize);
  player2.getPlayerBoard().setSize(playerBoardSize);
  player2.getEnemyBoard().setSize(playerBoardSize);

  // set names

  cout << "Enter player 1 name: ";
  cin >> name;
  player1.setName(name);

  cout << "Enter player 2 name: ";
  cin >> name;
  player2.setName(name);

  // set ships

  vector<WarShip> _ships;

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

  player1.setShips(_ships);
  player2.setShips(_ships);

  // settear la orientacion de los barcos

  vector<WarShip> ships1 = player1.getShips();
  vector<WarShip> ships2 = player2.getShips();

  char orientation;

  for (WarShip &ship : ships1)
  {
    cout << player1.getName() << " enter the orientation of the ship " << ship.getSymbol() << endl;
    cout << "Enter the orientation (H for horizontal, V for vertical): ";
    cin >> orientation;

    ship.setOrientation(orientation);
  }

  clearScreen();

  for (WarShip &ship : ships2)
  {
    cout << player2.getName() << " enter the orientation of the ship " << ship.getSymbol() << endl;
    cout << "Enter the orientation (H for horizontal, V for vertical): ";
    cin >> orientation;

    ship.setOrientation(orientation);
  }

  clearScreen();

  // set coordinates

  vector<pair<int, int>> coordinates;
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

  clearScreen();

  for (WarShip &ship : ships2)
  {
    cout << player2.getName() << " enter the coordinates of the ship " << ship.getSymbol() << endl;
    cout << ship.getSymbol() << "'s orientation is: " << ship.getOrientation() << endl;

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

  player1.getPlayerBoard().setShips(ships1);
  player1.getEnemyBoard().setShips(ships1);
  player2.getPlayerBoard().setShips(ships2);
  player2.getEnemyBoard().setShips(ships2);

  // set squares

  pair<int, int> size = player1.getPlayerBoard().getSize();

  player1.getPlayerBoard().setSquares(ships1, size);
  player2.getPlayerBoard().setSquares(ships2, size);

  clearScreen();
}

void Game::setBotGameSettings(Human &player1, Bot &player2)
{
  pair<int, int> playerBoardSize;
  string name;

  cout << "set the playerBoard size" << endl;
  cout << "Enter the number of rows: ";
  cin >> playerBoardSize.first;
  cout << "Enter the number of columns: ";
  cin >> playerBoardSize.second;

  player1.setPlayerBoard();
  player2.setPlayerBoard();

  player1.getPlayerBoard().setSize(playerBoardSize);
  player2.getPlayerBoard().setSize(playerBoardSize);

  // set names

  cout << "Enter player 1 name: ";
  cin >> name;
  player1.setName(name);

  // set ships

  vector<WarShip> _ships;

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

  player1.setShips(_ships);
  player2.setShips(_ships);

  // settear la orientacion de los barcos

  vector<WarShip> ships1 = player1.getShips();
  vector<WarShip> ships2 = player2.getShips();

  clearScreen();

  char orientation;

  for (WarShip &ship : ships1)
  {
    cout << player1.getName() << " enter the orientation of the ship " << ship.getSymbol() << endl;
    cout << "Enter the orientation (H for horizontal, V for vertical): ";
    cin >> orientation;

    ship.setOrientation(orientation);
  }

  // set random orientation for bot ships
  srand(time(0));
  for (WarShip &ship : ships2)
  {
    orientation = (rand() % 2) == 0 ? 'H' : 'V';
    ship.setOrientation(orientation);
  }

  clearScreen();

  // set coordinates

  vector<pair<int, int>> coordinates;
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
    row = rand() % playerBoardSize.first;
    col = rand() % playerBoardSize.second;

    coordinates.push_back(make_pair(row, col));
    for (int i = 0; i < ship.getSize(); i++)
    {
      if (ship.getOrientation() == 'H')
      {
        col++;
      }
      else
      {
        row++;
      }

      coordinates.push_back(make_pair(row, col));
    }

    ship.setCoordinates(coordinates);
    coordinates.clear();
  }

  player1.getPlayerBoard().setShips(ships1);
  player2.getPlayerBoard().setShips(ships2);

  // set squares

  pair<int, int> size = player1.getPlayerBoard().getSize();

  player1.getPlayerBoard().setSquares(ships1, size);
  player2.getPlayerBoard().setSquares(ships2, size);

  clearScreen();
}

void Game::humanGameplay()
{
  Human player1;
  Human player2;

  setHumanGameSettings(player1, player2);

  // game loop
  bool gameOver = false;
  int row, col;

  while (!gameOver)
  {
    // player 1 turn

    player1.showPlayerBoard();
    player1.showEnemyBoard();
    cout << player1.getName() << " turn" << endl;
    cout << "Enter the row: ";
    cin >> row;
    cout << "Enter the column: ";
    cin >> col;

    player2.setShot(make_pair(row, col));

    if (player2.makeShot())
    {
      cout << "Hit!" << endl;

      if (player2.getPlayerBoard().checkVictory())
      {
        cout << player1.getName() << " wins!" << endl;
        gameOver = true;
        break;
      }
    }
    else
    {
      cout << "Miss!" << endl;
    }

    this_thread::sleep_for(chrono::seconds(5));

    clearScreen();

    // player 2 turn

    player2.showPlayerBoard();
    cout << player2.getName() << " turn" << endl;
    cout << "Enter the row: ";
    cin >> row;
    cout << "Enter the column: ";
    cin >> col;

    player1.setShot(make_pair(row, col));

    if (player1.makeShot())
    {
      cout << "Hit!" << endl;

      if (player1.getPlayerBoard().checkVictory())
      {
        cout << player2.getName() << " wins!" << endl;
        gameOver = true;
        break;
      }
    }
    else
    {
      cout << "Miss!" << endl;
    }

    this_thread::sleep_for(chrono::seconds(5));

    clearScreen();

    // repeat
  }
}

void Game::botGameplay()
{
  Human player1;
  Bot bot;

  setBotGameSettings(player1, bot);

  // game loop

  bool gameOver = false;
  int row, col;

  while (!gameOver)
  {
    // player 1 turn

    player1.getPlayerBoard().draw();
    cout << player1.getName() << " turn" << endl;
    cout << "Enter the row: ";
    cin >> row;
    cout << "Enter the column: ";
    cin >> col;

    player1.setShot(make_pair(row, col));

    if (bot.getPlayerBoard().receiveShot(make_pair(row, col)))
    {
      cout << "Hit!" << endl;

      if (bot.getPlayerBoard().checkVictory())
      {
        cout << player1.getName() << " wins!" << endl;
        gameOver = true;
        break;
      }
    }
    else
    {
      cout << "Miss!" << endl;
    }

    this_thread::sleep_for(chrono::seconds(5));

    clearScreen();

    // bot turn
    cout << bot.getName() << " turn" << endl;

    row = bot.strategy().first;
    col = bot.strategy().second;

    if (player1.getPlayerBoard().receiveShot(make_pair(row, col)))
    {
      cout << "Hit!" << endl;

      if (player1.getPlayerBoard().checkVictory())
      {
        cout << bot.getName() << " wins!" << endl;
        gameOver = true;
        break;
      }
    }
    else
    {
      cout << "Miss!" << endl;
    }

    this_thread::sleep_for(chrono::seconds(5));

    clearScreen();

    // repeat
  }
}
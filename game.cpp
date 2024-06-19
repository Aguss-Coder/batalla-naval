#include "game.h"
#include "human.h"
#include "bot.h"
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

void Game::choosePlayer(Human &player1, Human &player2, Bot &bot)
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
        setHumanGameSettings(player1, player2);
        humanGameplay(player1, player2);
        validChoice = true;
      }
      else if (choice == 2)
      {
        setBotGameSettings(player1, bot);
        botGameplay(player1, bot);
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

void Game::newGame(Human &player1, Human &player2, Bot &bot)
{
  cout << "Starting new game..." << endl;
  choosePlayer(player1, player2, bot);
}

void Game::loadGame(Human &player1, Human &player2, Bot &bot)
{
  cout << "Loading game..." << endl;
  readGameData(player1, player2, bot);

  if (player2.getIsPlaying() == true)
  {
    humanGameplay(player1, player2);
  }
  else
  {
    botGameplay(player1, bot);
  }
}

void Game::readGameData(Human &player1, Human &player2, Bot &bot)
{
  cout << "Loading game..." << endl;
  try
  {
    ifstream file("savedGame.txt");

    if (!file.is_open())
    {
      throw runtime_error("Error opening file");
    }

    string name;
    bool turn;
    pair<int, int> size;
    vector<vector<char>> squares;
    vector<WarShip> ships;
    bool isPlaying;

    // Load logic
    file >> isPlaying;
    player1.setIsPlaying(isPlaying);

    file >> isPlaying;
    player2.setIsPlaying(isPlaying);

    file >> isPlaying;
    bot.setIsPlaying(isPlaying);

    file >> name;
    player1.setName(name);
    file >> name;
    player2.setName(name);
    file >> name;
    bot.setName(name);

    file >> turn;
    player1.setTurn(turn);
    file >> turn;
    player2.setTurn(turn);
    file >> turn;
    bot.setTurn(turn);

    file >> size.first >> size.second;
    player1.getPlayerBoard().setSize(size);

    file >> size.first >> size.second;
    player2.getPlayerBoard().setSize(size);

    file >> size.first >> size.second;
    bot.getPlayerBoard().setSize(size);

    file >> size.first >> size.second;
    player1.getOpponentBoard().setSize(size);

    file >> size.first >> size.second;
    player2.getOpponentBoard().setSize(size);

    file >> size.first >> size.second;
    bot.getOpponentBoard().setSize(size);

    // player1 ships

    int shipSize;
    char shipSymbol;
    char orientation;
    vector<pair<int, int>> coordinates;

    int shipsSize;
    file >> shipsSize;

    for (int i = 0; i < shipsSize; i++)
    {
      file >> shipSize >> shipSymbol >> orientation;
      WarShip ship(shipSize, shipSymbol);
      ship.setOrientation(orientation);

      for (int j = 0; j < shipSize; j++)
      {
        int row, col;
        file >> row >> col;
        coordinates.push_back(make_pair(row, col));
      }

      ship.setCoordinates(coordinates);
      ships.push_back(ship);
      coordinates.clear();
    }

    player1.getPlayerBoard().setShips(ships);
    player1.getOpponentBoard().setShips(ships);

    // player2 ships

    ships.clear();
    file >> shipsSize;

    for (int i = 0; i < shipsSize; i++)
    {
      file >> shipSize >> shipSymbol >> orientation;
      WarShip ship(shipSize, shipSymbol);
      ship.setOrientation(orientation);

      for (int j = 0; j < shipSize; j++)
      {
        int row, col;
        file >> row >> col;
        coordinates.push_back(make_pair(row, col));
      }

      ship.setCoordinates(coordinates);
      ships.push_back(ship);
      coordinates.clear();
    }

    player2.getPlayerBoard().setShips(ships);
    player2.getOpponentBoard().setShips(ships);

    // bot ships

    ships.clear();
    file >> shipsSize;

    for (int i = 0; i < shipsSize; i++)
    {
      file >> shipSize >> shipSymbol >> orientation;
      WarShip ship(shipSize, shipSymbol);
      ship.setOrientation(orientation);

      for (int j = 0; j < shipSize; j++)
      {
        int row, col;
        file >> row >> col;
        coordinates.push_back(make_pair(row, col));
      }

      ship.setCoordinates(coordinates);
      ships.push_back(ship);
      coordinates.clear();
    }

    bot.setShips(ships);

    // player 1 squares

    file >> size.first >> size.second;
    squares.resize(size.first, vector<char>(size.second));
    for (int i = 0; i < size.first; i++)
    {
      for (int j = 0; j < size.second; j++)
      {
        file >> squares[i][j];
      }
    }

    player1.getPlayerBoard().setSquares(ships, size);
    player1.getOpponentBoard().setSquares(ships, size);

    // player 2 squares

    file >> size.first >> size.second;
    squares.resize(size.first, vector<char>(size.second));
    for (int i = 0; i < size.first; i++)
    {
      for (int j = 0; j < size.second; j++)
      {
        file >> squares[i][j];
      }
    }

    player2.getPlayerBoard().setSquares(ships, size);
    player2.getOpponentBoard().setSquares(ships, size);

    // bot squares

    file >> size.first >> size.second;
    squares.resize(size.first, vector<char>(size.second));
    for (int i = 0; i < size.first; i++)
    {
      for (int j = 0; j < size.second; j++)
      {
        file >> squares[i][j];
      }
    }

    bot.getPlayerBoard().setSquares(ships, size);
    bot.getOpponentBoard().setSquares(ships, size);

    file.close();
    cout << "Game loaded successfully" << endl;
  }
  catch (const exception &e)
  {
    cout << "An error ocurred: " << e.what() << '\n';
  }
}

void Game::setHumanGameSettings(Human &player1, Human &player2)
{
  player1.setIsPlaying(true);
  player2.setIsPlaying(true);

  pair<int, int> playerBoardSize;
  string name;

  bool validInput = false;

  while (!validInput)
  {
    pair<string, string> boardSizeInput;

    cout << "set the playerBoard size" << endl;
    cout << "Enter the number of rows: ";
    cin >> boardSizeInput.first;
    cout << "Enter the number of columns: ";
    cin >> boardSizeInput.second;

    try
    {
      playerBoardSize.first = stoi(boardSizeInput.first);
      playerBoardSize.second = stoi(boardSizeInput.second);
      validInput = true;
    }
    catch (const exception &e)
    {
      cerr << "Invalid input. Please enter a number." << '\n';
    }
  }

  player1.setPlayerBoard();
  player1.setOpponentBoard();
  player2.setPlayerBoard();
  player2.setOpponentBoard();

  player1.getPlayerBoard().setSize(playerBoardSize);
  player1.getOpponentBoard().setSize(playerBoardSize);
  player2.getPlayerBoard().setSize(playerBoardSize);
  player2.getOpponentBoard().setSize(playerBoardSize);

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
    if (ship.getSize() == 1)
    {
      ship.setOrientation('H');
      continue;
    }

    cout << player1.getName() << " enter the orientation of the ship " << ship.getSymbol() << endl;
    cout << "Enter the orientation (H for horizontal, V for vertical): ";
    cin >> orientation;
    orientation = toupper(orientation);

    ship.setOrientation(orientation);
  }

  clearScreen();

  for (WarShip &ship : ships2)
  {
    if (ship.getSize() == 1)
    {
      ship.setOrientation('H');
      continue;
    }

    cout << player2.getName() << " enter the orientation of the ship " << ship.getSymbol() << endl;
    cout << "Enter the orientation (H for horizontal, V for vertical): ";
    cin >> orientation;
    orientation = toupper(orientation);

    ship.setOrientation(orientation);
  }

  clearScreen();

  // set coordinates

  player1.placeShips(ships1);

  clearScreen();

  player2.placeShips(ships2);

  player1.getPlayerBoard().setShips(ships1);
  player2.getOpponentBoard().setShips(ships1);
  player2.getPlayerBoard().setShips(ships2);
  player1.getOpponentBoard().setShips(ships2);

  // set squares

  pair<int, int> size = player1.getPlayerBoard().getSize();

  player1.getPlayerBoard().setSquares(ships1, size);
  player1.getOpponentBoard().setSquares(ships1, size);
  player2.getPlayerBoard().setSquares(ships2, size);
  player2.getOpponentBoard().setSquares(ships2, size);

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

void Game::humanGameplay(Human &player1, Human &player2)
{
  Bot bot;

  // game loop
  bool gameOver = false;
  string rowInput, colInput;
  int row, col;

  while (!gameOver)
  {
    int choice;

    do
    {
      cout << "What do you want to do?" << endl;
      cout << "1. Save game" << endl;
      cout << "2. Continue game" << endl;
      cout << "3. Exit game" << endl;

      cin >> choice;

      // Verifica si la entrada es inválida
      if (cin.fail())
      {
        cin.clear();                                         // Limpia el estado de error de cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada hasta el próximo salto de línea
        choice = 0;                                          // Establece choice a un valor inválido para continuar el bucle
        cout << "Please enter a valid option (1, 2, or 3)." << endl;
      }
      else if (choice < 1 || choice > 3)
      {
        cout << "Please enter a valid option (1, 2, or 3)." << endl;
      }

    } while (choice < 1 || choice > 3);

    switch (choice)
    {
    case 1:
      player1.saveGameData(player1, player2, bot);
      cout << "Game saved." << endl;
      break;
    case 3:
      gameOver = true;
      cout << "Exiting game." << endl;
      exit(0);
      break;
    }

    // player 1 turn

    player1.showPlayerBoard();
    player1.showOpponentBoard();

    bool validShot = false;

    while (!validShot)
    {
      try
      {
        cout << player1.getName() << " turn" << endl;
        cout << "Enter the row: ";
        cin >> rowInput;
        cout << "Enter the column: ";
        cin >> colInput;

        row = stoi(rowInput);
        col = stoi(colInput);
        validShot = true;
      }
      catch (const std::exception &e)
      {
        std::cerr << "Invalid input. Please enter a number." << '\n';
      }
    }

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
    player2.showOpponentBoard();
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

void Game::botGameplay(Human &player1, Bot &bot)
{
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
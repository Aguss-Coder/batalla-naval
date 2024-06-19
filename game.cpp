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

    // Read logic

    // read isPlaying
    bool isPlayer1Playing;
    file >> isPlayer1Playing;
    player1.setIsPlaying(isPlayer1Playing);

    bool isPlayer2Playing;
    file >> isPlayer2Playing;
    player2.setIsPlaying(isPlayer2Playing);

    bool isBotPlaying;
    file >> isBotPlaying;
    bot.setIsPlaying(isBotPlaying);

    // read board size
    pair<int, int> boardSize;
    file >> boardSize.first >> boardSize.second;
    player1.getPlayerBoard().setSize(boardSize);
    player2.getPlayerBoard().setSize(boardSize);
    bot.getPlayerBoard().setSize(boardSize);

    // read player names
    string player1Name;
    file >> player1Name;
    player1.setName(player1Name);

    string player2Name;
    file >> player2Name;
    player2.setName(player2Name);

    string botName;
    file >> botName;
    bot.setName(botName);

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

    player1.setShips(_ships);
    player2.setShips(_ships);
    bot.setShips(_ships);

    // read ships orientation

    // player 1
    vector<WarShip> player1Ships = player1.getShips();
    char orientation;
    for (size_t i = 0; i < player1Ships.size(); i++)
    {
      file >> orientation;
      player1Ships[i].setOrientation(orientation);
    }

    // player 2
    vector<WarShip> player2Ships = player2.getShips();
    for (size_t i = 0; i < player2Ships.size(); i++)
    {
      file >> orientation;
      player2Ships[i].setOrientation(orientation);
    }

    // bot
    vector<WarShip> botShips = bot.getShips();
    for (size_t i = 0; i < botShips.size(); i++)
    {
      file >> orientation;
      botShips[i].setOrientation(orientation);
    }

    // read ships coordinates

    // player 1
    for (WarShip &ship : player1Ships)
    {
      vector<pair<int, int>> coordinates;
      int row, col;
      for (int i = 0; i < ship.getSize(); i++)
      {
        file >> row;
        file >> col;
        coordinates.push_back(make_pair(row, col));
      }
      ship.setCoordinates(coordinates);
    }

    // player 2
    for (WarShip &ship : player2Ships)
    {
      vector<pair<int, int>> coordinates;
      int row, col;
      for (int i = 0; i < ship.getSize(); i++)
      {
        file >> row >> col;
        coordinates.push_back(make_pair(row, col));
      }
      ship.setCoordinates(coordinates);
    }

    // bot
    for (WarShip &ship : botShips)
    {
      vector<pair<int, int>> coordinates;
      int row, col;
      for (int i = 0; i < ship.getSize(); i++)
      {
        file >> row >> col;
        coordinates.push_back(make_pair(row, col));
      }
      ship.setCoordinates(coordinates);
    }

    player1.getPlayerBoard().setShips(player1Ships);
    player2.getPlayerBoard().setShips(player2Ships);
    bot.getPlayerBoard().setShips(botShips);

    // set squares

    pair<int, int> size = player1.getPlayerBoard().getSize();

    player1.getPlayerBoard().setSquares(player1Ships, size);
    player2.getPlayerBoard().setSquares(player2Ships, size);
    bot.getPlayerBoard().setSquares(botShips, size);

    // read coordinates shoted

    // player 1
    vector<pair<int, int>> coordinatesShoted;
    int row, col;
    while (file >> row >> col)
    {
      coordinatesShoted.push_back(make_pair(row, col));
    }
    player1.setCoordinatesShoted(coordinatesShoted);

    // player 2
    coordinatesShoted.clear();
    while (file >> row >> col)
    {
      coordinatesShoted.push_back(make_pair(row, col));
    }
    player2.setCoordinatesShoted(coordinatesShoted);

    // bot
    coordinatesShoted.clear();
    while (file >> row >> col)
    {
      coordinatesShoted.push_back(make_pair(row, col));
    }
    bot.setCoordinatesShoted(coordinatesShoted);

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
  player2.setPlayerBoard();

  player1.getPlayerBoard().setSize(playerBoardSize);
  player2.getPlayerBoard().setSize(playerBoardSize);

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
  player2.getPlayerBoard().setShips(ships2);

  // set squares

  pair<int, int> size = player1.getPlayerBoard().getSize();

  player1.getPlayerBoard().setSquares(ships1, size);
  player2.getPlayerBoard().setSquares(ships2, size);

  clearScreen();
}

void Game::setBotGameSettings(Human &player1, Bot &player2)
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

  // set random orientation for bot ships
  srand(time(0));
  for (WarShip &ship : ships2)
  {
    orientation = (rand() % 2) == 0 ? 'H' : 'V';
    ship.setOrientation(orientation);
  }

  clearScreen();

  // set coordinates

  player1.placeShips(ships1);

  vector<pair<int, int>> coordinates;
  int row, col;

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
  bool hitPlayer1 = false;
  bool hitPlayer2 = false;

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

    cout << player1.getName() << " turn" << endl;
    player1.showPlayerBoard();

    if (player1.getCoordinatesShoted().size() > 0)
    {
      cout << "You attacked this coordinates: ";

      for (pair<int, int> &coord : player1.getCoordinatesShoted())
      {
        cout << "(" << coord.first << ", " << coord.second << ") " << (hitPlayer1 ? "Hit!" : "Miss!");
      }

      cout << endl;
    }

    bool validShot = false;

    while (!validShot)
    {
      try
      {
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

    cout << endl;

    player1.getCoordinatesShoted().push_back(make_pair(row, col));

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
      hitPlayer1 = true;
    }
    else
    {
      cout << "Miss!" << endl;
      hitPlayer1 = false;
    }

    this_thread::sleep_for(chrono::seconds(1));

    clearScreen();

    // player 2 turn

    cout << player2.getName() << " turn" << endl;
    player2.showPlayerBoard();

    if (player1.getCoordinatesShoted().size() > 0)
    {
      cout << "You attacked this coordinates: ";

      for (pair<int, int> &coord : player2.getCoordinatesShoted())
      {
        cout << "(" << coord.first << ", " << coord.second << ") " << (hitPlayer2 ? "Hit!" : "Miss!");
      }
      cout << endl;
    }

    validShot = false;
    while (!validShot)
    {
      try
      {
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

    player2.getCoordinatesShoted().push_back(make_pair(row, col));

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
      hitPlayer2 = true;
    }
    else
    {
      cout << "Miss!" << endl;
      hitPlayer2 = false;
    }

    this_thread::sleep_for(chrono::seconds(1));

    clearScreen();

    // repeat
  }
}

void Game::botGameplay(Human &player1, Bot &bot)
{
  Human player2;

  // game loop
  bool gameOver = false;
  string rowInput, colInput;
  int row, col;
  bool hitPlayer1 = false;

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

    cout << player1.getName() << " turn" << endl;
    player1.showPlayerBoard();

    if (player1.getCoordinatesShoted().size() > 0)
    {
      cout << "You attacked this coordinates: ";

      for (pair<int, int> &coord : player1.getCoordinatesShoted())
      {
        cout << "(" << coord.first << ", " << coord.second << ") " << (hitPlayer1 ? "Hit!" : "Miss!");
      }

      cout << endl;
    }

    bool validShot = false;

    while (!validShot)
    {
      try
      {
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

    cout << endl;

    player1.getCoordinatesShoted().push_back(make_pair(row, col));

    bot.setShot(make_pair(row, col));

    if (bot.getPlayerBoard().receiveShot(make_pair(row, col)))
    {
      cout << "Hit!" << endl;

      if (bot.getPlayerBoard().checkVictory())
      {
        cout << player1.getName() << " wins!" << endl;
        gameOver = true;
        break;
      }
      hitPlayer1 = true;
    }
    else
    {
      cout << "Miss!" << endl;
      hitPlayer1 = false;
    }

    this_thread::sleep_for(chrono::seconds(1));

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

    this_thread::sleep_for(chrono::seconds(1));

    clearScreen();

    // repeat
  }
}
#include "human.h"
#include <iostream>
#include <exception>
#include <fstream>
#include <vector>

using namespace std;

// Constructors
Human::Human()
{
  name = "Player";
  turn = false;
}

// Methods
void Human::saveGameData(Human player1, Human player2, Bot bot)
{
  cout << "Saving game..." << endl;
  try
  {
    ofstream file("savedGame.txt");

    if (!file.is_open())
    {
      throw runtime_error("Error opening file");
    }

    // Save logic

    // save isPlaying
    bool isPlayer1Playing = player1.getIsPlaying();
    file << isPlayer1Playing << endl;

    bool isPlayer2Playing = player2.getIsPlaying();
    file << isPlayer2Playing << endl;

    bool isBotPlaying = bot.getIsPlaying();
    file << isBotPlaying << endl;

    // save board size
    pair<int, int> boardSize = player1.getPlayerBoard().getSize();
    file << boardSize.first << " " << boardSize.second << endl;

    // save player names
    string player1Name = player1.getName();
    file << player1Name << endl;

    string player2Name = player2.getName();
    file << player2Name << endl;

    string botName = bot.getName();
    file << botName << endl;

    // save ships orientation

    // player 1
    vector<WarShip> player1Ships = player1.getPlayerBoard().getShips();
    for (size_t i = 0; i < player1Ships.size(); i++)
    {
      file << player1Ships[i].getOrientation() << " ";
    }
    file << endl;

    // player 2
    vector<WarShip> player2Ships = player2.getPlayerBoard().getShips();
    for (size_t i = 0; i < player2Ships.size(); i++)
    {
      file << player2Ships[i].getOrientation() << " ";
    }
    file << endl;

    // bot
    vector<WarShip> botShips = bot.getPlayerBoard().getShips();
    for (size_t i = 0; i < botShips.size(); i++)
    {
      file << botShips[i].getOrientation() << " ";
    }
    file << endl;

    // save ships coordinates

    // player 1
    for (WarShip ship : player1Ships)
    {
      vector<pair<int, int>> coordinates = ship.getCoordinates();
      for (pair<int, int> coord : coordinates)
      {
        file << coord.first << " " << coord.second << endl;
      }
      file << endl;
    }

    // player 2
    for (WarShip ship : player2Ships)
    {
      vector<pair<int, int>> coordinates = ship.getCoordinates();
      for (pair<int, int> coord : coordinates)
      {
        file << coord.first << " " << coord.second << endl;
      }
      file << endl;
    }

    // bot
    for (WarShip ship : botShips)
    {
      vector<pair<int, int>> coordinates = ship.getCoordinates();
      for (pair<int, int> coord : coordinates)
      {
        file << coord.first << " " << coord.second << endl;
      }
      file << endl;
    }

    // save player 1 coordinates shoted
    vector<pair<int, int>> player1CoordinatesShoted = player1.getCoordinatesShoted();
    for (pair<int, int> coord : player1CoordinatesShoted)
    {
      file << coord.first << " " << coord.second << " ";
    }
    file << endl;

    // save player 2 coordinates shoted
    vector<pair<int, int>> player2CoordinatesShoted = player2.getCoordinatesShoted();
    for (pair<int, int> coord : player2CoordinatesShoted)
    {
      file << coord.first << " " << coord.second << " ";
    }
    file << endl;

    // save bot coordinates shoted
    vector<pair<int, int>> botCoordinatesShoted = bot.getCoordinatesShoted();
    for (pair<int, int> coord : botCoordinatesShoted)
    {
      file << coord.first << " " << coord.second << " ";
    }
    file << endl;

    file.close();
    cout << "Game saved successfully" << endl;
  }
  catch (const exception &e)
  {
    cout << "An error ocurred: " << e.what() << '\n';
  }
}
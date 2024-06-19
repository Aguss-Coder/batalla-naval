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
    bool isPlaying = player1.getIsPlaying();
    file << isPlaying << endl;

    isPlaying = player2.getIsPlaying();
    file << isPlaying << endl;

    isPlaying = bot.getIsPlaying();
    file << isPlaying << endl;

    string player1Name = player1.getName();
    string player2Name = player2.getName();
    string botName = bot.getName();

    bool player1Turn = player1.getTurn();
    bool player2Turn = player2.getTurn();
    bool botTurn = bot.getTurn();

    GameBoard player1Board = player1.getPlayerBoard();
    GameBoard player2Board = player2.getPlayerBoard();
    GameBoard botBoard = bot.getPlayerBoard();

    GameBoard player1OpponentBoard = player1.getOpponentBoard();
    GameBoard player2OpponentBoard = player2.getOpponentBoard();
    GameBoard botOpponentBoard = bot.getOpponentBoard();

    vector<WarShip> player1Ships = player1.getPlayerBoard().getShips();
    vector<WarShip> player2Ships = player2.getPlayerBoard().getShips();
    vector<WarShip> botShips = bot.getPlayerBoard().getShips();

    vector<vector<char>> player1BoardSquares = player1Board.getSquares();
    vector<vector<char>> player2BoardSquares = player2Board.getSquares();
    vector<vector<char>> botBoardSquares = botBoard.getSquares();

    vector<vector<char>> player1OpponentBoardSquares = player1OpponentBoard.getSquares();
    vector<vector<char>> player2OpponentBoardSquares = player2OpponentBoard.getSquares();
    vector<vector<char>> botOpponentBoardSquares = botOpponentBoard.getSquares();

    // Save players names

    file << player1Name << endl;
    file << player2Name << endl;
    file << botName << endl;

    // Save players turns

    file << player1Turn << endl;
    file << player2Turn << endl;
    file << botTurn << endl;

    // Save players boards

    pair<int, int> player1BoardSize = player1Board.getSize();
    pair<int, int> player2BoardSize = player2Board.getSize();
    pair<int, int> botBoardSize = botBoard.getSize();

    file << player1BoardSize.first << " " << player1BoardSize.second << endl;
    file << player2BoardSize.first << " " << player2BoardSize.second << endl;
    file << botBoardSize.first << " " << botBoardSize.second << endl;

    player1BoardSize = player1OpponentBoard.getSize();
    player2BoardSize = player2OpponentBoard.getSize();
    botBoardSize = botOpponentBoard.getSize();

    file << player1BoardSize.first << " " << player1BoardSize.second << endl;
    file << player2BoardSize.first << " " << player2BoardSize.second << endl;
    file << botBoardSize.first << " " << botBoardSize.second << endl;

    // Save player 1 ships

    int player1ShipsSize = player1Ships.size();
    file << player1ShipsSize << endl;

    for (int i = 0; i < player1ShipsSize; i++)
    {
      file << player1Ships[i].getSize() << player1Ships[i].getSymbol() << player1Ships[i].getOrientation();

      for (int j = 0; j < player1Ships[i].getSize(); j++)
      {
        vector<pair<int, int>> position = player1Ships[i].getCoordinates();
        file << position[j].first << " " << position[j].second;
      }
    }

    // Save player 2 ships

    int player2ShipsSize = player2Ships.size();
    file << player2ShipsSize << endl;

    for (int i = 0; i < player2ShipsSize; i++)
    {
      file << player2Ships[i].getSize() << player2Ships[i].getSymbol() << player2Ships[i].getOrientation();

      for (int j = 0; j < player2Ships[i].getSize(); j++)
      {
        vector<pair<int, int>> position = player2Ships[i].getCoordinates();
        file << position[j].first << " " << position[j].second;
      }
    }

    // Save bot ships

    int botShipsSize = botShips.size();
    file << botShipsSize << endl;

    for (int i = 0; i < botShipsSize; i++)
    {
      file << botShips[i].getSize() << botShips[i].getSymbol() << botShips[i].getOrientation();

      for (int j = 0; j < botShips[i].getSize(); j++)
      {
        vector<pair<int, int>> position = botShips[i].getCoordinates();
        file << position[j].first << " " << position[j].second;
      }
    }

    // player 1 squares

    file << player1BoardSize.first << player1BoardSize.second << endl;

    for (int i = 0; i < player1BoardSize.first; i++)
    {
      for (int j = 0; j < player1BoardSize.second; j++)
      {
        file << player1BoardSquares[i][j];
      }
    }

    // player 2 squares

    file << player2BoardSize.first << player2BoardSize.second << endl;

    for (int i = 0; i < player2BoardSize.first; i++)
    {
      for (int j = 0; j < player2BoardSize.second; j++)
      {
        file << player2BoardSquares[i][j];
      }
    }

    // bot squares

    file << botBoardSize.first << botBoardSize.second << endl;

    for (int i = 0; i < botBoardSize.first; i++)
    {
      for (int j = 0; j < botBoardSize.second; j++)
      {
        file << botBoardSquares[i][j];
      }
    }

    file.close();
    cout << "Game saved successfully" << endl;
  }
  catch (const exception &e)
  {
    cout << "An error ocurred: " << e.what() << '\n';
  }
}
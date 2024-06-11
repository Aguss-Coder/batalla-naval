#include "human.h"
#include <iostream>
#include <exception>
#include <fstream>

using namespace std;

// Constructors
Human::Human()
{
  name = "Player";
  turn = false;
}

// Methods
void Human::saveGame()
{
  cout << "Saving game..." << endl;
  try
  {
    ofstream file("savedGame.txt");

    if (!file.is_open())
    {
      throw runtime_error("Error opening file");
    }

    // function to write the content of the object to the file
  }
  catch (const exception &e)
  {
    cout << "An error ocurred: " << e.what() << '\n';
  }
}
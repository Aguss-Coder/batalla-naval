#include <iostream>
#include <vector>
#include "ship.h"

using namespace std;

// constructors
WarShip::WarShip(int size_, vector<pair<int, int>> coordinates_, bool sunk_, bool damaged_, char symbol_, char orientation_)
{
    size = size_;
    coordinates = coordinates_;
    sunk = sunk_;
    damaged = damaged_;
    symbol = symbol_;
    orientation = orientation_;
}
// setters
void WarShip::setSize(int size_)
{
    size = size_;
}

void WarShip::setCoordinates(vector<pair<int, int>> coordinates_)
{
    coordinates = coordinates_;
}

void WarShip::setSunk(bool sunk_)
{
    sunk = sunk_;
}
void WarShip::setDamaged(bool damage_)
{
    damaged = damage_;
}

void WarShip::setSymbol(char symbol_)
{
    symbol = symbol_;
}
void WarShip::setOrientation(char orientation_)
{
    orientation = orientation_;
}
// getters
int WarShip::getSize()
{
    return size;
}
vector<pair<int, int>> WarShip::getCoordinates()
{
    return coordinates;
}
bool WarShip::getSunk()
{
    return sunk;
}
bool WarShip::getDamaged()
{
    return damaged;
}
char WarShip::getSymbol()
{
    return symbol;
}
char WarShip::getOrientation()
{
    return orientation;
}

// Methods

void WarShip::takeShoot(vector<pair<int, int>> shoot)
{
    {
        for (int i = 0; i < coordinates.size(); i++)
        {
            if (coordinates[i].first == shoot[i].first && coordinates[i].second == shoot[i].second)
            {
                damaged = true;
                coordinates.erase(coordinates.begin() + i);
                break;
            }
        }
    }
}

bool WarShip::isSunk()
{
    if (coordinates.empty())
    {
        sunk = true;
        return true;
    }

    return false;
}

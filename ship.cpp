#include <iostream>
#include <vector>
#include "ship.h"

using namespace std;

// constructors
WarShip::WarShip()
{
    size = 0;
    coordinates = {};
    sunk = false;
    damaged = false;
    symbol = ' ';
    orientation = ' ';
}
WarShip::WarShip(int size_, char symbol_)
{
    size = size_;
    sunk = false;
    damaged = false;
    symbol = symbol_;
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
vector<pair<int, int>> WarShip::getCoordinates() const
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
char WarShip::getSymbol() const
{
    return symbol;
}
char WarShip::getOrientation()
{
    return orientation;
}

// Methods

void WarShip::takeShoot(pair<int, int> shoot)
{
    {
        for (size_t i = 0; i < coordinates.size(); i++)
        {
            if (coordinates[i].first == shoot.first && coordinates[i].second == shoot.second)
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


#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <utility>


class Screen {
public:
    Screen(int row, int col);
    void makeFree(int row, int col);
    bool isFree(int row, int col);
    void removeFromFreePool(int row, int col);
    std::pair<int,int> generateRandomFreeCell();

private:
    std::vector< std::vector < int > > screen;
    std::vector< std::pair < int, int > > freepool;
    int freepoolLastIndex;
};

#endif // SCREEN_HPP
#include "screen.hpp"


Screen::Screen(int row, int col){
    screen.resize(col);
    int i = 0;
    for (int r = 0; r < row; r++){
        for(int c = 0; c < col; c++){
            if (c == 0 || r == 0 || r == row - 1 || c == col - 1)
                screen[c].push_back(-1);
            else{
                screen[c].push_back(i);
                freepool.push_back(std::make_pair(r,c));
                i++;
            }
        }
    }
    freepoolLastIndex = freepool.size();
}






void Screen::makeFree(int row, int col){
    int adjustedRow = row - 1;
    if (!isFree(row,col)){
        screen[col][adjustedRow] = freepoolLastIndex;
        freepool.push_back(std::make_pair(adjustedRow,col));
        freepoolLastIndex++;
    }
}






bool Screen::isFree(int row, int col){
    int adjustedRow = row - 1; //adjusting for front end grid starting at one lower level row
    return screen[col][adjustedRow] != -1;
}






void Screen::removeFromFreePool(int row, int col){
    int adjustedRow = row - 1; //adjusting for front end grid starting at one lower level row
    if (isFree(row, col)){
        freepoolLastIndex--;
        freepool[screen[col][adjustedRow]] = freepool[freepoolLastIndex];
        screen[std::get<1>(freepool[freepoolLastIndex])][std::get<0>(freepool[freepoolLastIndex])] = screen[col][adjustedRow];
        freepool.pop_back();
        screen[col][adjustedRow] = -1;
    }
}






std::pair<int,int> Screen::generateRandomFreeCell(){
    srand (time(NULL));
    int randomIndex = rand() % (freepool.size() - 1);
    std::pair<int,int> returnPair = std::make_pair(std::get<0>(freepool[randomIndex]) + 1, std::get<1>(freepool[randomIndex]));
    return returnPair;
}
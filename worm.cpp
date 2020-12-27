#include "worm.hpp"


Worm::Worm(int size, int row, int col){
    worm.resize(size);
    numElements = size;
    _head = 0;
    _tail = _head;
    int adjustedRow = row - 1;
    worm[_head] = std::make_pair(adjustedRow, col);
}






void Worm::addHead(int row, int col){
    _head = (_head + 1) % numElements;
    worm[_head] = std::make_pair(row - 1,col);
}






void Worm::removeTail(){
    _tail = (_tail + 1) % numElements;
}






std::pair< int, int > Worm::head(){
    std::pair<int,int> adjustedHead = std::make_pair(std::get<0>(worm[_head]) + 1, std::get<1>(worm[_head]));
    return adjustedHead;
}






std::pair< int, int > Worm::tail(){
    std::pair<int,int> adjustedTail = std::make_pair(std::get<0>(worm[_tail]) + 1, std::get<1>(worm[_tail]));
    return adjustedTail;
}






int Worm::size(){
    return numElements;
}


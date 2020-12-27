#ifndef WORM_HPP
#define WORM_HPP

#include <vector>
#include <iostream>
#include <utility>

class Worm {
public:
    Worm(int size, int row, int col);
    void addHead(int row, int col);
    void removeTail();
    std::pair< int, int > head();
    std::pair< int, int > tail();
    int size();

private:
    std::vector< std::pair< int, int > > worm;
    int _head, _tail, numElements;
};

#endif // WORM_HPP
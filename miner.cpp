#include <iostream>
#include <string>

using namespace std;

class Miner {
    public:
        Miner() = default;

        virtual void benchmark() = 0;
        virtual void mining(string tri, int min) = 0;
 };

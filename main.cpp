#include <iostream>
#include <string>
#include <cstdlib>
#include "coincoinminer.cpp"


using namespace std;

inline bool checkArgs(int nbr) {
    try {
        if (nbr < 2 || nbr > 6) {
            throw string("Probleme d'arguments !");
        }
    } catch (string const& chaine) {
        cerr << chaine << "\n";
        return false;
    }
    return true;
}

int main( int argc, char *argv[], char *envp[] ) {

    bool isCheck = checkArgs(argc);
    if (!isCheck) {
        return 1;
    }

    string param1(argv[1]);
    auto *miner = new CoinCoinMiner();
    if (param1 == "-z") {
        miner->benchmark();
        if (argc > 2) {
            string param2(argv[2]);
            string tri(argv[3]);
            string param4(argv[4]);
            string min(argv[5]);
            int minInt = stoi(min);
            miner->mining(tri,minInt);
        }
    } else if (param1 == "-tri") {
        string tri(argv[2]);
        string param4(argv[3]);
        string min(argv[4]);
        int minInt = stoi(min);
        miner->mining(tri, minInt);
    }
}
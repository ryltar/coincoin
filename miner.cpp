#include <iostream>
#include <string>

using namespace std;

class Miner{
    public:
        CoinMiner() = default;
    
        virtual bool parserCommandLine(char* argv[], int size) = 0;
        virtual char getRandomChar() = 0;
        virtual string generateNounce() = 0;
        virtual string sha1(unsigned char *data, size_t length) = 0;
        virtual long int unix_timestamp() = 0;
        virtual string baseToken(const string triOwn) = 0;
        virtual inline int check(string pieces, string token, int number) = 0;
        virtual inline bool checkArguments(int number) = 0;
        virtual void benchmark() = 0;
        virtual void mining(string tri, int min) = 0;
        virtual map<string, string> parameters(char* argv[]) = 0;
        virtual void chooseOptions(char* argv[]) = 0;
};

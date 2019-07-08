#include <iostream>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>
#include <map>

using namespace std;

class CoinMiner{
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

class CoinCoinMiner : public CoinMiner{
    protected:
        int poolSize;
        char ascii[97];
    public:
        CoinCoinMiner(){
            string mem =
                "AZERTYUIOPQSDFGHJKLMWXCVBN"
                "azertyuiopqsdfghjklmwxcvbn"
                "0123456789/*-+.!,?;:%*&~#{["
                "`\\^@]}^$\"%<>_-|= ";
            strcpy(ascii, mem.c_str());
            poolSize = sizeof(ascii) - 1;
        };

        bool parserCommandLine(char* argv[], int size) override{
            bool bench = false;
            for(int i = 1; i < size; i++){
                if((string)argv[i] == "-z"){
                    bench = true;
                }
            }
            return bench;
        }

        char getRandomChar() override{
            return ascii[rand() % poolSize];
        }

        string generateNounce() override{
            string nounce;
            for(int i = 0; i < 32; i++){
                nounce += getRandomChar();
            }
            return nounce;
        }

        string sha1(unsigned char *data, size_t length) override{
            unsigned char hash[SHA_DIGEST_LENGTH];
            SHA1(data, length, hash);
            char mdString[SHA_DIGEST_LENGTH];
            for(int i = 0; i < SHA_DIGEST_LENGTH; i++) {
                sprintf(&mdString[i * 2], "%02x", (unsigned int) hash[i]);
            }
            return mdString;
        }

        long int unix_timestamp() override{
            time_t t = time(0);
            long now = static_cast<long int> (t);
            return now;
        }

        string baseToken(const string triOwn) override{
            string token = generateNounce() + "-" + triOwn + "-CC1.0-" + to_string(unix_timestamp()) + "-0f0f0f";
            return token;
        }

        inline int check(string pieces, string token, int number) override{
            int numberOfC = 0;
            unsigned int i = 0;
            while(i < pieces.length()){
                if(pieces[i] == 'c'){
                    numberOfC++;
                    i++;
                }else{
                    i = pieces.length();
                }
            }
            if(numberOfC >= number){
                cout << numberOfC << " c trouvé" << endl;
                cout << pieces << endl;
                cout << token << endl;
            }
            return numberOfC;
        }

        inline bool checkArguments(int number) {
            try {
                if (number < 2 || number > 6) {
                    throw string("You have a problem with your arguments! please check...");
                }else{
                    return true;
                }
            } catch (string const& error) {
                cerr << error << endl;
                return false;
            }
        }

        void benchmark() override{
            cout << "Starting benchmark..." << endl;
            string coin;
            int nbr5c = 0;
            auto start = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds{};
            while (nbr5c < 10) {
                string token = baseToken("GMA");
                char data[token.length()+1];
                strcpy(data, token.c_str());
                size_t length = sizeof(data)-1;
                coin = sha1((unsigned char*) data, length);
                if (coin.substr(0,5) == "ccccc") {
                    auto end = chrono::system_clock::now();
                    elapsed_seconds = end-start;
                    nbr5c++;
                }
            }
            cout << "Benchmark executed in " << elapsed_seconds.count() << "s\n";
            elapsed_seconds = elapsed_seconds/10;
            cout << "5c found in average of " << elapsed_seconds.count() << "s\n";
            cout << "-- Mining projections --" << "\n";
            cout << "Subcoin" << "\t\t" << elapsed_seconds.count()*16 << " s" << "\t" << (elapsed_seconds.count()*16)/3600 << " h" <<"\n";
            cout << "Coin" << "\t\t" << elapsed_seconds.count()*pow(16,2) << " s" << "\t" << (elapsed_seconds.count()*pow(16,2))/3600 << " h" <<"\n";
            cout << "Hexcoin" << "\t\t" << elapsed_seconds.count()*pow(16,3) << " s" << "\t" << (elapsed_seconds.count()*pow(16,3))/3600 << " h" <<"\n";
            cout << "Arkenstone" << "\t" << elapsed_seconds.count()*pow(16,4) << " s" << "\t" << (elapsed_seconds.count()*pow(16,4))/3600 << " h" <<"\n";
            cout << "Blackstar" << "\t" << elapsed_seconds.count()*pow(16,5) << " s" << "\t" << (elapsed_seconds.count()*pow(16,5))/3600 << " h" <<"\n";
            cout << "Grand Cross" << "\t" << elapsed_seconds.count()*pow(16,6) << " s" << "\t" << (elapsed_seconds.count()*pow(16,6))/3600 << " h" <<"\n";
        }

        void mining(string tri, int min) override {

            bool loop = true;
            string token;

            while(loop){
                string token = baseToken(tri);
                char data[token.length()+1];
                strcpy(data, token.c_str());
                size_t length = sizeof(data)-1;
                string test = sha1((unsigned char*)data, length);
                check(test, token, min);
            }
        }

        map<string, string> parameters(char* argv[]) override {
            map<string, string> params;
            params["tri"] = argv[2];
            params["min"] = argv[4];
            return params;
        }

        void chooseOptions(char* argv[]) override {
            if((string)argv[1] == "-z"){
               benchmark();
            }else{
                map<string, string> params = parameters(argv);
                mining(params["tri"], stoi(params["min"]));
            }
        }

};

int main(int argc, char** argv) {
    srand(time(0));
    auto *miner = new CoinCoinMiner();
    bool commandLineTrue = miner->checkArguments(argc);
    if (!commandLineTrue) {
        return 1;
    }else{
        miner->chooseOptions(argv);
    }

    return 0;
}

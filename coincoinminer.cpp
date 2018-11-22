#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include "miner.cpp"
#include "sha1.h"

using namespace std;

class CoinCoinMiner : public Miner {
    public:
        CoinCoinMiner() = default;

        void benchmark() override {
            srand(static_cast<unsigned int>(time(nullptr)));
            default_random_engine generator;
            uniform_real_distribution<float> distribution(32, 126);

            cout << "Démarrage du benchmark..." << "\n";
            int cpt5c = 0;
            string token;
            string coin;

            auto start = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds{};
            while (cpt5c < 10) {
                for(unsigned int i = 0; i < 32; ++i) {
                    token += char(distribution(generator));
                }
                time_t now = time(0);
                token += "-JGE-CC1.0-"+to_string(now)+"-0f0f0f";
                coin = sha1(token);
                if (coin.substr(0,5) == "ccccc") {
                    auto end = chrono::system_clock::now();
                    elapsed_seconds = end-start;
                    cpt5c++;
                }
                token = "";
            }
            cout << "Benchmark fini en " << elapsed_seconds.count() << "s\n";
            elapsed_seconds = elapsed_seconds/10;
            cout << "Moyenne sur 10 pour 5c : " << elapsed_seconds.count() << "s\n";
            cout << "*** Mining projections ***" << "\n";
            cout << "Subcoin" << "\t\t" << elapsed_seconds.count()*16 << " s" << "\t" << (elapsed_seconds.count()*16)/3600 << " h" <<"\n";
            cout << "Coin" << "\t\t" << elapsed_seconds.count()*pow(16,2) << " s" << "\t" << (elapsed_seconds.count()*pow(16,2))/3600 << " h" <<"\n";
            cout << "Hexcoin" << "\t\t" << elapsed_seconds.count()*pow(16,3) << " s" << "\t" << (elapsed_seconds.count()*pow(16,3))/3600 << " h" <<"\n";
            cout << "Arkenstone" << "\t" << elapsed_seconds.count()*pow(16,4) << " s" << "\t" << (elapsed_seconds.count()*pow(16,4))/3600 << " h" <<"\n";
            cout << "Blackstar" << "\t" << elapsed_seconds.count()*pow(16,5) << " s" << "\t" << (elapsed_seconds.count()*pow(16,5))/3600 << " h" <<"\n";
            cout << "Grand Cross" << "\t" << elapsed_seconds.count()*pow(16,6) << " s" << "\t" << (elapsed_seconds.count()*pow(16,6))/3600 << " h" <<"\n";
    }

        void mining(string tri, int min) override {
            cout << "-------------------------------" << "\n";
            cout << "Le minage débute !"<< "\n" << "Le trigramme est : " << tri << "\n" << "Le nombre de 'c' minimum est : " << min << "\n";
            cout << "-------------------------------" << "\n";
            srand(static_cast<unsigned int>(time(nullptr)));
            default_random_engine generator;
            uniform_real_distribution<float> distribution(32, 126);

            bool mining = true;
            string token;
            string coin;
            string stringC;

            for (int j = 0; j < min; ++j) {
                stringC+='c';
            }

            while(mining) {
                for(unsigned int i = 0; i < 32; ++i) {
                    token += char(distribution(generator));
                }
                time_t now = time(0);
                token += "-"+tri+"-CC1.0-"+to_string(now)+"-0f0f0f";
                coin = sha1(token);
                if (coin.substr(0, static_cast<unsigned long>(min)) == stringC) {
                    cout << token << " => " << coin << "\n";
                }
                token = "";
            }
        }
};


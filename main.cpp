#include <iostream>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

static const char ascii[] =
        "AZERTYUIOPQSDFGHJKLMWXCVBN"
        "azertyuiopqsdfghjklmwxcvbn"
        "0123456789/*-+.!,?;:%*&~#{["
        "`\\^@]}^$\"%<>_-|= ";

static int poolSize = sizeof(ascii) - 1;

bool parserCommandLine(char* argv[], int size){
    bool bench = false;
    for(int i = 1; i < size; i++){
        if((string)argv[i] == "-z"){
            bench = true;
        }
    }
    return bench;
}

char getRandomChar(){
    return ascii[rand() % poolSize];
}

string generateNounce(){
    string nounce;
    for(int i = 0; i < 32; i++){
        nounce += getRandomChar();
    }
    return nounce;
}


string sha1(unsigned char *data, size_t length){
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(data, length, hash);
    char mdString[SHA_DIGEST_LENGTH];
    for(int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(&mdString[i * 2], "%02x", (unsigned int) hash[i]);
    }
    return mdString;
}

long int unix_timestamp() {
    time_t t = time(0);
    long now = static_cast<long int> (t);
    return now;
}

string baseToken(const string triOwn){
    string token = generateNounce() + "-" + triOwn + "-CC1.0-" + to_string(unix_timestamp()) + "-0f0f0f";
    return token;
}

void benchmark(){
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
            cout << coin << endl;
            cout << token << endl;
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

int check(string pieces, string token){
    int numberOfC = 0;
    int i = 0;
    while(i < pieces.length()){
        if(pieces[i] == 'c'){
            numberOfC++;
            i++;
        }else{
            i = pieces.length();
        }
    }
    if(numberOfC > 8){
        cout << numberOfC << " c trouvé" << endl;
        cout << pieces << endl;
        cout << token << endl;
    }
    return numberOfC;
}


int main(int argc, char** argv) {
    srand(time(0));
    bool benchmarkArg = parserCommandLine(argv, argc);
    if(benchmarkArg ){
        benchmark();
    }else{
        while(1){
            string token = baseToken("GMA");
            char data[token.length()+1];
            strcpy(data, token.c_str());
            size_t length = sizeof(data)-1;
            string test = sha1((unsigned char*)data, length);
            check(test, token);
        }
    }
    return 0;
}
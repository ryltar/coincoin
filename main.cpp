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

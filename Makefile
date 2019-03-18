coin:
	g++ -Ofast -Wall -Werror -std=c++11 coinminer.cpp -L/usr/lib -lssl -lcrypto -o ./coinminer
packages:
	sudo apt install libssl-dev

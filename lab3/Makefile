all: filehash stringhash diff_analysis test

filehash:
	g++ -std=c++11 -Wall -pedantic Keccak/Keccak.cpp filehash.cpp -o filehash

stringhash:
	g++ -std=c++11 -Wall -pedantic Keccak/Keccak.cpp stringhash.cpp -o stringhash

diff_analysis:
	g++ -std=c++11 -Wall -pedantic Keccak/Keccak.cpp diff_analysis.cpp -o diff_analysis

test:
	gcc test.c -o test


clean:
	rm -rf filehash stringhash test diff_analysis __pycache__ *.stat *.png
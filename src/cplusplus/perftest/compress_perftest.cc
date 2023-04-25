#include "../chimp.h"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std::chrono;

using namespace std;


#define compresstype double

int main(int argc, char *argv[]) {
    int compresswidth = sizeof(compresstype);
    int MAXN = stoi(argv[2]);
    char *src = new char[compresswidth * MAXN];

    if (argc < 2) {
        cout << "lack filename!!!" << endl;
        return -1;
    }
    char *filename = argv[1];
    auto infile = ifstream(filename, std::ios::out | std::ios::binary);

    for (int i = 0; i < MAXN; i++) {
        infile.read((char *) (src + compresswidth * i), compresswidth);
    }

    infile.close();

    int compressed_size;

    CompressOption opt;
    opt.typewidth = 8;

    compressed_size = NumericTypeCompress<double>(sf::encoding::CHIMP, src, compresswidth * MAXN, &opt);

    cout << "Chimp compressed_size: " << compressed_size << endl;
    cout.precision(6);
    cout << fixed;

    cout << "compressed_rate: " << compressed_size * 1.0 / (compresswidth * MAXN) << endl;

    compressed_size = NumericTypeCompress<double>(sf::encoding::GORILLA8_2, src, compresswidth * MAXN, &opt);

    cout << "gorilla2 compressed_size: " << compressed_size << endl;
    cout.precision(6);
    cout << fixed;

    cout << "compressed_rate: " << compressed_size * 1.0 / (compresswidth * MAXN) << endl;


    if (argc >= 3) {
        char *ofile = argv[2];
        auto ofs = ofstream(ofile);
        ofs << "time,value" << endl;
        for (int i = 0; i < MAXN; i++) {
            ofs << i << "," << *((double *) (src + 8 * i)) << endl;
        }
    }
    delete[] src;
}
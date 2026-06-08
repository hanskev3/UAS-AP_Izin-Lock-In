#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, skor;
string qstn;

string toUpper(string &s) {
    for(size_t i=0; i<s.size(); ++i) {
        char c=s[i];
        if(c >= 'a' && c <='z') s[i] = char(c -'a' + 'A');
    }
    return s;
}

string makeqstn(const string countryUpper, int ronde) {
    n = countryUpper.size();
    qstn.clear();
    int removeCount = n/3;\
    if (n - removeCount < 3) removeCount = n - 3;
    vector <bool> removed(n, false);
    
    int removedCount = 0;
    int pos = ronde % n; 
    int step = 1 + (ronde % (n - 1));
    
    while(removedCount < removeCount) {
        if (!removed[pos]) {
            removed[pos] = true;
            ++removedCount;
        }
        pos = (pos + step) % n;
    }
    for (int i = 0; i < n; ++i) {
        if (removed[i]) qstn += " _";
        else qstn += countryUpper[i];
    }
    return qstn;
}

int main() {
    vector<string> countries = {
        "Indonesia", "Jepang", "Amerika", "Jerman", "Perancis",
        "Italia", "Spanyol", "Inggris", "Australia", "Kanada",
        "Meksiko", "Brazil", "Argentina", "Kolombia", "Peru",
        "Chili", "Venezuela", "Ekuador", "Bolivia", "Nurway"
    };

    int ronde = 0;
    size_t index = 0;
    srand(time(0));

    while (true) {
        int randIndex = rand() % countries.size();
        string country = countries[randIndex];
        string countryUpper = toUpper(country);

        string question = makeqstn(countryUpper, ronde);

        cout << "Tebak Negara: " << question << endl;
        cout << "Negara Apakah yang Dimaksud?  ";

        string guess;
        if (!getline(cin, guess)) break;

        string guessUpper = toUpper(guess);

        if (guessUpper == countryUpper) {
            skor += 1;
            cout << "Selamat, Anda Benar!" << endl;
            cout << "Skor Anda: " << skor << endl;
        } else {
            cout << "Maaf Anda Salah. Coba Lagi";
        }

        cout << "Ingin Lanjut Lagi? (Y/N) ";
        string yn;
        if (!getline(cin, yn)) break;
        if (yn.size() > 0 && (yn[0] == 'N' || yn[0] == 'n')) break;

        ++ronde;
        cout << "\n";
    }

    cout << "Game Selesai :D";
    return 0;
}

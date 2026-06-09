#include <iostream>
#include "TebakKata.h"

using namespace std;

int main() {
    char mainLagi;
    char tebakan;
    string namaPemain;

    int tingkatKesulitan;
    int maxNyawa;
    int pengaliSkor;
    int skorAkhir;

    KataGame sesiGame;
    char tebakanSalah[26];
    int jumlahSalah;
    bool gameSelesai;
    bool menang;

    srand(time(0)); 
    
    for (int i = 0; i < 5; i++) {
        leaderboard[i].nama = "";
        leaderboard[i].skor = 0;
    }

    cout << "Selamat Datang di PROJECT TEBAK KATA CLI!\n";
    cout << "Tekan Enter untuk memulai...";
    cin.get();

    do {
        tingkatKesulitan = 0;
        maxNyawa = 0;
        pengaliSkor = 0;
        skorAkhir = 0;
        jumlahSalah = 0;
        gameSelesai = false;
        menang = false;

        bersihkanLayar();
        
        cout << "=== PILIH TINGKAT KESULITAN ===\n";
        cout << "1. Easy   (8 Kesalahan)\n";
        cout << "2. Medium (6 Kesalahan)\n";
        cout << "3. Hard   (4 Kesalahan)\n";
        cout << "Pilihan (1/2/3): ";
        cin >> tingkatKesulitan;

        cin.clear();
        cin.ignore(10000, '\n');

        if (tingkatKesulitan == 1) { 
            maxNyawa = 8; 
            pengaliSkor = 1; 
        }
        else if (tingkatKesulitan == 2) { 
            maxNyawa = 6; 
            pengaliSkor = 2; 
        }
        else if (tingkatKesulitan == 3) { 
            maxNyawa = 4; 
            pengaliSkor = 3; 
        }
        else {
            cout << "Pilihan salah! Otomatis mode Easy.\n";
            maxNyawa = 8; 
            pengaliSkor = 1;
        }

        initGame(&sesiGame, maxNyawa);

        while (gameSelesai == false) {
            tampilkanStatus(&sesiGame, tebakanSalah, jumlahSalah);

            cout << "Masukkan huruf (Ketik '?' untuk Hint): ";
            cin >> tebakan;

            cin.clear();
            cin.ignore(10000, '\n');

            if (tebakan == '?') {
                gunakanHint(&sesiGame);
            } else {
                prosesTebakan(&sesiGame, tebakan, tebakanSalah, &jumlahSalah);
            }

            if (sesiGame.statusTebakan == sesiGame.kataAsli) {
                gameSelesai = true;
                menang = true;
            } 
            else if (sesiGame.sisaNyawa <= 0) {
                gameSelesai = true;
                menang = false;
            }
        }

        bersihkanLayar();
        if (menang == true) {
            skorAkhir = sesiGame.sisaNyawa * 10 * pengaliSkor;
            
            cout << "\n*** SELAMAT! ANDA MENANG ***\n";
            cout << "Kata Rahasia: " << sesiGame.kataAsli << "\n";
            cout << "Skor Anda   : " << skorAkhir << "\n\n";

            cout << "Masukkan nama Anda untuk Leaderboard: ";
            getline(cin, namaPemain);
            
            updateLeaderboard(namaPemain, skorAkhir);
        } else {
            cout << "\n*** GAME OVER! ***\n";
            cout << "Kata yang benar adalah: " << sesiGame.kataAsli << "\n";
        }

        tampilkanLeaderboard();

        cout << "\nMain lagi? (Y/N): ";
        cin >> mainLagi;

        cin.clear();
        cin.ignore(10000, '\n');

    } while (mainLagi == 'Y' || mainLagi == 'y');

    bersihkanLayar();
    cout << "\nTerima kasih sudah bermain!\n";
    return 0;
}

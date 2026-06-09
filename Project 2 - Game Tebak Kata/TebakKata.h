#ifndef TEBAK_KATA_H
#define TEBAK_KATA_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//STRUKTUR DATA
struct KataGame {
    string kataAsli;
    string statusTebakan;
    int sisaNyawa;
};

struct SkorPemain {
    string nama;
    int skor;
};

// === VARIABEL GLOBAL ===
string BANK_KATA[15] = {
    "ALGORITMA", "PEMROGRAMAN", "VARIABEL", "POINTER", "STRUKTUR",
    "FUNGSI", "REKURSIF", "KOMPILATOR", "DATABASE", "ENKRIPSI",
    "JARINGAN", "FRAMEWORK", "DEBUGGING", "TERMINAL", "SINTAKS"
};

SkorPemain leaderboard[5]; 

// === FUNGSI-FUNGSI ===

void bersihkanLayar() {
    system("cls || clear");
}

void initGame(KataGame *game, int nyawa) {
    int indexAcak; 
    
    indexAcak = rand() % 15;
    game->kataAsli = BANK_KATA[indexAcak];
    
    game->statusTebakan = "";
    for (int i = 0; i < game->kataAsli.length(); i++) {
        game->statusTebakan = game->statusTebakan + "_";
    }
    
    game->sisaNyawa = nyawa;
}

void tampilkanStatus(KataGame *game, char tebakanSalah[], int jumlahSalah) {
    cout << "\n========================================\n";
    cout << "KATA RAHASIA : ";
    
    for (int i = 0; i < game->statusTebakan.length(); i++) {
        cout << game->statusTebakan[i] << " ";
    }
    
    cout << "\n\nSisa Nyawa   : " << game->sisaNyawa << "\n";
    cout << "Riwayat Salah: ";
    
    for (int i = 0; i < jumlahSalah; i++) {
        cout << tebakanSalah[i];
        if (i < jumlahSalah - 1) {
            cout << ", ";
        }
    }
    cout << "\n========================================\n";
}

void gunakanHint(KataGame *game) {
    if (game->sisaNyawa > 1) {
        for (int i = 0; i < game->kataAsli.length(); i++) {
            if (game->statusTebakan[i] == '_') {
                game->statusTebakan[i] = game->kataAsli[i]; 
                game->sisaNyawa = game->sisaNyawa - 1;      
                cout << "\n[!] HINT AKTIF: 1 Huruf terbuka! Nyawa berkurang 1.\n";
                break; 
            }
        }
    } else {
        cout << "\n[!] GAGAL: Nyawa Anda tidak cukup untuk Hint!\n";
    }
}

void prosesTebakan(KataGame *game, char tebakan, char tebakanSalah[], int *jumlahSalah) {
    // Deklarasi variabel pencarian di atas
    bool ketemu; 
    ketemu = false;

    if (tebakan >= 'a' && tebakan <= 'z') {
        tebakan = tebakan - 32; 
    }

    for (int i = 0; i < game->statusTebakan.length(); i++) {
        if (game->statusTebakan[i] == tebakan) {
            cout << "\n[-] Huruf '" << tebakan << "' sudah ditebak benar. Cari huruf lain!\n";
            return;
        }
    }

    for (int i = 0; i < *jumlahSalah; i++) {
        if (tebakanSalah[i] == tebakan) {
            cout << "\n[-] Huruf '" << tebakan << "' sudah ditebak salah. Cari huruf lain!\n";
            return;
        }
    }

    for (int i = 0; i < game->kataAsli.length(); i++) {
        if (game->kataAsli[i] == tebakan) {
            game->statusTebakan[i] = tebakan; 
            ketemu = true;
        }
    }

    if (ketemu == false) {
        tebakanSalah[*jumlahSalah] = tebakan;
        *jumlahSalah = *jumlahSalah + 1;
        game->sisaNyawa = game->sisaNyawa - 1;
        cout << "\n[X] SALAH! Huruf '" << tebakan << "' tidak ada.\n";
    } else {
        cout << "\n[V] BENAR! Lanjutkan.\n";
    }
}

void updateLeaderboard(string nama, int skor) {
    for (int i = 0; i < 5; i++) {
        if (skor > leaderboard[i].skor) {
            for (int j = 4; j > i; j--) {
                leaderboard[j] = leaderboard[j - 1];
            }
            leaderboard[i].nama = nama;
            leaderboard[i].skor = skor;
            break;
        }
    }
}

void tampilkanLeaderboard() {
    // Deklarasi flag data di atas
    int adaData; 
    adaData = 0;
    
    cout << "\n--- TOP 5 LEADERBOARD ---\n";
    for (int i = 0; i < 5; i++) {
        if (leaderboard[i].nama != "") {
            cout << i + 1 << ". " << leaderboard[i].nama << " \t- " << leaderboard[i].skor << " Poin\n";
            adaData = 1;
        }
    }
    if (adaData == 0) {
        cout << "(Belum ada skor)\n";
    }
    cout << "-------------------------\n";
}

#endif
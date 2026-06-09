#include <iostream>
#include "TebakKata.h"

using namespace std;

int main() {
    // Variabel Kontrol Utama
    char mainLagi;
    char tebakan;
    string namaPemain;
    
    // Variabel Pengaturan Tingkat Kesulitan
    int tingkatKesulitan;
    int maxNyawa;
    int pengaliSkor;
    int skorAkhir;
    
    // Variabel Status Permainan (Sesi Game)
    KataGame sesiGame;
    char tebakanSalah[26];
    int jumlahSalah;
    bool gameSelesai;
    bool menang;

    // 2. PERSIAPAN AWAL PROGRAM (Dijalankan 1x)
    srand(time(0)); 

    // Kosongkan leaderboard di awal game
    for (int i = 0; i < 5; i++) {
        leaderboard[i].nama = "";
        leaderboard[i].skor = 0;
    }

    cout << "Selamat Datang di PROJECT TEBAK KATA CLI!\n";
    cout << "Tekan Enter untuk memulai...";
    cin.get();

    // 3. LOOP UTAMA PERMAINAN
    do {
        // RESET VARIABEL UNTUK RONDE BARU
        // (Agar sisa data dari game sebelumnya terhapus)
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

        // Logika percabangan untuk setingan game
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

        // Panggil fungsi inisialisasi
        initGame(&sesiGame, maxNyawa);

        // Looping selama game belum selesai (Menebak Kata)
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

            // Cek kondisi Menang / Kalah
            if (sesiGame.statusTebakan == sesiGame.kataAsli) {
                gameSelesai = true;
                menang = true;
            } 
            else if (sesiGame.sisaNyawa <= 0) {
                gameSelesai = true;
                menang = false;
            }
        }

        // 4. HASIL AKHIR & LEADERBOARD
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
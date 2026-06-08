#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAKS = 10;

class Minesweeper {
private:
    int  papan[MAKS][MAKS];
    bool terbuka[MAKS][MAKS];
    bool ditandai[MAKS][MAKS];

    int    jumlahBaris;
    int    jumlahKolom;
    int    totalBom;
    int    jumlahTanda;
    time_t waktuMulai;
    bool   mati;
    bool   menang;

    void cetakRapi(int nilai, int lebar) {
        int digit = 1, sementara = nilai;
        while (sementara >= 10) { digit++; sementara /= 10; }
        for (int i = digit; i < lebar; i++) cout << ' ';
        cout << nilai;
    }

    void bersihkanPapan() {
        for (int i = 0; i < MAKS; i++)
            for (int j = 0; j < MAKS; j++) {
                papan[i][j]    = 0;
                terbuka[i][j]  = false;
                ditandai[i][j] = false;
            }
    }

    void tanamBom() {
        int tertanam = 0;
        while (tertanam < totalBom) {
            int b = rand() % jumlahBaris;
            int k = rand() % jumlahKolom;
            if (papan[b][k] != -1) {
                papan[b][k] = -1;
                tertanam++;
            }
        }
    }

    void hitungAngka() {
        for (int b = 0; b < jumlahBaris; b++)
            for (int k = 0; k < jumlahKolom; k++) {
                if (papan[b][k] == -1) continue;
                int jumlah = 0;
                for (int db = -1; db <= 1; db++)
                    for (int dk = -1; dk <= 1; dk++) {
                        int nb = b + db, nk = k + dk;
                        if (nb >= 0 && nb < jumlahBaris && nk >= 0 && nk < jumlahKolom && papan[nb][nk] == -1)
                            jumlah++;
                    }
                papan[b][k] = jumlah;
            }
    }

    void bukaSekitar(int b, int k) {
        if (b < 0 || b >= jumlahBaris || k < 0 || k >= jumlahKolom) return;
        if (terbuka[b][k] || ditandai[b][k])                         return;
        if (papan[b][k] == -1)                                       return;
        terbuka[b][k] = true;
        if (papan[b][k] == 0)
            for (int db = -1; db <= 1; db++)
                for (int dk = -1; dk <= 1; dk++)
                    if (db != 0 || dk != 0)
                        bukaSekitar(b + db, k + dk);
    }

    bool cekMenang() {
        for (int b = 0; b < jumlahBaris; b++)
            for (int k = 0; k < jumlahKolom; k++) {
                if (papan[b][k] == -1 && !ditandai[b][k]) return false;
                if (papan[b][k] != -1 &&  ditandai[b][k]) return false;
            }
        return true;
    }

    void tampilkanPapan(bool tampilSemuaBom = false) {
        int detik = (int)difftime(time(0), waktuMulai);

        cout << "\n";
        cout << "  +==============================+\n";
        cout << "  |        MINESWEEPER++         |\n";
        cout << "  +==============================+\n";
        cout << "  |  Papan       : " << jumlahBaris << " x " << jumlahKolom << "           |\n";
        cout << "  |  Bom tersisa : ";
        cetakRapi(totalBom - jumlahTanda, 2);
        cout << "             |\n";
        cout << "  |  Waktu       : ";
        cetakRapi(detik, 4);
        cout << " detik       |\n";
        cout << "  +==============================+\n\n";

        cout << "      ";
        for (int k = 0; k < jumlahKolom; k++) {
            cout << ' ';
            cetakRapi(k + 1, 2);
        }
        cout << "\n";

        cout << "     +";
        for (int k = 0; k < jumlahKolom; k++) cout << "---";
        cout << "+\n";

        for (int b = 0; b < jumlahBaris; b++) {
            cetakRapi(b + 1, 4);
            cout << " |";
            for (int k = 0; k < jumlahKolom; k++) {
                char karakter;
                if (tampilSemuaBom && papan[b][k] == -1)
                    karakter = ditandai[b][k] ? 'F' : '*';
                else if (terbuka[b][k])
                    karakter = (papan[b][k] == 0) ? '.' : ('0' + papan[b][k]);
                else if (ditandai[b][k])
                    karakter = 'F';
                else
                    karakter = '#';
                cout << ' ' << karakter << ' ';
            }
            cout << "|\n";
        }

        cout << "     +";
        for (int k = 0; k < jumlahKolom; k++) cout << "---";
        cout << "+\n";

        cout << "\n  Legenda:  # = tutup   F = ditandai   . = kosong\n";
        cout << "            1-8 = angka tetangga   * = BOM\n";
    }

    int bacaAngka(int minimum, int maksimum) {
        int nilai;
        while (true) {
            cin >> nilai;
            if (nilai >= minimum && nilai <= maksimum) return nilai;
            cin.clear();
            cin.get();
            cout << "  [!] Masukkan angka " << minimum << " - " << maksimum << ": ";
        }
    }

public:
    Minesweeper() {
        bersihkanPapan();
        jumlahBaris = 0; jumlahKolom = 0;
        totalBom = 0; jumlahTanda = 0;
        waktuMulai = 0; mati = false; menang = false;
    }

    void permainanBaru() {
        system("CLS");
        cout << "\n  ============================================\n";
        cout << "           PENGATURAN PERMAINAN BARU\n";
        cout << "  ============================================\n";

        cout << "  Jumlah baris (4 - 10) : ";
        jumlahBaris = bacaAngka(4, 10);

        cout << "  Jumlah kolom (4 - 10) : ";
        jumlahKolom = bacaAngka(4, 10);

        int maksBom = jumlahBaris * jumlahKolom - 1;
        cout << "  Jumlah bom  (1 - " << maksBom << ")  : ";
        totalBom = bacaAngka(1, maksBom);

        jumlahTanda = 0; mati = false; menang = false;
        bersihkanPapan();
        tanamBom();
        hitungAngka();
        waktuMulai = time(0);

        cout << "\n  Papan " << jumlahBaris << "x" << jumlahKolom
             << " siap! " << totalBom << " bom tersembunyi.\n";
        cout << "  Tandai semua bom dengan tepat untuk menang!\n";
    }

    void mulaiMain() {
        while (!mati && !menang) {
            system("CLS");
            tampilkanPapan();

            cout << "\n  Pilih aksi:\n";
            cout << "    [1] Buka kotak\n";
            cout << "    [2] Tandai / Hapus tanda bom\n";
            cout << "  Pilihan: ";

            int pilihan;
            cin >> pilihan;

            if (pilihan != 1 && pilihan != 2) {
                cin.clear();
                cin.get();
                cout << "  [!] Pilihan tidak valid!\n";
                continue;
            }

            cout << "  Baris (1 - " << jumlahBaris << ") : ";
            int baris = bacaAngka(1, jumlahBaris) - 1;
            cout << "  Kolom (1 - " << jumlahKolom << ") : ";
            int kolom = bacaAngka(1, jumlahKolom) - 1;

            if (pilihan == 1) {
                if (terbuka[baris][kolom]) {
                    cout << "  [!] Kotak (" << (baris+1) << "," << (kolom+1) << ") sudah terbuka!\n";
                    continue;
                }
                if (ditandai[baris][kolom]) {
                    cout << "  [!] Hapus tanda dulu sebelum membuka!\n";
                    continue;
                }
                if (papan[baris][kolom] == -1)
                    mati = true;
                else
                    bukaSekitar(baris, kolom);
            } else {
                if (terbuka[baris][kolom]) {
                    cout << "  [!] Kotak terbuka tidak bisa ditandai!\n";
                    continue;
                }
                if (ditandai[baris][kolom]) {
                    ditandai[baris][kolom] = false;
                    jumlahTanda--;
                    cout << "  >> Tanda dihapus dari (" << (baris+1) << "," << (kolom+1) << ").\n";
                } else {
                    ditandai[baris][kolom] = true;
                    jumlahTanda++;
                    cout << "  >> Tanda dipasang di (" << (baris+1) << "," << (kolom+1) << ").\n";
                }
            }

            if (!mati) menang = cekMenang();
        }

        int detik = (int)difftime(time(0), waktuMulai);
        system("CLS");
        tampilkanPapan(true);

        cout << "\n";
        if (mati) {
            cout << "  +====================================+\n";
            cout << "  |   BOOM! Kamu menginjak bom!        |\n";
            cout << "  |           GAME OVER!               |\n";
            cout << "  +====================================+\n";
        } else {
            cout << "  +====================================+\n";
            cout << "  |  SELAMAT! Semua bom ditemukan!     |\n";
            cout << "  |        KAMU MENANG!                |\n";
            cout << "  +====================================+\n";
        }
        cout << "  Waktu bermain: " << detik << " detik\n\n";
    }
};

int main() {
    srand((unsigned)time(0));

    system("CLS");
    cout << "\n";
    cout << "  ==========================================\n";
    cout << "       SELAMAT DATANG DI MINESWEEPER++\n";
    cout << "   Temukan semua bom tanpa meledakkan satu!\n";
    cout << "  ==========================================\n";

    Minesweeper game;

    while (true) {
        cout << "\n  ==========================================\n";
        cout << "                 MENU UTAMA\n";
        cout << "  ==========================================\n";
        cout << "    [1] Mulai Permainan Baru\n";
        cout << "    [2] Keluar\n";
        cout << "  ==========================================\n";
        cout << "  Pilihan: ";

        int pilihan;
        cin >> pilihan;

        if (pilihan == 1) {
            game.permainanBaru();
            game.mulaiMain();
        } else if (pilihan == 2) {
            cout << "\n  Terima kasih sudah bermain Minesweeper++!\n\n";
            break;
        } else {
            cin.clear();
            cin.get();
            cout << "  [!] Pilihan tidak valid!\n";
        }
    }

    return 0;
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Mobil {
    string plat;
    string merk;
    string warna;
    int jamMasuk;
    int menitMasuk;
};

class ParkingSystem {
private:
    vector<Mobil> daftarMobil;
    string namaPetugas;
    string idPetugas;

    static const int MAX_KAPASITAS = 20;
    int tarifPerMenit = 150;

    string formatTwoDigits(int number) {
        if (number < 10) return "0" + to_string(number);
        return to_string(number);
    }

public:

    void showHeader() {
        cout << string(80, '=') << "\n";
        cout << "Nama Petugas : " << namaPetugas << "\n";
        cout << "ID Petugas   : " << idPetugas << "\n\n";
        cout << string(24, ' ') << "TERIMA KASIH ATAS KERJASAMANYA !\n";
        cout << string(24, '-') << " S E L A M A T   B E R T U G A S " << string(24, '-') << "\n";
        cout << string(80, '=') << "\n\n";
    }

    void tambahKendaraan() {
        if (daftarMobil.size() >= MAX_KAPASITAS) {
            cout << "\nPARKIRAN SUDAH PENUH (20/20 MOBIL)!\n\n";
            return;
        }

        int jumlah;
        cout << "Masukkan jumlah mobil yang akan di parkirkan : ";
        cin >> jumlah;
        cin.ignore();

        int sisaKapasitas = MAX_KAPASITAS - daftarMobil.size();

        if (jumlah > sisaKapasitas) {
            cout << "\nMaksimum Kapasitas hanya 20"
                 << sisaKapasitas
                 << " mobil.\n\n";
            return;
        }

        for (int i = 0; i < jumlah; i++) {
            Mobil m;

            cout << "Mobil ke " << (i + 1) << "\n";

            cout << "Masukkan plat mobil : ";
            getline(cin, m.plat);

            cout << "Masukkan merk mobil : ";
            getline(cin, m.merk);

            cout << "Masukkan warna mobil : ";
            getline(cin, m.warna);

            cout << "Masukkan jam masuk (0-23) : ";
            cin >> m.jamMasuk;

            cout << "Masukkan menit masuk (0-59) : ";
            cin >> m.menitMasuk;
            cin.ignore();

            cout << "\n";

            daftarMobil.push_back(m);
        }

        cout << "Jumlah mobil terparkir : "
             << daftarMobil.size()
             << "/" << MAX_KAPASITAS << "\n\n";
    }

    void tampilkanKendaraan() {
        cout << "DAFTAR MOBIL YANG SUDAH TERPARKIR :\n";

        if (daftarMobil.empty()) {
            cout << string(80, '=') << "\n";
            cout << "Tidak ada mobil yang terparkir.\n";
            cout << string(80, '=') << "\n\n";
            return;
        }

        for (size_t i = 0; i < daftarMobil.size(); i++) {
            cout << string(80, '=') << "\n";
            cout << "Mobil ke-" << (i + 1) << "\n";
            cout << "Plat mobil  : " << daftarMobil[i].plat << "\n";
            cout << "Merk mobil  : " << daftarMobil[i].merk << "\n";
            cout << "Warna mobil : " << daftarMobil[i].warna << "\n";
            cout << "Waktu masuk : "
                 << formatTwoDigits(daftarMobil[i].jamMasuk)
                 << ":"
                 << formatTwoDigits(daftarMobil[i].menitMasuk)
                 << "\n";
        }

        cout << string(80, '=') << "\n";
    }

    void pembayaran() {
        if (daftarMobil.empty()) {
            cout << "Tidak ada mobil di area parkir untuk dibayar.\n\n";
            return;
        }

        tampilkanKendaraan();

        while (true) {
            string platBayar;

            cout << "Masukkan plat mobil yang ingin dibayar : ";
            getline(cin, platBayar);

            int index = -1;

            for (size_t i = 0; i < daftarMobil.size(); i++) {
                if (daftarMobil[i].plat == platBayar) {
                    index = i;
                    break;
                }
            }

            if (index != -1) {
                int jamKeluar, menitKeluar;

                cout << "Masukkan jam keluar (0-23) : ";
                cin >> jamKeluar;

                cout << "Masukkan menit keluar (0-59) : ";
                cin >> menitKeluar;
                cin.ignore();

                int menitMasukTotal =
                    daftarMobil[index].jamMasuk * 60 +
                    daftarMobil[index].menitMasuk;

                int menitKeluarTotal =
                    jamKeluar * 60 +
                    menitKeluar;

                if (menitKeluarTotal < menitMasukTotal) {
                    menitKeluarTotal += 24 * 60;
                }

                int selisihMenit =
                    menitKeluarTotal - menitMasukTotal;

                int lamaJam = selisihMenit / 60;
                int lamaMenit = selisihMenit % 60;

                int biaya = selisihMenit * tarifPerMenit;

                cout << "\nDurasi Parkir : "
                     << lamaJam << " jam "
                     << lamaMenit << " menit\n";

                cout << "B I A Y A  P A R K I R : Rp"
                     << biaya << "\n";

                cout << string(80, '=') << "\n\n";

                daftarMobil.erase(daftarMobil.begin() + index);
                break;
            }
            else {
                cout << "PLAT TIDAK DITEMUKAN !\n\n";
            }
        }
    }

    void run() {
        showHeader();

        while (true) {
            cout << "Silahkan input opsi berikut dalam bentuk angka.\n";
            cout << "1. Tambahkan Daftar Kendaraan\n";
            cout << "2. Tampilkan Daftar Kendaraan\n";
            cout << "3. Pembayaran\n";
            cout << "4. Keluar Program\n";
            cout << "Masukkan opsi : ";

            int opsi;

            if (!(cin >> opsi))
                break;

            cin.ignore();

            if (opsi == 1) {
                tambahKendaraan();
            }
            else if (opsi == 2) {
                tampilkanKendaraan();
            }
            else if (opsi == 3) {
                pembayaran();
            }
            else if (opsi == 4) {
                cout << "Terima kasih. Program selesai.\n";
                break;
            }
            else {
                cout << "Opsi tidak valid!\n\n";
            }
        }
    }
    ParkingSystem(string nama, string id) {
        namaPetugas = nama;
        idPetugas = id;
    }
};

int main() {
    cout << string(80, '=') << "\n";
    cout << string(25, '-') << " S E L A M A T   D A T A N G " << string(25, '-') << "\n";
    cout << string(25, ' ') << "DI PORTAL PARKIR KHUSUS MOBIL\n";
    cout << string(34, ' ') << "MALL PRIENAL\n";
    cout << string(80, '=') << "\n\n";

    cout << "Kami senang Anda telah hadir.\n";
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini.\n\n";

    string nama, id;

    cout << "Masukkan nama : ";
    getline(cin, nama);

    cout << "Masukkan ID   : ";
    getline(cin, id);

    cout << "\n";
    ParkingSystem system(nama, id);
    system.run();
    return 0;
}

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Barang {
    string kodeBarang;
    string namaBarang;
    double harga;
    int stok;
};

void tambahBarang(vector<Barang>& inventaris) {
    Barang barang;

    cout << "\n=== Tambah Barang ===\n";

    cout << "Kode Barang : ";
    cin >> barang.kodeBarang;

    cin.ignore();

    cout << "Nama Barang : ";
    getline(cin, barang.namaBarang);

    do {
        cout << "Harga Barang : ";
        cin >> barang.harga;

        if (barang.harga < 0) {
            cout << "Error! Harga tidak boleh negatif.\n";
        }
    } while (barang.harga < 0);

    do {
        cout << "Stok Barang : ";
        cin >> barang.stok;

        if (barang.stok < 0) {
            cout << "Error! Stok tidak boleh negatif.\n";
        }
    } while (barang.stok < 0);

    inventaris.push_back(barang);

    cout << "Barang berhasil ditambahkan!\n";
}

void tampilkanBarang(const vector<Barang>& inventaris) {
    cout << "\n=== Daftar Barang ===\n";

    if (inventaris.empty()) {
        cout << "Inventaris kosong.\n";
        return;
    }

    cout << "--------------------------------------------------\n";
    cout << "Kode\tNama\t\tHarga\t\tStok\n";
    cout << "--------------------------------------------------\n";

    for (int i = 0; i < inventaris.size(); i++) {
        cout << inventaris[i].kodeBarang << "\t"
             << inventaris[i].namaBarang << "\t\t"
             << inventaris[i].harga << "\t\t"
             << inventaris[i].stok << endl;
    }
}

void cariBarangTermahal(const vector<Barang>& inventaris) {
    cout << "\n=== Barang Termahal ===\n";

    if (inventaris.empty()) {
        cout << "Inventaris kosong.\n";
        return;
    }

    int indeksTermahal = 0;

    for (int i = 1; i < inventaris.size(); i++) {
        if (inventaris[i].harga > inventaris[indeksTermahal].harga) {
            indeksTermahal = i;
        }
    }

    cout << "Kode Barang : "
         << inventaris[indeksTermahal].kodeBarang << endl;
    cout << "Nama Barang : "
         << inventaris[indeksTermahal].namaBarang << endl;
    cout << "Harga       : "
         << inventaris[indeksTermahal].harga << endl;
    cout << "Stok        : "
         << inventaris[indeksTermahal].stok << endl;
}

void hitungTotalInventaris(const vector<Barang>& inventaris) {
    double total = 0;

    for (int i = 0; i < inventaris.size(); i++) {
        total += inventaris[i].harga * inventaris[i].stok;
    }

    cout << "\n=== Total Nilai Inventaris ===\n";
    cout << "Total nilai inventaris = Rp " << total << endl;
}

void cekRestock(const vector<Barang>& inventaris) {
    cout << "\n=== Barang Perlu Restock (Stok < 5) ===\n";

    bool ditemukan = false;

    for (int i = 0; i < inventaris.size(); i++) {
        if (inventaris[i].stok < 5) {
            ditemukan = true;

            cout << "Kode : " << inventaris[i].kodeBarang
                 << " | Nama : " << inventaris[i].namaBarang
                 << " | Stok : " << inventaris[i].stok
                 << endl;
        }
    }

    if (!ditemukan) {
        cout << "Tidak ada barang yang perlu direstock.\n";
    }
}

void updateStok(vector<Barang>& inventaris) {
    cout << "\n=== Update Stok ===\n";

    if (inventaris.empty()) {
        cout << "Inventaris kosong.\n";
        return;
    }

    string kode;
    cout << "Masukkan kode barang: ";
    cin >> kode;

    bool ditemukan = false;

    for (int i = 0; i < inventaris.size(); i++) {
        if (inventaris[i].kodeBarang == kode) {
            ditemukan = true;

            int perubahan;

            cout << "Stok saat ini: "
                 << inventaris[i].stok << endl;

            cout << "Masukkan perubahan stok (+/-): ";
            cin >> perubahan;

            int* ptrStok = &inventaris[i].stok;

            if ((*ptrStok + perubahan) < 0) {
                cout << "Error! Stok tidak boleh negatif.\n";
                return;
            }

            *ptrStok += perubahan;

            cout << "Stok berhasil diperbarui.\n";
            cout << "Stok sekarang: " << *ptrStok << endl;

            break;
        }
    }

    if (!ditemukan) {
        cout << "Barang tidak ditemukan.\n";
    }
}

int main() {
    vector<Barang> inventaris;

    int pilihan;

    do {
        cout << "\n===================================\n";
        cout << " SISTEM MANAJEMEN INVENTARIS TOKO\n";
        cout << "===================================\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Semua Barang\n";
        cout << "3. Cari Barang Termahal\n";
        cout << "4. Hitung Total Nilai Inventaris\n";
        cout << "5. Cek Restock (Stok < 5)\n";
        cout << "6. Update Stok\n";
        cout << "7. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahBarang(inventaris);
                break;

            case 2:
                tampilkanBarang(inventaris);
                break;

            case 3:
                cariBarangTermahal(inventaris);
                break;

            case 4:
                hitungTotalInventaris(inventaris);
                break;

            case 5:
                cekRestock(inventaris);
                break;

            case 6:
                updateStok(inventaris);
                break;

            case 7:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 7);

    return 0;
}
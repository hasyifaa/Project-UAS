#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

struct dataKendaraan {
    string platNomor;
    string merk;
    string warna;
    int waktuMasuk;
    bool terisi;
};
void inisialisasiData (dataKendaraan dataMotor[], int n) {
    for (int i=0; i<n; i++) {
        dataMotor[i].platNomor= "-";
        dataMotor[i].merk= "-";
        dataMotor[i].warna= "-";
        dataMotor[i].waktuMasuk= 0;
        dataMotor[i].terisi= false;
    }
}
int hitungSlot (dataKendaraan dataMotor[], int n) {
    int jumlah = 0;
    for (int i=0; i<n; i++) {
        if (dataMotor[i].terisi) {
            jumlah++;
        }
    }
    return jumlah;
}
int cariIndex(dataKendaraan dataMotor[], int n, string plat) {
    for (int i = 0; i < n; i++) {
        if (dataMotor[i].terisi == true && dataMotor[i].platNomor == plat) {
            return i;
        }
    }

    return -1;
}
void kendaraanMasuk(dataKendaraan dataMotor[], int n) {
    int slotKosong = -1;
    string plat;

    cout << "\n===== PENCATATAN KENDARAAN MASUK =====\n";

    for (int i = 0; i < n; i++) {
        if (dataMotor[i].terisi == false) {
            slotKosong = i;
            break;
        }
    }

    if (slotKosong == -1) {
        cout << "Parkiran sudah penuh!\n";
        return;
    }

    cout << "Masukkan nomor plat : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, plat);

    if (cariIndex(dataMotor, n, plat) != -1) {
        cout << "Nomor plat sudah terdaftar!\n";
        return;
    }

    dataMotor[slotKosong].platNomor = plat;

    cout << "Masukkan merk motor : ";
    cin >> dataMotor[slotKosong].merk;

    cout << "Masukkan warna motor : ";
    cin >> dataMotor[slotKosong].warna;

    cout << "Masukkan waktu masuk (contoh: 830) : ";
    cin >> dataMotor[slotKosong].waktuMasuk;

    dataMotor[slotKosong].terisi = true;

    cout << "\nKendaraan berhasil dicatat!\n";
    cout << "Nomor slot parkir : " << slotKosong + 1 << endl;
}
void cariKendaraan(dataKendaraan dataMotor[], int n) {
    string plat;

    cout << "\n===== PENCARIAN KENDARAAN =====\n";
    cout << "Masukkan nomor plat : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, plat);

    int index = cariIndex(dataMotor, n, plat);

    if (index != -1) {
        cout << "\nKendaraan ditemukan!\n";
        cout << "Nomor plat : " << dataMotor[index].platNomor << endl;
        cout << "Merk motor : " << dataMotor[index].merk << endl;
        cout << "Warna motor : " << dataMotor[index].warna << endl;
        cout << "Waktu masuk : " << dataMotor[index].waktuMasuk << endl;
        cout << "Nomor slot : " << index + 1 << endl;
    } else {
        cout << "\nKendaraan tidak ditemukan!\n";
    }
}
void tampilkanKapasitas(dataKendaraan dataMotor[], int n) {
    int terisi = hitungSlot(dataMotor, n);
    int tersedia = n - terisi;

    for (int i = 0; i < n; i++) {
        cout << "slot" << i + 1 << " : ";

        if (dataMotor[i].terisi) {
            cout << "terisi " << dataMotor[i].platNomor << " -- " << dataMotor[i].merk << endl;
        } else {
            cout << "kosong" << endl;
        }
    }
    cout << left << setw(20) << "KAPASITAS PARKIR" << " : " << n << endl;
    cout << left << setw(20) << "KAPASITAS TERSEDIA" << " : " << tersedia << endl;
    cout << left << setw(20) << "SLOT TERISI" << " : " << terisi << endl;
}
int main () {
    const int kapasitasParkir = 400;
    dataKendaraan dataMotor[kapasitasParkir] = {};
    
    int pilihan;

    do {
        cout << "\n===== SISTEM MANAJEMEN PARKIR =====\n";
        cout << "1. Kendaraan Masuk\n";
        cout << "2. Cari Kendaraan\n";
        cout << "3. Lihat Kapasitas Parkir\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                kendaraanMasuk(dataMotor, kapasitasParkir);
                break;
            case 2:
                cariKendaraan(dataMotor, kapasitasParkir);
                break;
            case 3:
                tampilkanKapasitas(dataMotor, kapasitasParkir);
                break;
            case 0:
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan !=0);
    
    return 0;
}
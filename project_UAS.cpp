#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cctype>
using namespace std;

struct dataKendaraan {
    string platNomor;
    string merk;
    string warna;
    string hariMasuk;
    string hariKeluar;
    int waktuMasuk;
    int waktuKeluar;
    bool terisi;
};
void inisialisasiData (dataKendaraan dataMotor[], int n) {
    for (int i = 0; i < n; i++) {
        dataMotor[i].platNomor = "-";
        dataMotor[i].merk = "-";
        dataMotor[i].warna = "-";
        dataMotor[i].hariMasuk = "-";
        dataMotor[i].hariKeluar = "-";
        dataMotor[i].waktuMasuk = 0;
        dataMotor[i].waktuKeluar = 0;
        dataMotor[i].terisi = false;
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
int indeksHari(string hari) {
    for (int i = 0; i < hari.length(); i++) {
        hari[i] = tolower(hari[i]);
    }
    if (hari == "senin") return 0;
    else if (hari == "selasa") return 1;
    else if (hari == "rabu") return 2;
    else if (hari == "kamis") return 3;
    else if (hari == "jumat") return 4;
    else if (hari == "sabtu") return 5;
    else if (hari == "minggu") return 6;

    return -1;
}
string bacaHari() {
    string hari;

    while (true) {
        cin >> hari;

        if (indeksHari(hari) == -1) {
            cout << "Nama hari tidak valid. Masukkan kembali : ";
        } else {
            return hari;
        }
    }
}
int bacaWaktu() {
    int jam, menit;
    char pemisah;

    while (true) {
        cin >> jam >> pemisah >> menit;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Format salah. Contoh 9.35 atau 10.30 : ";
        } else if ((pemisah != '.' && pemisah != ':') ||
                    jam < 0 || jam > 23 || menit < 0 || menit > 59) {
            cin. ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Waktu tidak valid. Contoh 9.35 atau 10.30 : ";
        } else {
            return jam * 60 + menit;
        }
    }
}
void tampilWaktu(int totalMenit) {
    cout << setfill('0') << setw(2) << totalMenit / 60
         << ":" << setw(2) << totalMenit % 60
         << setfill(' ');
}
void kendaraanMasuk(dataKendaraan dataMotor[], int n, int &totalMasuk) {
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

    cout << "Masukkan hari masuk : ";
    dataMotor[slotKosong].hariMasuk = bacaHari();

    cout << "Masukkan waktu masuk (contoh = 9.35) : ";
    dataMotor[slotKosong].waktuMasuk = bacaWaktu();

    dataMotor[slotKosong].terisi = true;
    totalMasuk++;

    cout << "\nKendaraan berhasil dicatat!\n";
    cout << "Nomor slot parkir : " << slotKosong + 1 << endl;
}
void kendaraanKeluar(dataKendaraan dataMotor[], int n, int &totalKeluar) {
    string plat;
    string hariKeluar;
    int waktuKeluar;
    int durasiMenit;

    cout << "\n===== PENCATATAN KENDARAAN KELUAR =====\n";
    cout << "Masukkan nomor plat : ";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, plat);

    int index = cariIndex(dataMotor, n, plat);

    if (index != -1) {
        cout << "Kendaraan ditemukan!\n";
        cout << "Nomor plat : " << dataMotor[index].platNomor << endl;
        cout << "Nomor slot : " << index + 1 << endl;

        cout << "Hari masuk : " << dataMotor[index].hariMasuk << endl;
        cout << "Waktu masuk : ";
        tampilWaktu(dataMotor[index].waktuMasuk);
        cout << endl;

        cout << "Masukkan hari keluar : ";
        hariKeluar = bacaHari();

        cout << "Masukkan waktu keluar (contoh = 9.35) : ";
        waktuKeluar = bacaWaktu();

        int selisihHari = (indeksHari(hariKeluar) - indeksHari(dataMotor[index].hariMasuk) + 7) % 7;

        durasiMenit = (selisihHari * 1440) + (waktuKeluar - dataMotor[index].waktuMasuk);

        if (durasiMenit < 0) {
            cout << "\nHari atau waktu keluar tidak valid!\n";
            cout << "Kendaraan tetap tercatat di parkiran.\n";
            return;
        }

        dataMotor[index].hariKeluar = hariKeluar;
        dataMotor[index].waktuKeluar = waktuKeluar;

        int durasiHari = durasiMenit / 1440;
        int sisaMenit = durasiMenit % 1440;
        int durasiJam = sisaMenit / 60;
        int menit = sisaMenit % 60;

        dataMotor[index].terisi = false;
        totalKeluar++;

        cout << "\nKendaraan berhasil keluar!\n";
        cout << "Hari keluar : " << hariKeluar << endl;
        cout << "Waktu keluar : ";
        tampilWaktu(waktuKeluar);
        cout << endl;

        cout << "Durasi parkir : "
             << durasiHari << " hari "
             << durasiJam << " jam "
             << menit << " menit " << endl;

    } else {
        cout << "\nKendaraan tidak ditemukan!\n";
    }
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
        cout << "Waktu masuk : "; 
        tampilWaktu(dataMotor[index].waktuMasuk); 
        cout << endl;
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
void statistikParkir(dataKendaraan dataMotor[], int n, int totalMasuk, int totalKeluar) {
    int sedangParkir = hitungSlot(dataMotor, n);
    int slotKosong = n - sedangParkir;

    cout << "\n===== STATISTIK PARKIR =====\n";
    cout << left << setw(30) << "TOTAL KENDARAAN MASUK" << " : " << totalMasuk << endl;
    cout << left << setw(30) << "TOTAL KENDARAAN KELUAR" << " : " << totalKeluar << endl;
    cout << left << setw(30) << "KENDARAAN SEDANG PARKIR" << " : " << sedangParkir << endl;
    cout << left << setw(30) << "SLOT PARKIR KOSONG" << " : " << slotKosong << endl;
    cout << left << setw(30) << "KAPASITAS PARKIR" << " : " << n << endl;
}
int main () {
    const int kapasitasParkir = 400;
    dataKendaraan dataMotor[kapasitasParkir] = {};

    inisialisasiData(dataMotor, kapasitasParkir);

    int totalMasuk = 0;
    int totalKeluar = 0;
    
    int pilihan;

    do {
        cout << "\n===== SISTEM MANAJEMEN PARKIR =====\n";
        cout << "1. Kendaraan Masuk\n";
        cout << "2. Cari Kendaraan\n";
        cout << "3. Lihat Kapasitas Parkir\n";
        cout << "4. Kendaraan Keluar\n";
        cout << "5. Statistik Parkir\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                kendaraanMasuk(dataMotor, kapasitasParkir, totalMasuk);
                break;
            case 2:
                cariKendaraan(dataMotor, kapasitasParkir);
                break;
            case 3:
                tampilkanKapasitas(dataMotor, kapasitasParkir);
                break;
            case 4:
                kendaraanKeluar(dataMotor, kapasitasParkir, totalKeluar);
                break;
            case 5:
                statistikParkir(dataMotor, kapasitasParkir, totalMasuk, totalKeluar);
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
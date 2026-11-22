#include <iostream>
#include <iomanip>
#include <string>
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
int main () {
    const int kapasitasParkir = 400;
    dataKendaraan dataMotor[kapasitasParkir] = {};
    
    inisialisasiData(dataMotor, kapasitasParkir);

    int terisi = hitungSlot(dataMotor, kapasitasParkir);
    int tersedia = kapasitasParkir - terisi;
    for (int i=0; i<kapasitasParkir; i++) {
        cout << "slot " << i+1 << " : ";
        if (dataMotor[i].terisi) {
            cout << "terisi " << dataMotor[i].platNomor << " -- " << dataMotor[i].merk << endl;
        }
        else {
            cout << "kosong" << endl;
        }
    }

    cout << left << setw(20) << "KAPASITAS PARKIR" << " : " << kapasitasParkir << endl;
    cout << left << setw(20) << "KAPASITAS TERSEDIA" << " : " << tersedia <<  endl;
    cout << left << setw(20) << "SLOT TERISI" << " : " << terisi << endl; 
    return 0;
}
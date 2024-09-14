#include <iostream>
#include <stdlib.h>
using namespace std;


void MenaraHanoi(int n, char asal, char bantu, char tujuan){
    if (n == 1){ // Kondisi saat piringan 1 dapat dipindah
        cout <<"Pindahkan Piringan 1 Dari Tiang " << asal << " ke " << tujuan << endl; 
        return;
    }
    // Metode Rekursif untuk mengvisalkan cara menara hanoi bekerja 
    MenaraHanoi(n-1, asal, tujuan, bantu); // Parameter diubah agar bisa menyesuaikan dengan penyelesaian menara hanoi
    cout << "Pindahkan Piringan " << n << " Dari Tiang " << asal << " ke " << tujuan << endl; 
    MenaraHanoi(n-1, bantu, asal, tujuan);
}   

int main(){
    // Inisialisasi Variabel
    int n;
    char answer;
        // Perulangan Hanya Untuk Gimmick
        do{
            system("cls");
            cout << "======================" << endl;
            cout << "REKURSIF MENARA HANOI" << endl;
            cout << "======================" << endl << endl;
            cout << "Masukkan Jumlah Piringan : ";
            cin >> n;
            MenaraHanoi(n, 'A', 'B', 'C');
            cout << endl << "APAKAH INGIN MENGULANG PROGRAM (Y/N) : ";
            cin >> answer;
        } while(answer == 'y' || answer == 'Y' );
    return 0;
}
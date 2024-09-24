#include <iostream>
#include <cstdlib>
#include <limits>
using namespace std;

struct detailNovel {
    string penerbit;
    string tahunTerbit;
};
struct novel {
    string judul;
    string genre;
    detailNovel detail;
};

struct user {
    string namaUser;
    string pwUser;
};

struct admin {
    string namaAdmin;
    string pwAdmin;
};

void setTextColor(int color){
    cout << "\033[1;" << color << "m";
}

void pause(){
    cout << "";
    cout << "...";
    cin.get();
}

void clear(){
    system("cls");
}

int menuLogin(user login, admin log){
    string username, password;
    cout << "MASUKKAN USERNAME: ";
    getline(cin, username);
    cout << "MASUKKAN PASSWORD: ";
    getline(cin, password);
    if (username == log.namaAdmin && password == log.pwAdmin){
        clear();
        setTextColor(32);
        cout << "LOGIN ADMIN BERHASIL\n\n";
        setTextColor(0);
        return 0;
    } else if (username == login.namaUser && password == login.pwUser){
        clear();
        setTextColor(32);
        cout << "LOGIN USER BERHASIL\n\n";
        setTextColor(0);
        return 1;
    } else {
        setTextColor(31);
        cout << "\nUSERNAME SALAH, MOHON COBA LAGI\n";
        setTextColor(0);
        return -1;
    };
};

int menuAdmin(){
    int choice;
    while (true) {
        setTextColor(33);
        cout << "====================\n";
        cout << "    MENU ADMIN    \n";
        cout << "====================\n\n";
        setTextColor(0);
        cout << "[1] MENAMBAH NOVEL\n";
        cout << "[2] MELIHAT DAFTAR NOVEL\n";
        cout << "[3] MENGEDIT NOVEL\n";
        cout << "[4] MENGHAPUS NOVEL\n";
        cout << "[5] EXIT PROGRAM\n\n";
        cout << "PILIH MENU NOMOR: ";
        cin >> choice;
        cin.ignore();
        if(cin.fail() || choice < 1 || choice > 5){
            clear();
            setTextColor(31);
            cout << "PILIHAN TIDAK VALID\n";
            setTextColor(0);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return choice;
        }
    }
}

//diberikan pointer pada jumlahnovelditambahkan agar variable lokal ini bisa mengambil nilai dari variable yang diinginkan
void menuSatu(novel dataNovel[],int *jumlahNovelDitambahkan){
    string newNovel,newGenre,newTerbit,newPenerbit;
    cout << "MASUKKAN NAMA NOVEL BARU : ";
    getline(cin, newNovel);
    cout << "MASUKKAN GENRE NOVEL BARU : ";
    getline(cin, newGenre);
    cout << "TAHUN TERBIT : ";
    getline(cin, newTerbit);
    cout << "NAMA PENERBIT : ";
    getline(cin, newPenerbit);
    //menambahkan novel ke index baru 
    dataNovel[*jumlahNovelDitambahkan].judul = newNovel;
    dataNovel[*jumlahNovelDitambahkan].genre = newGenre;
    dataNovel[*jumlahNovelDitambahkan].detail.tahunTerbit = newTerbit;
    dataNovel[*jumlahNovelDitambahkan].detail.penerbit = newPenerbit;
    *jumlahNovelDitambahkan+= 1;
    setTextColor(32);
    clear();
    cout << "NOVEL BERHASIL DITAMBAHKAN\n\n";
    setTextColor(0);
}
void menuDua(novel dataNovel[],int *jumlahNovelDitambahkan){
    cout << "====================\n";
    cout << "     DAFTAR NOVEL    \n";
    cout << "====================\n\n";
    for (int i=0;i<*jumlahNovelDitambahkan;i++){ //menampilkan data novel
        cout << i+1 <<". " << "JUDUL : " << dataNovel[i].judul << endl 
        << "GENRE : " << dataNovel[i].genre << endl 
        << "TAHUN TERBIT : " << dataNovel[i].detail.tahunTerbit << endl 
        << "NAMA PENERBIT : " << dataNovel[i].detail.penerbit << endl << endl;
    }
    pause();
}
void menuTiga(novel dataNovel[],int *jumlahNovelDitambahkan){
    string newNameNovel,newGenreNovel,newTahunTerbit,newNamaPenulis;
    int editNovel;
    menuDua(dataNovel,jumlahNovelDitambahkan);
            cout << "NOMOR NOVEL YANG INGIN DI EDIT : ";
            cin >> editNovel;
            if (editNovel <= (*jumlahNovelDitambahkan) && editNovel > 0){
                editNovel = editNovel - 1;
                cout << "NAMA BARU NOVEL : ";
                cin.ignore();
                getline(cin,newNameNovel);
                cout << "GENRE NOVEL : ";
                getline(cin,newGenreNovel);
                cout << "TAHUN TERBIT : ";
                getline(cin,newTahunTerbit);
                cout << "NAMA PENERBIT : ";
                getline(cin,newNamaPenulis);
                dataNovel[editNovel].judul = newNameNovel;
                dataNovel[editNovel].genre = newGenreNovel;
                dataNovel[editNovel].detail.tahunTerbit = newTahunTerbit;
                dataNovel[editNovel].detail.penerbit = newNamaPenulis;
                clear();
                setTextColor(32);
                cout << "NOVEL BERHASIL DI EDIT\n";
                setTextColor(0);
            }else{
                clear();
                setTextColor(31);
                cout << "INPUT SALAH , MOHON MASUKKAN INPUT DENGAN BENAR\n";
                setTextColor(0);
    }
}
void menuEmpat(novel dataNovel[],int *jumlahNovelDitambahkan){
    int delNovel;
    if ((*jumlahNovelDitambahkan) > 0){
        menuDua(dataNovel,jumlahNovelDitambahkan);   
        cout << "MASUKKAN NOMOR NOVEL YANG INGIN DI HAPUS : ";
        cin >> delNovel;
        cin.ignore();
        delNovel--;
        if(delNovel<(*jumlahNovelDitambahkan) && delNovel>=0){
            for(int i=delNovel;i<(*jumlahNovelDitambahkan-1);i++){
                dataNovel[i].judul = dataNovel[i+1].judul;
                dataNovel[i].genre = dataNovel[i+1].genre;
                dataNovel[i].detail.tahunTerbit = dataNovel[i+1].detail.tahunTerbit;
                dataNovel[i].detail.penerbit = dataNovel[i+1].detail.penerbit;
            }
            (*jumlahNovelDitambahkan)--;
            clear();
            setTextColor(32);
            cout << "NOVEL BERHASIL DI HAPUS\n";
            setTextColor(0);
        }else {
            clear();
            setTextColor(31);
            cout << "NOMOR NOVEL YANG KAMU INGIN HAPUS TIDAK ADA\n";
            setTextColor(0);
        }
    }else{
        clear();
        setTextColor(31);
        cout << "NOVEL SUDAH HABIS , TAMBAHKAN DULU BEBERAPA NOVEL\n";
        setTextColor(0);
    }
}

int menuUser(){
    int choice;
    while (true) {
        setTextColor(33);
        cout << "====================\n";
        cout << "     MENU USER    \n";
        cout << "====================\n\n";
        setTextColor(0);
        cout << "[1] MELIHAT DAFTAR NOVEL\n";
        cout << "[2] MEMBELI NOVEL\n";
        cout << "[3] EXIT PROGRAM\n\n";
        cout << "PILIH MENU NOMOR: ";
        cin >> choice;
        cin.ignore();
        if (cin.fail() || choice < 1 || choice > 3) {
            clear();
            setTextColor(31);
            cout << "PILIHAN TIDAK VALID\n";
            setTextColor(0);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return choice;
        }
    }
}

void menuDuaUser(novel dataNovel[],int *jumlahNovelDitambahkan){
    cout << "====================\n";
    cout << "     DAFTAR NOVEL    \n";
    cout << "====================\n\n";
    int beliNovel;
    for (int i=0;i<*jumlahNovelDitambahkan;i++){ //menampilkan data novel
        cout << i+1 <<". " << "JUDUL : " << dataNovel[i].judul << endl 
        << "GENRE : " << dataNovel[i].genre << endl 
        << "TAHUN TERBIT : " << dataNovel[i].detail.tahunTerbit << endl 
        << "NAMA PENERBIT : " << dataNovel[i].detail.penerbit << endl << endl ;
    }
    cout << "NOVEL YANG INGIN DIBELI : ";
    cin >> beliNovel;
    cin.ignore();
    setTextColor(32);
    clear();
    cout << "====================\n";
    cout << "   PEMBELIAN NOVEL\n";
    cout << "====================\n\n";
    cout << "NOVEL " << dataNovel[beliNovel-1].judul << " BERHASIL DIBELI , TERIMAKASIH BANYAK USER\n\n";
    setTextColor(0);
    pause();
}

int main(){
    user login;
    admin log;
    int jumlahNovelDitambahkan = 2;
    novel dataNovel[100];
    log.namaAdmin = "Heri";
    log.pwAdmin = "Heri";
    login.namaUser = "User";
    login.pwUser = "User";
    dataNovel[0].judul = "Malioboro at Midnight";//judul novel
    dataNovel[0].genre = "Drama"; // genre novel
    dataNovel[0].detail.tahunTerbit = "2019";
    dataNovel[0].detail.penerbit = "Bukune";
    dataNovel[1].judul = "Bumi";// judul novel
    dataNovel[1].genre = "Action";// genre novel
    dataNovel[1].detail.tahunTerbit = "2023";
    dataNovel[1].detail.penerbit = "Media Kita";    
    setTextColor(33);
    clear();
    cout << "=============================\n";
    cout << "   PROGRAM CRUD LIST NOVEL  \n";
    cout << "=============================\n\n";
    setTextColor(0);

    //kondisi untuk ke menu login
    int hasilLogin;
    while(true){ 
        hasilLogin = menuLogin(login, log); // Login user atau admin
        if (hasilLogin == -1){
            continue; // Ulangi jika login gagal
        } else if (hasilLogin == 0 ) { // Admin berhasil login
            int pilihan; 
            do {
                clear();
                pilihan = menuAdmin(); // Ambil pilihan dari menu admin
                switch(pilihan){
                    case 1:
                        clear();
                        menuSatu(dataNovel, &jumlahNovelDitambahkan); // Menambah novel
                        break;
                    case 2:
                        clear();
                        menuDua(dataNovel, &jumlahNovelDitambahkan); // Melihat daftar novel
                        break;
                    case 3:
                        clear();
                        menuTiga(dataNovel, &jumlahNovelDitambahkan); // Mengedit novel
                        break;
                    case 4:
                        clear();
                        menuEmpat(dataNovel, &jumlahNovelDitambahkan); // Menghapus novel
                        break;
                    case 5:
                        return 0; // Keluar dari program
                }
            } while(pilihan != 5); // Admin akan terus berada di menu hingga memilih keluar
        } else if (hasilLogin == 1) { // User berhasil login
            int choice;
            do {
                clear();
                choice = menuUser(); // Ambil pilihan dari menu user
                switch(choice){
                    case 1:
                        clear();
                        menuDua(dataNovel, &jumlahNovelDitambahkan); // Melihat daftar novel
                        break;
                    case 2:
                        clear();
                        menuDuaUser(dataNovel, &jumlahNovelDitambahkan); // Membeli novel
                        break;
                    case 3:
                        return 0; // Keluar dari program
                }
            } while(choice != 3); // User akan terus berada di menu hingga memilih keluar
        }
    }
}



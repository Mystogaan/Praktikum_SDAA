// Nama : Zulfikar Heriansyah
// NIM  : 2309106033
// Program CRUD List Novel
// Program ini adalah program yang memungkinkan user dan admin untuk melakukan CRUD pada list novel

// Posttest 4 : IMPLEMENTASI STACK DAN QUEUE PADA PROGRAM CRUD LIST NOVEL

//ALUR PROGRAM
// 1.LOGIN SEBAGAI USER LALU PESAN NOVEL (QUEUE)
// 2.LIHAT NOVEL JUGA DETAILNYA (STACK)
// 4.LOGOUT, DAN LOGIN SEBAGAI ADMIN
// 5.LIHAT HISTORY NOVEL YANG BARU DILIHAT (STACK)
// 6.ORDERAN NOVEL (QUEUE)

//SEMOGA PAHAM BANG HEHE..


// include library yang dibutuhkan
#include <iostream>
#include <cstdlib>
#include <limits>
using namespace std;

// struct untuk data novel
#define max_history 100

struct detailNovel {
    string penerbit;
    string tahunTerbit;
};
struct novel {
    string judul;
    string genre;
    detailNovel detail;
};

struct Node {
    novel Novel;
    Node* next;
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

// STACK
novel history[max_history];
int top = -1;

void push(novel data){
    if (top == max_history - 1){
        setTextColor(31);
        cout << "History Penuh" << endl;
        setTextColor(0);
        return;
    }
    top++;
    history[top] = data;
}

void pop(){
    if (top == -1){
        setTextColor(31);
        cout << "History Kosong" << endl;
        setTextColor(0);
        return;
    } else {
    cout <<"NOVEL YANG BARU SAJA DILIHAT "<< history[top].judul << endl;
    top--;
    }
}

// QUEUE
novel order[max_history];
int front = 0;
int rear = -1;


void enqueue(novel data){
    if (rear == max_history - 1){
        setTextColor(31);
        cout << "Orderan Penuh" << endl;
        setTextColor(0);
        return;
    }
    rear++;
    history[rear] = data;
}

void dequeue(){
    if (front > rear){
        setTextColor(31);
        cout << "Orderan Kosong" << endl;
        setTextColor(0);
        return;
    } else {
    setTextColor(32);
    cout << "ORDERAN NOVEL "<< history[front].judul << " TELAH DI KONFIRMASI" << endl;
    setTextColor(0);
    front++;
    }
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
        clear();
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
        cout << "====================\n";
        setTextColor(0);
        cout << "[1] MENAMBAH NOVEL\n";
        cout << "[2] MELIHAT DAFTAR NOVEL\n";
        cout << "[3] MENGEDIT NOVEL\n";
        cout << "[4] MENGHAPUS NOVEL\n";
        cout << "[5] HISTORY NOVEL YANG BARU DILIHAT\n";
        cout << "[6] ORDERAN NOVEL\n";
        cout << "[7] LOGOUT\n";
        cout << "[8] EXIT PROGRAM\n\n";
        cout << "PILIH MENU NOMOR: ";
        cin >> choice;
        cin.ignore();
        if(cin.fail() || choice < 1 || choice > 6){
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

void addLast(Node *&head, novel databaru, int *jumlahNovelDitambahkan){
    Node *nodeBaru = new Node;
    nodeBaru -> Novel = databaru;
    nodeBaru -> next = NULL;
    if (head == NULL){
        head = nodeBaru;
        return;
    }

    Node *temp = head;
    while (temp -> next != NULL){
        temp = temp -> next;
    }
    temp -> next = nodeBaru;
    (*jumlahNovelDitambahkan)++;
}

void display(Node *&head) {
    int i = 1;
    Node *temp = head;
    if (head == NULL) {
        cout << "List Kosong" << endl;
        return;
    }
    
    // melihat judul novel dulu, jika ingin melihat detail novel bisa diubah
    setTextColor(33);
    cout << "====================\n";
    cout << "      LIST NOVEL    \n";
    cout << "====================\n\n";
    setTextColor(0);
    while (temp != NULL) {
        cout << i << ". " << "JUDUL : " << temp->Novel.judul << endl;
        i++;
        temp = temp->next; // Gerakkan pointer temp ke node berikutnya
    }

    cout << "\nApakah Anda ingin melihat detail novel? (y/n) : ";
    char pilih;
    cin >> pilih;
    cin.ignore();
    do {
        if (pilih == 'n') {
            return;
        } else if (pilih == 'y') {
            break;
        } else {
            cout << "Pilihan tidak valid, silahkan masukkan y atau n : ";
            cin >> pilih;
            cin.ignore();
        }
    } while (pilih != 'y' || pilih != 'n');
    
    // pilih nomor novel yang ingin dilihat detailnya
    cout << "NOMOR NOVEL YANG INGIN DILIHAT DETAILNYA : ";
    int nomorNovel;
    cin >> nomorNovel;
    cin.ignore();
    
    i = 1;
    temp = head; // Reset temp ke head untuk melihat detail novel
    while (temp != NULL) {
        if (i == nomorNovel) {
            clear();
            setTextColor(33);
            cout << "====================\n";
            cout << "      DETAIL NOVEL    \n";
            cout << "====================\n\n";
            setTextColor(0);
            cout << "JUDUL : " << temp->Novel.judul << endl 
                 << "GENRE : " << temp->Novel.genre << endl 
                 << "TAHUN TERBIT : " << temp->Novel.detail.tahunTerbit << endl 
                 << "NAMA PENERBIT : " << temp->Novel.detail.penerbit << endl;
            push(temp->Novel);
            return;
        }
        temp = temp->next;
        i++;
    } 
}

void edit(Node *&head, int *jumlahNovelDitambahkan){
    int index;
    display(head);
    cout << "NOMOR NOVEL YANG INGIN DI EDIT : ";
    cin >> index;
    cin.ignore();
    //kondisi kalau index yang diinputkan tidak ada
    if (index < 1 || index > *jumlahNovelDitambahkan){
        setTextColor(31);
        cout << "NOVEL TIDAK DITEMUKAN" << endl;
        setTextColor(0);
        pause();
        return;
    }
    int i = 1;
    Node *temp = head;
    while (temp != NULL){
        if (i == index){
            cout << "====================\n";
            cout << "    EDIT NOVEL    \n";
            cout << "====================\n\n";
            cout << "NAMA NOVEL BARU : ";
            getline(cin, temp -> Novel.judul);
            cout << "GENRE NOVEL BARU : ";
            getline(cin, temp -> Novel.genre);
            cout << "TAHUN TERBIT : ";
            getline(cin, temp -> Novel.detail.tahunTerbit);
            cout << "NAMA PENERBIT : ";
            getline(cin, temp -> Novel.detail.penerbit);
            setTextColor(32);
            cout << "NOVEL BERHASIL DI EDIT" << endl;
            setTextColor(0);
            return;
        }
        temp = temp -> next;
        i++;
    }
}

void hapus (Node *&head){
    int index;
    display(head);
    cout << "NOMOR NOVEL YANG INGIN DIHAPUS : ";
    cin >> index;
    cin.ignore();
    Node *temp = head;
    Node *prev = NULL;
    int i = 1;
    while (temp != NULL){
        if (i == index){
            if (prev == NULL){
                head = temp -> next;
                delete temp;
                return;
            }
            prev -> next = temp -> next;
            delete temp;
            setTextColor(32);
            cout << "NOVEL BERHASIL DIHAPUS" << endl;
            setTextColor(0);
            pause();
            return;
        }
        prev = temp;
        temp = temp -> next;
        i++;
    }
}

void menuDuaUser(Node *&head){
    int index;
    int i = 1;
    Node *temp = head;
    if (head == NULL) {
        cout << "List Kosong" << endl;
        return;
    }
    cout << "====================\n";
    cout << "      LIST NOVEL    \n";
    cout << "====================\n\n";
    while (temp != NULL) {
        cout << i << ". " << "JUDUL : " << temp->Novel.judul << endl;
        i++;
        temp = temp->next; 
    }
    cout << "NOMOR NOVEL YANG INGIN DIBELI : ";
    cin >> index;
    cin.ignore();
    temp = head;
    i = 1;
    while (temp != NULL){
        if (i == index){
            setTextColor(32);
            cout << "TERIMAKASIH ATAS PEMBELIAN NOVEL " << temp -> Novel.judul << endl;
            setTextColor(0);
            pause();
            enqueue(temp -> Novel);
            return;
        }
        temp = temp -> next;
        i++;
        }
        setTextColor(31);
        cout << "NOVEL TIDAK DITEMUKAN" << endl;
        setTextColor(0);
        pause();
        return;
}

int menuUser(){
    int choice;
    while (true) {
        setTextColor(33);
        cout << "====================\n";
        cout << "     MENU USER    \n";
        cout << "====================\n";
        setTextColor(0);
        cout << "[1] MELIHAT DAFTAR NOVEL\n";
        cout << "[2] MEMBELI NOVEL\n";
        cout << "[3] LOGOUT\n";
        cout << "[4] EXIT PROGRAM\n\n";
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

int main(){
    user login;
    admin log;
    int jumlahNovelDitambahkan = 2;
    log.namaAdmin = "Heri";
    log.pwAdmin = "Heri";
    login.namaUser = "User";
    login.pwUser = "User";
    Node *head = NULL;
    novel novel1 = {"Harry Potter", "Fantasy", {"Gramedia", "2000"}};
    novel novel2 = {"The Lord of The Rings", "Fantasy", {"Gramedia", "2000"}};
    addLast(head, novel1, &jumlahNovelDitambahkan);
    addLast(head, novel2, &jumlahNovelDitambahkan);
    setTextColor(33);
    clear();
    cout << "=============================\n";
    cout << "   PROGRAM CRUD LIST NOVEL  \n";
    cout << "=============================\n\n";
    setTextColor(0);

    int hasilLogin;
    while(true){ 
        hasilLogin = menuLogin(login, log); 
        if (hasilLogin == -1){
            continue; 
        } else if (hasilLogin == 0 ) { 
            int pilihan; 
            do {
                clear();
                pilihan = menuAdmin(); // Ambil pilihan dari menu admin
                novel novelBaru;
                switch(pilihan){
                    case 1:
                        clear();
                        cout << "JUDUL : ";
                        getline(cin, novelBaru.judul);
                        cout << "GENRE : ";
                        getline(cin, novelBaru.genre);
                        cout << "TAHUN TERBIT : ";
                        getline(cin, novelBaru.detail.tahunTerbit);
                        cout << "NAMA PENERBIT : ";
                        getline(cin, novelBaru.detail.penerbit);
                        addLast(head, novelBaru, &jumlahNovelDitambahkan); 
                        setTextColor(32);
                        cout << "NOVEL BERHASIL DITAMBAHKAN\n";
                        setTextColor(0);
                        pause();
                        break;
                    case 2:
                        clear();
                        display(head); 
                        pause();
                        break;
                    case 3:
                        clear();
                        edit(head, &jumlahNovelDitambahkan); 
                        break;
                    case 4:
                        clear();
                        hapus(head); 
                        break;
                    case 5:
                        clear();
                        pop();
                        pause();
                        break;
                    case 6:
                        clear();
                        dequeue();
                        pause();
                        break;

                    case 7: // Logout
                        break;

                    case 8: // EXIT
                        return 0; 
                }
            } while(pilihan != 7); 
        } else if (hasilLogin == 1) { 
            int choice;
            do {
                clear();
                choice = menuUser(); 
                switch(choice){
                    case 1:
                        clear();
                        display(head); 
                        pause();
                        break;
                    case 2:
                        clear();
                        menuDuaUser(head); 
                        break;
                    case 3:
                        clear();
                        break;
                    case 4:
                        return 0; 
                }
            } while(choice != 3); 
        }
    }
}

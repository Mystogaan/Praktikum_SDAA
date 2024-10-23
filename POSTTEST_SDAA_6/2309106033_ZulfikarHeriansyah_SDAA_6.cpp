// Nama : Zulfikar Heriansyah
// NIM  : 2309106033
// Posttest 6 : Implementasi Searching

// Langkah-langkah:
// 1. Lakukan Sorting secara ascending menggunakan Merge Sort
// 2. Setelah melakukan sorting, user baru bisa melakukan searching (disini saya tidak mengatur searching secara descending)
// 3. User bisa melakukan searching berdasarkan stok, harga, dan judul



// include library yang dibutuhkan
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <algorithm>  
#include <cctype>     
using namespace std;

// struct untuk data novel
#define max_history 100

// inisialisasi data
struct detailNovel {
    string penerbit;
    string tahunTerbit;
    int harga;
    int stok;
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

// terminal cheetsheet
void pause(){
    cout << "";
    cout << "...";
    cin.get();
}

void clear(){
    system("cls");
}

// Merge Sort (Ascending)
void splisList(Node *head, Node **frontRef, Node **backRef){ //Mencari nilai tengah
    Node *fast;
    Node *slow;
    slow = head;
    fast = head -> next;
    while (fast != NULL){
        fast = fast -> next;
        if (fast != NULL){
            slow = slow -> next;
            fast = fast -> next;
        }
    }
    *frontRef = head;
    *backRef = slow -> next;
    slow -> next = NULL;
}

Node *sortedMerge(Node *a, Node *b, bool ascending){ //Menggabungkan dua list
    Node *result = NULL;
    if (a == NULL){
        return b;
    } else if (b == NULL){
        return a;
    }
    if (a -> Novel.judul <= b -> Novel.judul){
        result = a;
        result -> next = sortedMerge(a -> next, b, ascending);
    } else {
        result = b;
        result -> next = sortedMerge(a, b -> next, ascending);
    }
    return result;
}

void mergeSort(Node **headRef, bool ascending){ //Mengurutkan list
    Node *head = *headRef;
    Node *a;
    Node *b;
    if ((head == NULL) || (head -> next == NULL)){
        return;
    }
    splisList(head, &a, &b);
    mergeSort(&a, ascending);
    mergeSort(&b, ascending);
    *headRef = sortedMerge(a, b, ascending);
}

// Quick Sort (Descending)
Node* getTail(Node* cur) { //Mencari nilai terakhir
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) { // Membagi list
    Node* pivot = end;
    Node* prev = NULL, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->Novel.judul >= pivot->Novel.judul) {
            if ((*newHead) == NULL)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;
            Node* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == NULL)
        (*newHead) = pivot;

    (*newEnd) = tail;

    return pivot;
}

Node* quickSortRecur(Node* head, Node* end) { //Mengurutkan list
    if (!head || head == end)
        return head;

    Node* newHead = NULL, *newEnd = NULL;

    Node* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) { // Jika pivot bukan elemen pertama
        Node* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        newHead = quickSortRecur(newHead, tmp);

        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

void quickSort(Node** headRef) { // Mengurutkan list
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
}

// Menambahkan data novel
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
    setTextColor(33);
    cout << "====================\n";
    cout << "      LIST NOVEL    \n";
    cout << "====================\n\n";
    setTextColor(0);
    while (temp != NULL) {
        cout << i << ". " << "JUDUL : " << temp->Novel.judul << endl;
        i++;
        temp = temp->next; 
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
    cout << "NOMOR NOVEL YANG INGIN DILIHAT DETAILNYA : "; // Memilih nomor novel yang ingin dilihat detailnya
    int nomorNovel;
    cin >> nomorNovel;
    cin.ignore();
    i = 1;
    temp = head; 
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
                 << "NAMA PENERBIT : " << temp->Novel.detail.penerbit << endl
                 << "HARGA : Rp" << temp->Novel.detail.harga << endl
                 << "STOK : " << temp->Novel.detail.stok << " buah" << endl;
            push(temp->Novel);
            return;
        }
        temp = temp->next;
        i++;
    } 
}

void edit(Node *&head, int *jumlahNovelDitambahkan){ // Mengedit data novel
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
            cout << "HARGA : Rp";
            cin >> temp -> Novel.detail.harga;
            cout << "STOK : ";
            cin >> temp -> Novel.detail.stok;
            cin.ignore();
            setTextColor(32);
            cout << "NOVEL BERHASIL DI EDIT" << endl;
            setTextColor(0);
            return;
        }
        temp = temp -> next;
        i++;
    }
}

void hapus (Node *&head){ // Menghapus data novel
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
    int jumlah;
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
        cout << "   HARGA: Rp" << temp->Novel.detail.harga << endl;
        cout << "   STOK : " << temp->Novel.detail.stok << " buah" << endl << endl;
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
            cout << "JUMLAH YANG INGIN DIBELI : ";
            cin >> jumlah;
            if (jumlah > temp->Novel.detail.stok){
                setTextColor(31);
                cout << "MAAF, STOK TIDAK MENCUKUPI!" << endl;
                setTextColor(0);
                pause();
                return;
            }
            temp->Novel.detail.stok -= jumlah;
            setTextColor(32);
            cout << "TERIMAKASIH ATAS PEMBELIAN " << jumlah << " BUAH NOVEL " << temp->Novel.judul << endl;
            cout << "TOTAL HARGA: Rp" << temp->Novel.detail.harga * jumlah << endl;
            setTextColor(0);
            pause();
            enqueue(temp->Novel);
            return;
        }
        temp = temp->next;
        i++;
    }
    setTextColor(31);
    cout << "NOVEL TIDAK DITEMUKAN" << endl;
    setTextColor(0);
    pause();
    return;
}

// Menu user
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
        cout << "[3] SORTING\n";
        cout << "[4] SEARCHING\n";
        cout << "[5] LOGOUT\n";
        cout << "[6] EXIT PROGRAM\n\n";
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

// Menu login
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

// Menu admin
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
        cout << "[7] SORTING ASCEDNING (MERGE)\n";
        cout << "[8] SORTING DESCENDING (QUICK)\n";
        cout << "[9] SEARCHING\n";
        cout << "[10] LOGOUT\n";
        cout << "[11] EXIT PROGRAM\n\n";
        cout << "PILIH MENU NOMOR: ";
        cin >> choice;
        cin.ignore();
        if(cin.fail() || choice < 1 || choice > 11){
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

// untuk searching, saya menggunakan sorting terpisah untuk searching stok dan harga
// Fungsi untuk sorting berdasarkan stok (ascending)
Node* sortedMergeStok(Node* a, Node* b) { // Menggabungkan dua list
    Node* result = NULL;
    if (a == NULL) return b;
    if (b == NULL) return a;

    if (a->Novel.detail.stok <= b->Novel.detail.stok) {
        result = a;
        result->next = sortedMergeStok(a->next, b);
    } else {
        result = b;
        result->next = sortedMergeStok(a, b->next);
    }
    return result;
}

void mergeSortStok(Node** headRef) { // Mengurutkan list
    Node* head = *headRef;
    Node* a;
    Node* b;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    splisList(head, &a, &b);
    mergeSortStok(&a);
    mergeSortStok(&b);
    *headRef = sortedMergeStok(a, b);
}

// Fungsi untuk sorting berdasarkan harga (ascending)
Node* sortedMergeHarga(Node* a, Node* b) { // Menggabungkan dua list
    Node* result = NULL;
    if (a == NULL) return b;
    if (b == NULL) return a;

    if (a->Novel.detail.harga <= b->Novel.detail.harga) {
        result = a;
        result->next = sortedMergeHarga(a->next, b);
    } else {
        result = b;
        result->next = sortedMergeHarga(a, b->next);
    }
    return result;
}

void mergeSortHarga(Node** headRef) { // Mengurutkan list
    Node* head = *headRef;
    Node* a;
    Node* b;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    splisList(head, &a, &b); // membagi linked list menjadi dua bagian
    mergeSortHarga(&a);
    mergeSortHarga(&b);
    *headRef = sortedMergeHarga(a, b);
}

// Fungsi untuk mengecek apakah list sudah terurut
bool isListSorted(Node* head) {
    if (head == nullptr || head->next == nullptr) // jika list kosong atau hanya memiliki satu elemen
        return true;
        
    Node* current = head;
    while (current->next != nullptr) {
        if (current->Novel.judul > current->next->Novel.judul)
            return false;
        current = current->next;
    }
    return true;
}

// Modifikasi Fibonacci Search untuk menampilkan semua hasil yang cocok
void fibonaccisearch(Node* head, int target) {
    Node* current = head;
    int index = 1;
    bool found = false;
    
    while (current != NULL) {
        if (current->Novel.detail.stok == target) { // jika stok novel sama dengan target
            if (!found) {
                setTextColor(32);
                cout << "\nNOVEL DENGAN STOK " << target << " DITEMUKAN:\n\n";
                setTextColor(0);
            }
            found = true;
            cout << "DITEMUKAN PADA NOMOR " << index << endl;
            cout << "DETAIL NOVEL\n";
            cout << "JUDUL : " << current->Novel.judul << endl 
                 << "GENRE : " << current->Novel.genre << endl 
                 << "TAHUN TERBIT : " << current->Novel.detail.tahunTerbit << endl 
                 << "NAMA PENERBIT : " << current->Novel.detail.penerbit << endl
                 << "HARGA : Rp" << current->Novel.detail.harga << endl
                 << "STOK : " << current->Novel.detail.stok << " buah\n" << endl;
        }
        current = current->next;
        index++;
    }
    
    if (!found) {
        setTextColor(31);
        cout << "NOVEL DENGAN STOK " << target << " TIDAK DITEMUKAN" << endl;
        setTextColor(0);
    }
}

// Modifikasi Jump Search untuk menampilkan semua hasil yang cocok
void jumpSearchHarga(Node* head, int target) {
    Node* current = head;
    int index = 1;
    bool found = false;
    
    while (current != NULL) {
        if (current->Novel.detail.harga == target) {
            if (!found) {
                setTextColor(32);
                cout << "\nNOVEL DENGAN HARGA " << target << " DITEMUKAN:\n\n";
                setTextColor(0);
            }
            found = true;
            
            cout << "DITEMUKAN PADA NOMOR " << index << endl;
            cout << "DETAIL NOVEL\n";
            cout << "JUDUL : " << current->Novel.judul << endl 
                 << "GENRE : " << current->Novel.genre << endl 
                 << "TAHUN TERBIT : " << current->Novel.detail.tahunTerbit << endl 
                 << "NAMA PENERBIT : " << current->Novel.detail.penerbit << endl
                 << "HARGA : Rp" << current->Novel.detail.harga << endl
                 << "STOK : " << current->Novel.detail.stok << " buah\n" << endl;
        }
        current = current->next;
        index++;
    }
    
    if (!found) {
        setTextColor(31);
        cout << "NOVEL DENGAN HARGA " << target << " TIDAK DITEMUKAN" << endl;
        setTextColor(0);
    }
}

// Modifikasi Boyer-Moore Search untuk menampilkan semua hasil yang cocok
void boyerMoore(Node* head, string pattern) {
    if (pattern.empty()) {
        cout << "Pattern pencarian tidak boleh kosong!" << endl;
        return;
    }
    
    Node* current = head;
    int index = 1;
    bool found = false;
    
    // Ubah pattern ke lowercase untuk pencarian case-insensitive untuk memudahkan pencarian
    transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);  // searchingnya diubah ke lowercase
    
    while (current != NULL) {
        string text = current->Novel.judul;
        transform(text.begin(), text.end(), text.begin(), ::tolower); // ubah judul novel ke lowercase karena input dari search juga sudah di lowercase
        
        if (text.find(pattern) != string::npos) {
            if (!found) {
                setTextColor(32);
                cout << "\nNOVEL DENGAN JUDUL MENGANDUNG '" << pattern << "' DITEMUKAN:\n\n";
                setTextColor(0);
            }
            found = true;
            
            cout << "DITEMUKAN PADA NOMOR " << index << endl;
            cout << "DETAIL NOVEL\n";
            cout << "JUDUL : " << current->Novel.judul << endl 
                 << "GENRE : " << current->Novel.genre << endl 
                 << "TAHUN TERBIT : " << current->Novel.detail.tahunTerbit << endl 
                 << "NAMA PENERBIT : " << current->Novel.detail.penerbit << endl
                 << "HARGA : Rp" << current->Novel.detail.harga << endl
                 << "STOK : " << current->Novel.detail.stok << " buah\n" << endl;
        }
        current = current->next;
        index++;
    }
    
    if (!found) {
        setTextColor(31);
        cout << "NOVEL DENGAN JUDUL MENGANDUNG '" << pattern << "' TIDAK DITEMUKAN" << endl;
        setTextColor(0);
    }
}

//Menu searching
void searchMenu(Node* head) {
    while (true) {
        clear();
        cout << "====================\n";
        cout << "    MENU SEARCH    \n";
        cout << "====================\n";
        cout << "[1] FIBONACCI SEARCH (STOK)\n";
        cout << "[2] JUMP SEARCH (HARGA)\n";
        cout << "[3] BOYER-MOORE SEARCH (JUDUL)\n";
        cout << "[4] KEMBALI KE MENU UTAMA\n\n";
        
        int choice;
        cout << "PILIH MENU NOMOR: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: {
                // Sort berdasarkan stok terlebih dahulu
                Node* tempHead = NULL;
                Node* current = head;
                // Menyalin Linked List untuk diurutkan
                while (current != NULL) {
                    Node* newNode = new Node;
                    newNode->Novel = current->Novel;
                    newNode->next = NULL;
                    
                    if (tempHead == NULL) {
                        tempHead = newNode;
                    } else {
                        Node* temp = tempHead;
                        while (temp->next != NULL) {
                            temp = temp->next;
                        }
                        temp->next = newNode;
                    }
                    current = current->next;
                }
                
                mergeSortStok(&tempHead);
                
                cout << "MASUKKAN STOK YANG DICARI: ";
                int target;
                cin >> target;
                
                fibonaccisearch(tempHead, target);
                
                // Membersihkan linked list sementara
                while (tempHead != NULL) {
                    Node* temp = tempHead;
                    tempHead = tempHead->next;
                    delete temp;
                }
                
                pause();
                break;
            }
            case 2: {
                // Sort berdasarkan harga terlebih dahulu
                Node* tempHead = NULL;
                Node* current = head;
                // Menyalin Linked List untuk diurutkan
                while (current != NULL) {
                    Node* newNode = new Node;
                    newNode->Novel = current->Novel;
                    newNode->next = NULL;
                    
                    if (tempHead == NULL) {
                        tempHead = newNode;
                    } else {
                        Node* temp = tempHead;
                        while (temp->next != NULL) {
                            temp = temp->next;
                        }
                        temp->next = newNode;
                    }
                    current = current->next;
                }
                
                mergeSortHarga(&tempHead);
                
                cout << "MASUKKAN HARGA YANG DICARI: ";
                int target;
                cin >> target;
                
                jumpSearchHarga(tempHead, target);
                
                // Membersihkan linked list sementara
                while (tempHead != NULL) {
                    Node* temp = tempHead;
                    tempHead = tempHead->next;
                    delete temp;
                }
                
                pause();
                break;
            }
            case 3: {
                cout << "\nMASUKKAN JUDUL YANG DICARI: ";
                string pattern;
                getline(cin, pattern);
                
                boyerMoore(head, pattern);
                pause();
                break;
            }
            case 4:
                return;
            default:
                setTextColor(31);
                cout << "PILIHAN TIDAK VALID\n";
                setTextColor(0);
                pause();
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
    novel novel1 = {"Harry Potter", "Fantasy", {"Gramedia", "2001", 150000, 10}};
    novel novel2 = {"Lord of The Rings", "Fantasy", {"Gramedia", "1998", 200000, 5}};
    novel novel3 = {"The Hobbit", "Fantasy", {"Gramedia", "1973", 175000, 8}};
    novel novel4 = {"Chronicles of Narnia", "Fantasy", {"Gramedia", "2005", 125000, 15}};
    novel novel5 = {"Hunger Games", "Fantasy", {"Gramedia", "2010", 160000, 12}};
    novel novel6 = {"Maze Runner", "Fantasy", {"Gramedia", "2015", 145000, 7}};
    novel novel7 = {"Fault in Our Stars", "Fantasy", {"Gramedia", "1991", 135000, 9}};
    novel novel8 = {"Perks of Being a Wallflower", "Fantasy", {"Gramedia", "1998", 155000, 6}};
    novel novel9 = {"The Book Thief", "Fantasy", {"Gramedia", "2001", 180000, 4}};
    novel novel10 = {"The Giver", "Fantasy", {"Gramedia", "2005", 140000, 11}};
    addLast(head, novel1, &jumlahNovelDitambahkan);
    addLast(head, novel2, &jumlahNovelDitambahkan);
    addLast(head, novel3, &jumlahNovelDitambahkan);
    addLast(head, novel4, &jumlahNovelDitambahkan);
    addLast(head, novel5, &jumlahNovelDitambahkan);
    addLast(head, novel6, &jumlahNovelDitambahkan);
    addLast(head, novel7, &jumlahNovelDitambahkan);
    addLast(head, novel8, &jumlahNovelDitambahkan);
    addLast(head, novel9, &jumlahNovelDitambahkan);
    addLast(head, novel10, &jumlahNovelDitambahkan);
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
                        cout << "HARGA : Rp";
                        cin >> novelBaru.detail.harga;
                        cout << "STOK : ";
                        cin >> novelBaru.detail.stok;
                        cin.ignore();
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

                    case 7: 
                        clear();
                        mergeSort(&head, true);
                        setTextColor(32);
                        cout << "NOVEL BERHASIL DIURUTKAN SECARA ASCENDING\n";
                        setTextColor(0);
                        display(head);
                        pause();
                        break;
                    case 8: 
                        clear();
                        quickSort(&head);
                        setTextColor(32);
                        cout << "NOVEL BERHASIL DIURUTKAN SECARA DESCENDING\n";
                        setTextColor(0);
                        display(head);
                        pause();
                        break; 
                    case 9:
                        clear();
                        searchMenu(head);
                        break;
                    case 10:
                        clear();
                        break;
                    case 11:
                        return 0;
                }
            } while(pilihan != 10); 
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
                        mergeSort(&head, true);
                        setTextColor(32);
                        cout << "NOVEL BERHASIL DIURUTKAN\n";
                        setTextColor(0);
                        display(head);
                        pause();
                        break;
                    case 4:
                        clear();
                        searchMenu(head);
                        break;
                    case 5:
                        clear();
                        break;
                    case 6:
                        return 0; 
                }
            } while(choice != 5); 
        }
    }
}

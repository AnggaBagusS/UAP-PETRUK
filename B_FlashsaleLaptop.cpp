#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>

using namespace std;

// Class untuk merepresentasikan sebuah laptop
class Laptop {
private:
    string brand;
    string model;
    int price;

public:
    Laptop(string brand, string model, int price) {
        this->brand = brand;
        this->model = model;
        this->price = price;
    }

    string getBrand() {
        return brand;
    }

    string getModel() {
        return model;
    }

    int getPrice() {
        return price;
    }
};

// Class untuk merepresentasikan seorang pembeli
class Pembeli {
private:
    string name;
    int budget;

public:
    Pembeli(string name, int budget) {
        this->name = name;
        this->budget = budget;
    }

    string getName() {
        return name;
    }

    int getBudget() {
        return budget;
    }
};

// Fungsi untuk melakukan flashsale secara rekursif
void flashsaleRec(queue<Pembeli*>& antrian, const vector<Laptop*>& laptops, int start, int end) {
    if (start > end)
        return;

    Pembeli* pembeli = antrian.front();
    antrian.pop();

    cout << "Pembeli " << pembeli->getName() << " melakukan flashsale" << endl;

    // Memilih laptop yang dapat dibeli oleh pembeli berdasarkan budget
    Laptop* laptopTerpilih = nullptr;
    bool laptopDitemukan = false;

    int mid = (start + end) / 2;

    if (laptops[mid]->getPrice() <= pembeli->getBudget()) {
        laptopTerpilih = laptops[mid];
        laptopDitemukan = true;
    }

    if (laptopDitemukan) {
        cout << "Pembeli " << pembeli->getName() << " membeli laptop " << laptopTerpilih->getBrand() << " " << laptopTerpilih->getModel() << endl << endl;
    } else {
        cout << "Pembeli " << pembeli->getName() << " tidak dapat membeli laptop karena budget tidak mencukupi" << endl << endl;
    }

    flashsaleRec(antrian, laptops, start, mid - 1);
    flashsaleRec(antrian, laptops, mid + 1, end);
}

// Fungsi wrapper untuk melakukan flashsale menggunakan divide and conquer
void flashsale(queue<Pembeli*>& antrian, const vector<Laptop*>& laptops) {
    flashsaleRec(antrian, laptops, 0, laptops.size() - 1);
}

int main() {
    // Inisialisasi daftar laptop yang akan di-flashsale
    Laptop* laptop1 = new Laptop("BrandA", "Model1", 12000);
    Laptop* laptop2 = new Laptop("BrandB", "Model2", 10000);
    Laptop* laptop3 = new Laptop("BrandC", "Model3", 8000);
    Laptop* laptop4 = new Laptop("BrandD", "Model4", 7000);
    Laptop* laptop5 = new Laptop("BrandE", "Model5", 6000);

    // Menyimpan daftar laptop dalam sebuah vector
    vector<Laptop*> laptops = {laptop1, laptop2, laptop3, laptop4, laptop5};

    // Mencetak daftar laptop yang tersedia
    cout << "Daftar Laptop Tersedia:" << endl;
    for (Laptop* laptop : laptops) {
        cout << laptop->getBrand() << " " << laptop->getModel() << " - Rp. " << laptop->getPrice() << endl;
    }

    // Membuat antrian pembayaran menggunakan queue
    queue<Pembeli*> antrianPembayaran;

    // Membuat beberapa pembeli dan menambahkan ke antrian pembayaran
    int numPembeli;
    cout << "Masukkan jumlah pembeli: ";
    cin >> numPembeli;

    for (int i = 0; i < numPembeli; i++) {
        string name;
        int budget;

        cout << "Masukkan nama pembeli " << i+1 << ": ";
        cin >> name;
        cout << "Masukkan budget pembeli " << i+1 << ": ";
        cin >> budget;

        Pembeli* pembeli = new Pembeli(name, budget);
        antrianPembayaran.push(pembeli);
    }

    flashsale(antrianPembayaran, laptops);



    return 0;
}

#include <iostream>
#include <string>
#include <iomanip>
//Luong Quoc Cuong 24810310195 
using namespace std;

// C헧 1:
struct Ngay {
    int ngay;
    int thang;
    int nam;
};

struct HangHoa {
    string maHang;
    string tenHang;
    Ngay ngayXuat;
    double giaXuat;
};

string intToString(int n) {
    if (n == 0) return "0";
    string s = "";
    while (n > 0) {
        s = char(n % 10 + '0') + s;
        n /= 10;
    }
    return s;
}

// C헧 2:
void nhapMotHangHoa(HangHoa &hh) {
    cout << "  - Nhap ma hang: ";
    getline(cin, hh.maHang);
    cout << "  - Nhap ten hang: ";
    getline(cin, hh.tenHang);
    cout << "  - Nhap ngay xuat (ngay thang nam): ";
    cin >> hh.ngayXuat.ngay >> hh.ngayXuat.thang >> hh.ngayXuat.nam;
    cout << "  - Nhap gia xuat (trieu dong): ";
    cin >> hh.giaXuat;
    cin.ignore();
}

void nhapDanhSach(HangHoa a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\n--- Nhap thong tin hang hoa thu " << i + 1 << " ---\n";
        nhapMotHangHoa(a[i]);
    }
}

// C헧 3:
void inTieuDe() {
    cout << left << setw(12) << "Ma Hang" 
         << setw(25) << "Ten Hang" 
         << setw(15) << "Ngay Xuat" 
         << setw(15) << "Gia Xuat (Trieu)" << endl;
    cout << string(67, '-') << endl;
}

void inMotHangHoa(const HangHoa &hh) {
    string ngayStr = intToString(hh.ngayXuat.ngay) + "/" + 
                     intToString(hh.ngayXuat.thang) + "/" + 
                     intToString(hh.ngayXuat.nam);

    cout << left << setw(12) << hh.maHang 
         << setw(25) << hh.tenHang 
         << setw(15) << ngayStr 
         << setw(15) << fixed << setprecision(2) << hh.giaXuat << endl;
}

void xuatDanhSach(HangHoa a[], int n) {
    inTieuDe();
    for (int i = 0; i < n; i++) {
        inMotHangHoa(a[i]);
    }
}

// C헧 4:
void quickSort(HangHoa a[], int left, int right) {
    if (left >= right) return;

    double pivot = a[(left + right) / 2].giaXuat;
    int i = left;
    int j = right;

    while (i <= j) {
        while (a[i].giaXuat < pivot) i++;
        while (a[j].giaXuat > pivot) j--;
        
        if (i <= j) {
            HangHoa t = a[i];
		    a[i] = a[j];
		    a[j] = t;
		    
            i++;
            j--;
        }
    }

    if (left < j) quickSort(a, left, j);
    if (i < right) quickSort(a, i, right);
}

// C헧 5:
void timKiemNhiPhanTheoGia(HangHoa a[], int n, double X) {
    int left = 0, right = n - 1;
    int pos = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid].giaXuat == X) {
            pos = mid;
            break;
        } else if (a[mid].giaXuat < X) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (pos == -1) {
        cout << "\n=> Khong tim thay hang hoa nao co gia xuat bang " << X << " trieu dong.\n";
        return;
    }

    int start = pos;
    while (start > 0 && a[start - 1].giaXuat == X) {
        start--;
    }

    int end = pos;
    while (end < n - 1 && a[end + 1].giaXuat == X) {
        end++;
    }

    cout << "\n=> KET QUA TIM KIEM HANG HOA CO GIA XUAT BANG " << X << " TRIEU DONG:\n";
    inTieuDe();
    for (int i = start; i <= end; i++) {
        inMotHangHoa(a[i]);
    }
}

// C헧 6:
int main() {
    int n;
    cout << "Nhap so luong hang hoa n: ";
    cin >> n;
    cin.ignore();

    if (n <= 0) {
        cout << "So luong hang hoa khong hop le!" << endl;
        return 0;
    }

    HangHoa *a = new HangHoa[n];
	cout << "\n==========================================";
    cout << "\n1. NHAP DANH SACH HANG HOA";
    cout << "\n==========================================\n";
    nhapDanhSach(a, n);
    cout << "\n==========================================";
    cout << "\n2. DANH SACH HANG HOA VUA NHAP";
    cout << "\n==========================================\n";
    xuatDanhSach(a, n);

    quickSort(a, 0, n - 1);
    cout << "\n==========================================";
    cout << "\n3. DANH SACH SAU KHI SAP XEP TANG DAN (QUICK SORT)";
    cout << "\n==========================================\n";
    xuatDanhSach(a, n);

    double X;
    cout << "\n==========================================";
    cout << "\n4. TIM KIEM HANG HOA THEO GIA XUAT X";
    cout << "\n==========================================\n";
    cout << "Nhap gia xuat X can tim (trieu dong): ";
    cin >> X;
    timKiemNhiPhanTheoGia(a, n, X);

    delete[] a;
    return 0;
}

# Tuần 2: Mảng & Con Trỏ — Bài tập

## 🎯 Mục tiêu tuần này
Thành thạo mảng 1D/2D, con trỏ, cấp phát động trong C++.

### Bài 1: Mảng cơ bản ⭐
Nhập mảng n phần tử. Tính min, max, trung bình, tổng. Không dùng STL.

#include <iostream>
using namespace std;

int main() {
    int n, tong = 0;
    cout << "Nhap n: "; cin >> n;
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        cout << "arr[" << i << "]: "; cin >> arr[i];
    }

    int minVal = arr[0], maxVal = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
        tong += arr[i];
    }

    cout << "Min: " << minVal << " | Max: " << maxVal 
         << " | Tong: " << tong << " | TB: " << (double)tong / n << endl;

    delete[] arr;
    return 0;
}

### Bài 2: Mảng 2D ⭐⭐
Nhân 2 ma trận n×n. Tính định thức ma trận 3×3. Hiển thị đẹp.

#include <iostream>
using namespace std;

int main() {
    int n = 3; // Cố định 3x3 để vừa tính nhân vừa tính định thức nhanh gọn
    int A[3][3], B[3][3], C[3][3] = {0};

    cout << "Nhap ma tran A (3x3):\n";
    for(int i=0; i<3; i++) for(int j=0; j<3; j++) cin >> A[i][j];
    cout << "Nhap ma tran B (3x3):\n";
    for(int i=0; i<3; i++) for(int j=0; j<3; j++) cin >> B[i][j];

    // Nhân ma trận
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            for(int k=0; k<3; k++) C[i][j] += A[i][k] * B[k][j];

    // Định thức A bằng quy tắc Sarrus
    int det = A[0][0]*(A[1][1]*A[2][2] - A[1][2]*A[2][1])
            - A[0][1]*(A[1][0]*A[2][2] - A[1][2]*A[2][0])
            + A[0][2]*(A[1][0]*A[2][1] - A[1][1]*A[2][0]);

    cout << "\nMa tran ket qua C:\n";
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) cout << C[i][j] << "\t";
        cout << endl;
    }
    cout << "Dinh thuc ma tran A: " << det << endl;
    return 0;
}

### Bài 3: Con trỏ & cấp phát động ⭐⭐
Cài đặt mảng động tự resize (như `std::vector` đơn giản). Hỗ trợ push_back, pop_back, at(i).
#include <iostream>
using namespace std;

class MangDong {
public:
    int *data; unsigned cap, sz;
    MangDong() { cap = 2; sz = 0; data = new int[cap]; }
    ~MangDong() { delete[] data; }

    void push_back(int val) {
        if (sz == cap) {
            cap *= 2;
            int* temp = new int[cap];
            for (unsigned i = 0; i < sz; i++) temp[i] = data[i];
            delete[] data; data = temp;
        }
        data[sz++] = val;
    }
    void pop_back() { if (sz > 0) sz--; }
    int at(unsigned i) { return data[i]; }
};

int main() {
    MangDong v; v.push_back(10); v.push_back(20); v.push_back(30);
    cout << "Size: " << v.sz << " | Vi tri 1: " << v.at(1) << endl;
    return 0;
}


### Bài 4: 🔥 Dự Án Mini — Student Score Manager ⭐⭐⭐
> **Cảm hứng:** BaiTapTongHop — Quản lý sinh viên (DSALab)
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct SV { string mssv, ten; double diem; };

int main() {
    SV ds[100]; int n = 0, chon; // Dùng mảng cố định 100 để code ngắn gọn nhất
    do {
        cout << "\n1.Them 2.Xoa 3.Tim 4.XepHang 5.InFile 0.Thoat. Chon: "; cin >> chon;
        if (chon == 1) {
            cout << "MSSV, Ten, Diem: "; cin >> ds[n].mssv; cin.ignore(); 
            getline(cin, ds[n].ten); cin >> ds[n].diem; n++;
        } 
        else if (chon == 2) {
            string id; cout << "Nhap MSSV xoa: "; cin >> id;
            for(int i=0; i<n; i++) if(ds[i].mssv == id) {
                for(int j=i; j<n-1; j++) ds[j] = ds[j+1]; n--; break;
            }
        } 
        else if (chon == 3) {
            string key; cout << "Nhap MSSV can tim: "; cin >> key;
            for(int i=0; i<n; i++) if(ds[i].mssv == key) cout << ds[i].ten << " - " << ds[i].diem << endl;
        } 
        else if (chon == 4) { // Bubble Sort giảm dần
            for(int i=0; i<n-1; i++) for(int j=0; j<n-i-1; j++)
                if(ds[j].diem < ds[j+1].diem) { SV t = ds[j]; ds[j] = ds[j+1]; ds[j+1] = t; }
            for(int i=0; i<n; i++) cout << i+1 << ". " << ds[i].ten << " | " << ds[i].diem << endl;
        } 
        else if (chon == 5) {
            ofstream f("diem_sinhvien.txt");
            for(int i=0; i<n; i++) f << ds[i].mssv << "\t" << ds[i].ten << "\t" << ds[i].diem << "\n";
            f.close(); cout << "Da xuat file!\n";
        }
    } while (chon != 0);
    return 0;
}

Xây dựng hệ thống quản lý điểm sinh viên bằng **mảng động**:
- Thêm / xóa / sửa sinh viên (tên, MSSV, điểm)
- Sắp xếp theo điểm (dùng Selection Sort hoặc Bubble Sort)
- Tìm kiếm theo tên hoặc MSSV (Linear Search)
- Thống kê: điểm cao nhất, thấp nhất, trung bình lớp
- Xuất danh sách ra file `diem_sinhvien.txt`

```
=== QUẢN LÝ ĐIỂM SINH VIÊN ===
1. Thêm sinh viên
2. Xóa sinh viên
3. Tìm kiếm
4. Xếp hạng lớp
5. Xuất báo cáo
0. Thoát
```

---
📁 Tham khảo: `Chuong1_TongQuan/Chuong1_TongQuan.cpp`

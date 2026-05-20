/*
================================================================================
CHƯƠNG TRÌNH QUẢN LÝ HÀNG ĐỢI KHÁM BỆNH - BỆNH VIỆN CHỢ RẪY
Cấu trúc dữ liệu áp dụng: Hàng đợi vòng bằng mảng (Circular Queue) - Cơ chế FIFO
================================================================================
*/

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

// ============================================================================
// 1. ĐỊNH NGHĨA CẤU TRÚC DỮ LIỆU BỆNH NHÂN
// ============================================================================
struct BenhNhan {
    unsigned maSo;
    string hoTen;
    unsigned tuoi;
    string trieuChung;
};

// ============================================================================
// 2. LỚP TEMPLATE HÀNG ĐỢI VÒNG (CIRCULAR QUEUE)
// ============================================================================
template <typename Tipo>
class FilaHospital {
private:
    Tipo* v;                  // Mảng động lưu trữ dữ liệu
    unsigned tamanho;         // Sức chứa tối đa của hàng đợi
    int frente;               // Chỉ số đầu hàng đợi (nơi đi ra khám)
    int tras;                 // Chỉ số cuối hàng đợi (nơi xếp hàng vào)
    unsigned totalElementos;  // Số lượng bệnh nhân hiện tại trong hàng chờ

public:
    // Constructor khởi tạo hàng đợi với kích thước cố định
    FilaHospital(unsigned tam) {
        tamanho = tam;
        v = new Tipo[tamanho];
        frente = 0;
        tras = -1;
        totalElementos = 0;
    }

    // Destructor giải phóng bộ nhớ động, tránh rò rỉ bộ nhớ (Memory Leak)
    ~FilaHospital() {
        delete[] v;
    }

    // Kiểm tra hàng đợi đã đầy chưa
    bool filaCheia() {
        return totalElementos == tamanho;
    }

    // Kiểm tra hàng đợi có trống không
    bool filaVazia() {
        return totalElementos == 0;
    }

    // Thêm một phần tử vào cuối hàng đợi (EnQueue)
    void pushBnhNhan(Tipo x) {
        tras = (tras + 1) % tamanho; // Phép toán chia lấy dư để tạo vòng lặp mảng
        v[tras] = x;
        totalElementos++;
    }

    // Lấy phần tử đầu tiên ra khỏi hàng đợi (DeQueue)
    Tipo popBnhNhan() {
        Tipo temp = v[frente];
        frente = (frente + 1) % tamanho; // Tịnh tiến đầu hàng theo vòng tròn
        totalElementos--;
        return temp;
    }

    // Xem thông tin phần tử đứng đầu hàng
    Tipo elementodaFrente() {
        return v[frente];
    }

    // Lấy số lượng bệnh nhân đang chờ hiện tại
    unsigned getTotalElementos() {
        return totalElementos;
    }

    // Lấy giá trị phần tử tại vị trí logic thứ i trong hàng đợi để hiển thị
    Tipo getValorPosicao(unsigned i) {
        unsigned idx = (frente + i) % tamanho;
        return v[idx];
    }
};

// ============================================================================
// 3. CHƯƠNG TRÌNH CHÍNH QUẢN LÝ ĐIỀU PHỐI BỆNH VIỆN
// ============================================================================
int main()
{
    // Thiết lập màu sắc console sang màu xanh sáng cho giao diện y tế
    system("color 3");

    unsigned soPhongKham, pKham;
    cout << "=== HE THONG DIEU PHOI - BENH VIEN CHO RAY ===" << endl;
    cout << "Nhap so luong Phong/Khoa kham benh: ";
    cin >> soPhongKham;

    // Khởi tạo mảng các con trỏ để quản lý danh sách các phòng khám khác nhau
    FilaHospital<BenhNhan>** danhSachPhong = new FilaHospital<BenhNhan>*[soPhongKham];

    // Mỗi phòng khám mặc định có hàng chờ tối đa là 5 bệnh nhân
    for (unsigned i = 0; i < soPhongKham; i++) {
        danhSachPhong[i] = new FilaHospital<BenhNhan>(5);
    }

    BenhNhan bn;
    int opc;

    do {
        system("cls");
        cout << "********* HANG CHO KHAM BENH - CHO RAY *********" << endl;
        cout << "1 - TIEP NHAN BENH NHAN MOI (Xep hang)." << endl;
        cout << "2 - GOI BENH NHAN VAO KHAM (Xuat hang)." << endl;
        cout << "3 - XEM BENH NHAN KE TIEP VAO KHAM." << endl;
        cout << "4 - HIEN THI TAT CA CAC HANG CHO KHAM." << endl;
        cout << "9 - THOAT HE THONG." << endl;
        cout << "------------------------------------------------" << endl;
        cout << "CHON CHUC NANG: ";
        cin >> opc;

        switch (opc) {
        case 1:
            cout << "\nNhap STT Phong/Khoa kham (tu 0 den " << soPhongKham - 1 << "): ";
            cin >> pKham;

            if (pKham >= soPhongKham) {
                cout << "Phong kham khong ton tai trên he thong!" << endl;
                system("pause");
                break;
            }

            if (danhSachPhong[pKham]->filaCheia()) {
                cout << "Hang cho cua Phong nay da qua tai! Vui long dieu phoi sang phong khac..." << endl;
                system("pause");
            }
            else {
                cout << "\n--- NHAP THONG TIN BENH NHAN ---" << endl;
                cout << "Nhap Ma so benh nhan: ";
                cin >> bn.maSo;
                cin.ignore(); // Xóa bộ nhớ đệm để tránh trôi dòng khi nhập chuỗi ngay sau số

                cout << "Nhap Ho va Ten: ";
                getline(cin, bn.hoTen);

                cout << "Nhap Tuoi: ";
                cin >> bn.tuoi;
                cin.ignore(); // Xóa bộ nhớ đệm

                cout << "Nhap Trieu chung/Ly do kham: ";
                getline(cin, bn.trieuChung);

                danhSachPhong[pKham]->pushBnhNhan(bn);
                cout << "\nDA THEM BENH NHAN VAO HANG CHO CUA PHONG " << pKham << "." << endl;
                system("pause");
            }
            break;

        case 2:
            cout << "\nNhap STT Phong/Khoa kham can goi benh nhan: ";
            cin >> pKham;

            if (pKham >= soPhongKham) {
                cout << "Phong kham khong ton tai!" << endl;
                system("pause");
                break;
            }

            if (danhSachPhong[pKham]->filaVazia()) {
                cout << "\nHANG CHO TRONG! Khong co benh nhan nao dang cho tai phong nay." << endl;
                system("pause");
            }
            else {
                bn = danhSachPhong[pKham]->popBnhNhan();
                cout << "\n>>> MOI BENH NHAN VAO PHONG KHAM <<<" << endl;
                cout << "Ma so: " << bn.maSo << endl;
                cout << "Ho ten: " << bn.hoTen << endl;
                cout << "Tuoi: " << bn.tuoi << endl;
                cout << "Trieu chung: " << bn.trieuChung << endl;
                cout << "\nBenh nhan da duoc xoa khoi hang cho de vao gap bac si." << endl;
                system("pause");
            }
            break;

        case 3:
            cout << "Nhap STT Phong/Khoa kham can kiem tra: ";
            cin >> pKham;

            if (pKham >= soPhongKham) {
                cout << "Phong kham khong ton tai!" << endl;
                system("pause");
                break;
            }

            if (danhSachPhong[pKham]->filaVazia()) {
                cout << "\nHANG CHO DANG TRONG!" << endl;
                system("pause");
            }
            else {
                bn = danhSachPhong[pKham]->elementodaFrente();
                cout << "\n--- BENH NHAN CHUAN BI VAO KHAM TIEP THEO ---" << endl;
                cout << "Ma so: " << bn.maSo << endl;
                cout << "Ho ten: " << bn.hoTen << endl;
                cout << "Tuoi: " << bn.tuoi << endl;
                cout << "Trieu chung: " << bn.trieuChung << endl;
                system("pause");
            }
            break;

        case 4:
            cout << "\n===== TRANG THAI CAC HANG CHO TAI BENH VIEN =====" << endl;
            for (unsigned q = 0; q < soPhongKham; q++) {
                cout << "\n[PHONG KHAM SO " << q << "] ";
                if (danhSachPhong[q]->filaVazia()) {
                    cout << "-> HANG CHO TRONG." << endl;
                }
                else {
                    cout << "(Dang co " << danhSachPhong[q]->getTotalElementos() << " nguoi cho):" << endl;
                    for (unsigned i = 0; i < danhSachPhong[q]->getTotalElementos(); i++) {
                        bn = danhSachPhong[q]->getValorPosicao(i);
                        cout << "  [STT Cho: " << i + 1 << "] | MSBN: " << bn.maSo
                            << " | Ten: " << bn.hoTen << " | Tuoi: " << bn.tuoi
                            << " | Trieu chung: " << bn.trieuChung << endl;
                    }
                }
                cout << "----------------------------------------------------------------";
            }
            cout << endl;
            system("pause");
            break;

        case 9:
            cout << "DA THOAT HE THONG DIEU PHOI." << endl;
            break;

        default:
            cout << "LUA CHON KHONG HOP LE!!! VUI LONG CHON LAI!";
            system("pause");
        }
    } while (opc != 9);

    // ============================================================================
    // 4. GIẢI PHÓNG BỘ NHỚ ĐỘNG (QUAN TRỌNG TRONG ĐÁP ÁN DSA)
    // ============================================================================
    for (unsigned i = 0; i < soPhongKham; i++) {
        delete danhSachPhong[i]; // Giải phóng từng hàng đợi phòng khám
    }
    delete[] danhSachPhong;       // Giải phóng mảng quản lý phòng khám

    return 0;
}


#include "ticket.h"
#include <iostream>

using namespace std;

int main() {
    TicketSystem busSystem;

    // Them sẵn dữ liệu gia lap ban dau
    busSystem.bookTicket({ "0912345678", "Nguyen Van A", 1, "" });
    busSystem.bookTicket({ "0988888888", "Tran Thi Chiem (Cao tuoi)", 3, "" });
    busSystem.bookTicket({ "0977777777", "Le Minh Bau (Phu nu mang thai)", 2, "" });

    int choice;
    do {
        cout << "\n================= HE THONG QUAN LY XE BUYT 1/7/2026 =================\n";
        cout << " 1. Xem so do ghe ngoi\n";
        cout << " 2. Dang ky cho ngoi (Mien phi ve)\n";
        cout << " 3. Huy cho (Tu dong don nguoi trong hang doi uu tien)\n";
        cout << " 4. Tra cuu hanh khach theo Ma/CCCD (Dung BST)\n";
        cout << " 5. In toan bo danh sach hanh khach da co ghe\n";
        cout << " 6. Thong ke hieu qua giam thieu o nhiem & Ngan sach tro gia\n";
        cout << " 0. Thoat chuong trinh\n";
        cout << "--------------------------------------------------------------------\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
        case 1:
            busSystem.displaySeatMap();
            break;
        case 2: {
            Customer c;
            cout << "Nhap ma hanh khach (CCCD/SDT): "; cin >> c.id;
            cout << "Nhap ho ten hanh khach: "; cin.ignore(); getline(cin, c.name);
            cout << "Muc uu tien (3: Cao nhat/Gia ca, 2: Bau/Tre em, 1: Pho thong): "; cin >> c.priorityLevel;
            busSystem.bookTicket(c);
            break;
        }
        case 3: {
            string id;
            cout << "Nhap ma hanh khach muon huy cho: "; cin >> id;
            busSystem.cancelTicket(id);
            break;
        }
        case 4: {
            string id;
            cout << "Nhap ma hanh khach can tim: "; cin >> id;
            busSystem.searchCustomer(id);
            break;
        }
        case 5:
            busSystem.showBookedList();
            break;
        case 6:
            busSystem.showStatistics();
            break;
        case 0:
            cout << "\nDa dong he thong dieu hanh xe buyt!\n";
            break;
        default:
            cout << ">> Lua chon khong hop le, vui long kiem tra lai.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
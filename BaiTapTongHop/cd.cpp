#include "ticket.h"
#include <iostream>

using namespace std;

TicketSystem::TicketSystem() {
    bookedCount = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 4; j++) {
            seatMap[i][j] = 'O';
        }
    }
}

BSTNode* TicketSystem::insertBST(BSTNode* node, Customer c) {
    if (!node) return new BSTNode(c);
    if (c.id < node->customer.id) node->left = insertBST(node->left, c);
    else node->right = insertBST(node->right, c);
    return node;
}

BSTNode* TicketSystem::searchBST(BSTNode* node, string id) {
    if (!node || node->customer.id == id) return node;
    if (id < node->customer.id) return searchBST(node->left, id);
    return searchBST(node->right, id);
}

void TicketSystem::displaySeatMap() {
    cout << "\n--- SO DO GHE NGOI XE BUYT THOI GIAN THUC ---\n";
    cout << "      [ Tai xe ]\n";
    for (int i = 0; i < 10; i++) {
        cout << "Hang " << i + 1 << ": ";
        for (int j = 0; j < 4; j++) {
            if (j == 2) cout << "   "; // Loi di giua xe buyt
            cout << "[" << seatMap[i][j] << "] ";
        }
        cout << "\n";
    }
    cout << "Ghi chu: [O]: Con trong | [X]: Da dat cho\n";
}

void TicketSystem::bookTicket(Customer c) {
    if (bookedCount < totalSeats) {
        bool assigned = false;
        for (int i = 0; i < 10 && !assigned; i++) {
            for (int j = 0; j < 4; j++) {
                if (seatMap[i][j] == 'O') {
                    seatMap[i][j] = 'X';
                    c.seatCode = to_string(i + 1) + "-" + to_string(j + 1);
                    assigned = true;
                    break;
                }
            }
        }
        bookedCount++;
        customerRoot = insertBST(customerRoot, c);
        txHistory.push({ "BOOK", c });
        cout << ">> CAP VE MIEN PHI THANH CONG! Ma ghe: " << c.seatCode << "\n";
    }
    else {
        cout << ">> XE DA HET CHO! He thong tu dong dua vao danh sach cho uu tien.\n";
        waitingQueue.push(c);
    }
}

void TicketSystem::cancelTicket(string id) {
    BSTNode* res = searchBST(customerRoot, id);
    if (!res) {
        cout << ">> Khong tim thay thong tin hanh khach tren he thong!\n";
        return;
    }

    Customer canceledCustomer = res->customer;
    txHistory.push({ "CANCEL", canceledCustomer });

    // Parse chuoi "hang-cot" (vi du "2-3") de tra lai trang thai ghe trong
    size_t dash = canceledCustomer.seatCode.find('-');
    int r = stoi(canceledCustomer.seatCode.substr(0, dash)) - 1;
    int c = stoi(canceledCustomer.seatCode.substr(dash + 1)) - 1;

    seatMap[r][c] = 'O';
    bookedCount--;
    cout << ">> Da huy cho thanh cong cho hanh khach: " << canceledCustomer.name << "\n";

    // Tu dong quet Hang doi uu tien neu xe co cho trong moi
    if (!waitingQueue.empty()) {
        Customer nextCustomer = waitingQueue.top();
        waitingQueue.pop();

        cout << ">> Tu dong dieu phoi cho hanh khach cho uu tien: " << nextCustomer.name << "\n";
        seatMap[r][c] = 'X';
        nextCustomer.seatCode = to_string(r + 1) + "-" + to_string(c + 1);
        bookedCount++;
        customerRoot = insertBST(customerRoot, nextCustomer);
        txHistory.push({ "BOOK", nextCustomer });
        cout << ">> Cap ghe " << nextCustomer.seatCode << " cho khach hang cho thanh cong!\n";
    }
}

void TicketSystem::searchCustomer(string id) {
    BSTNode* res = searchBST(customerRoot, id);
    if (res) {
        cout << "\n--- KET QUA TIM KIEM HANH KHACH (BST) ---\n";
        cout << "  Ma/CCCD: " << res->customer.id << "\n";
        cout << "  Ho va ten: " << res->customer.name << "\n";
        cout << "  Vi tri ghe: " << res->customer.seatCode << "\n";
    }
    else {
        cout << ">> Khong tim thay hanh khach nao trung khop voi ma tren!\n";
    }
}

void TicketSystem::printInOrder(BSTNode* node) {
    if (!node) return;
    printInOrder(node->left);
    cout << "  ID: " << node->customer.id
        << " | Ten: " << node->customer.name
        << " | Ghe: " << node->customer.seatCode << "\n";
    printInOrder(node->right);
}

void TicketSystem::showBookedList() {
    cout << "\n--- DANH SACH HANH KHACH DA DUOC CAP GHE (Sap xep theo ID) ---\n";
    if (!customerRoot) {
        cout << "  (Chua co hanh khach nao dat cho)\n";
    }
    else {
        printInOrder(customerRoot);
    }
}

void TicketSystem::showStatistics() {
    cout << "\n================= BAO CAO HIET QUA (NGAY 1/7/2026) =================\n";
    cout << " * Trang thai he thong: MIEN PHI TOAN DAN CHONG UN TAC & O NHIEM\n";
    cout << " * So luong ghe da lap day: " << bookedCount << " / " << totalSeats << "\n";
    cout << " * So luong ghe con trong : " << totalSeats - bookedCount << "\n";
    cout << " * So hanh khach dang doi (Priority Queue): " << waitingQueue.size() << " nguoi.\n";
    cout << " * Gia ve niem yet dong nhat: 7,000 VND / luot\n";
    cout << " * Ngan sach thanh pho tro gia (Du kien chi): " << bookedCount * 7000 << " VND\n";
    cout << " * Luong CO2 tiet kiem duoc cho moi truong: " << bookedCount * 0.5 << " kg CO2\n";
    cout << "====================================================================\n";
}
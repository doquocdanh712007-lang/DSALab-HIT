#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <vector>
#include <queue>
#include <stack>

// Thong tin hanh khach
struct Customer {
    std::string id;          // Ma khach hang (CCCD hoac So dien thoai)
    std::string name;        // Ho va ten
    int priorityLevel;  // Muc uu tien: 3 (Nguoi gia/Khuyet tat), 2 (Bau/Tre em), 1 (Pho thong)
    std::string seatCode;    // Ma ghe ngoi (Vi du: "1-2")
};

// Nut cua Cay nhi phan tim kiem (BST) de quan ly hanh khach da co ghe
struct BSTNode {
    Customer customer;
    BSTNode* left = nullptr;
    BSTNode* right = nullptr;

    BSTNode(Customer c) : customer(c), left(nullptr), right(nullptr) {}
};

// Cau truc so sanh cho Hang doi uu tien (Priority Queue)
struct ComparePriority {
    bool operator()(const Customer& c1, const Customer& c2) {
        // Muc uu tien cao hon se duoc dung truoc
        return c1.priorityLevel < c2.priorityLevel;
    }
};

// Lich su de ho tro Huy ve (Stack)
struct Transaction {
    std::string type; // "BOOK" hoac "CANCEL"
    Customer customer;
};

class TicketSystem {
private:
    char seatMap[10][4]; // Sodo ghe ngoi xe buyt mang 2D (10 hang x 4 cot)
    int totalSeats = 40;
    int bookedCount = 0;

    BSTNode* customerRoot = nullptr; // Goc cay BST
    std::priority_queue<Customer, std::vector<Customer>, ComparePriority> waitingQueue; // Danh sach cho VIP
    std::stack<Transaction> txHistory; // Lich su de ho tro xuly hoan tac

    // Cac ham tro giup cho cay BST
    BSTNode* insertBST(BSTNode* node, Customer c);
    BSTNode* searchBST(BSTNode* node, std::string id);
    void printInOrder(BSTNode* node);

public:
    TicketSystem();
    void displaySeatMap();
    void bookTicket(Customer c);
    void cancelTicket(std::string id);
    void searchCustomer(std::string id);
    void showStatistics();
    void showBookedList();
};

#endif // TICKET_H
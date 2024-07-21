#include <iostream>
#include <string>
#include <vector>
#include <limits> 

using namespace std;

const int NUM_ROWS = 10;
const int NUM_COLS = 4;

class Seat {
private:
    int row;
    int col;
    bool reserved;
    string passengerName;

public:
    Seat(int r, int c) : row(r), col(c), reserved(false), passengerName("") {}

    void reserve(const string& name) {
        reserved = true;
        passengerName = name;
    }

    void cancel() {
        reserved = false;
        passengerName = "";
    }

    bool isReserved() const {
        return reserved;
    }

    string getPassengerName() const {
        return passengerName;
    }

    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }

    void print() const {
        cout << "Row " << row << ", Col " << col;
        if (reserved) {
            cout << " (reserved for " << passengerName << ")";
        } else {
            cout << " (available)";
        }
        cout << endl;
    }
};

class Bus {
private:
    vector<vector<Seat>> seats;

public:
    Bus() {
        for (int i = 0; i < NUM_ROWS; i++) {
            vector<Seat> row;
            for (int j = 0; j < NUM_COLS; j++) {
                row.emplace_back(i, j);
            }
            seats.push_back(row);
        }
    }

    void reserve(int row, int col, const string& name) {
        if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS) {
            cout << "Invalid seat position" << endl;
            return;
        }
        Seat& seat = seats[row][col];
        if (seat.isReserved()) {
            cout << "Seat is already reserved for " << seat.getPassengerName() << endl;
        } else {
            seat.reserve(name);
            cout << "Seat reserved for " << name << endl;
        }
    }

    void cancel(int row, int col) {
        if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS) {
            cout << "Invalid seat position" << endl;
            return;
        }
        Seat& seat = seats[row][col];
        if (!seat.isReserved()) {
            cout << "Seat is not reserved" << endl;
        } else {
            string name = seat.getPassengerName();
            seat.cancel();
            cout << "Reservation for " << name << " cancelled" << endl;
        }
    }

    void printLayout() const {
        cout << "Bus Layout:" << endl;
        for (const auto& row : seats) {
            for (const auto& seat : row) {
                seat.print();
            }
        }
        cout << endl;
    }

    void showAllBookings() const {
        cout << "All Bookings:" << endl;
        for (const auto& row : seats) {
            for (const auto& seat : row) {
                if (seat.isReserved()) {
                    cout << "Row " << seat.getRow() << ", Col " << seat.getCol() << " reserved for " << seat.getPassengerName() << endl;
                }
            }
        }
        cout << endl;
    }
};

void showMenu() {
    cout << "1. Show Bus Layout" << endl;
    cout << "2. Reserve a Seat" << endl;
    cout << "3. Cancel Reservation" << endl;
    cout << "4. Show All Bookings" << endl;
    cout << "5. Exit" << endl;
}

int main() {
    Bus bus;
    int choice;
    while (true) {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        if (choice == 5) {
            break;
        }

        int row, col;
        string name;
        switch (choice) {
            case 1:
                bus.printLayout();
                break;
            case 2:
                cout << "Enter row and column to reserve (0-9 for row, 0-3 for column): ";
                cin >> row >> col;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Enter passenger name: ";
                getline(cin, name);
                bus.reserve(row, col, name);
                break;
            case 3:
                cout << "Enter row and column to cancel (0-9 for row, 0-3 for column): ";
                cin >> row >> col;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                bus.cancel(row, col);
                break;
            case 4:
                bus.showAllBookings();
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }
    return 0;
}

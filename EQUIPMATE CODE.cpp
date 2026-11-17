#include <iostream>
#include <string>
using namespace std;

int main() {


    string eqName[5] = {"Chair", "Table", "Speaker", "Whiteboard", "Microphone"};
    int eqStock[5] = {5, 3, 4, 2, 6};
    int userBorrowedQty[5] = {0, 0, 0, 0, 0};

    const int MAX = 100;
    int borrowedEquip[MAX];
    int borrowedQty[MAX];
    int returnedQty[MAX] = {0};
    string returnDate[MAX];
    string actualReturnDate[MAX];
    int recordCount = 0;

    string borrower, contact, information;
    int dashboardChoice;
    int systemChoice;
    int equipChoice;

    cout << "\n===== EQUIPMATE LOGIN =====\n";

    cout << "Enter Borrower's Full Name: ";
    getline(cin, borrower);

    cout << "Enter Borrower's Contact Information: ";
    getline(cin, contact);
    
    cout << "Enter Borrower's LRN(Learner Reference Number): ";
    getline(cin, information);
    
    cout << "\nWelcome, " << borrower << "!\n";


 
    do {

        cout << "\n===== DASHBOARD =====\n";
        cout << "1. Equipment Borrowing System\n";
        cout << "2. My Borrowed Equipments\n";
        cout << "0. Log Out\n";
        cout << "Enter your choice: ";
        cin >> dashboardChoice;

        switch (dashboardChoice) {

            case 1: {

                do {

                    cout << "\n===== EQUIPMENT BORROWING SYSTEM =====\n";
                    cout << "1. View Available Equipment\n";
                    cout << "2. Borrow Equipment\n";
                    cout << "3. Return Borrowed Equipment\n";
                    cout << "4. View Your Records\n";
                    cout << "0. Back to Dashboard\n";
                    cout << "Enter your choice: ";
                    cin >> systemChoice;

                    switch (systemChoice) {

                        case 1: {

                            cout << "\n===== AVAILABLE EQUIPMENT =====\n";

                            for (int i = 0; i < 5; i++) {
                                cout << i + 1 << ". " << eqName[i]
                                     << " (Available Stock: " << eqStock[i] << ")\n";
                            }

                            cout << "\nEnter equipment number to view (1-5): ";
                            cin >> equipChoice;

                            if (equipChoice >= 1 && equipChoice <= 5) {

                                int index = equipChoice - 1;

                                cout << "\n===== EQUIPMENT DETAILS =====\n";
                                cout << "Equipment Name: " << eqName[index] << endl;
                                cout << "Available Stock: " << eqStock[index] << endl;
                                cout << "Currently Borrowed: " << userBorrowedQty[index] << endl;

                            } else {

                                cout << "Invalid equipment choice.\n";
                            }

                            break;
                        }


                        case 2: {

                            int eqNum, qty;
                            bool validSelection = false;

                            cout << "\n===== BORROWING INSTRUCTIONS =====\n";
                            cout << "1. Select the equipment you want to borrow.\n";
                            cout << "2. Enter the quantity.\n";
                            cout << "3. Provide your expected return date.\n";
                            cout << "4. Return the equipment on or before the due date.\n";

                            while (!validSelection) {

                                cout << "\n===== AVAILABLE EQUIPMENT =====\n";

                                for (int i = 0; i < 5; i++) {
                                    cout << i + 1 << ". " << eqName[i]
                                         << " (Stock: " << eqStock[i] << ")\n";
                                }

                                cout << "Enter equipment number (1-5): ";
                                cin >> eqNum;

                                if (eqNum < 1 || eqNum > 5) {
                                    cout << "Invalid equipment number.\n";
                                    continue;
                                }

                                int index = eqNum - 1;

                                if (eqStock[index] <= 0) {
                                    cout << "That equipment is unavailable.\n";
                                    continue;
                                }

                                cout << "Enter quantity (1-" << eqStock[index] << "): ";
                                cin >> qty;

                                if (qty < 1 || qty > eqStock[index]) {
                                    cout << "Invalid quantity.\n";
                                    continue;
                                }

                                if (recordCount >= MAX) {
                                    cout << "Borrowing record limit reached.\n";
                                    break;
                                }

                                cout << "Enter expected return date (YYYY-MM-DD): ";
                                cin >> returnDate[recordCount];

                                borrowedEquip[recordCount] = index;
                                borrowedQty[recordCount] = qty;
                                returnedQty[recordCount] = 0;
                                actualReturnDate[recordCount] = "Not yet returned";

                                eqStock[index] -= qty;
                                userBorrowedQty[index] += qty;

                                recordCount++;

                                cout << "\nBorrowing recorded successfully!\n";
                                cout << "Borrower: " << borrower << endl;
                                cout << "Equipment: " << eqName[index] << endl;
                                cout << "Quantity: " << qty << endl;

                                validSelection = true;
                            }

                            break;
                        }


                        case 3: {

                            int totalBorrowed = 0;

                            cout << "\n===== RETURN MENU =====\n";

                            for (int i = 0; i < recordCount; i++) {

                                if (returnedQty[i] < borrowedQty[i]) {

                                    cout << i + 1 << ". "
                                         << eqName[borrowedEquip[i]]
                                         << " (Remaining: "
                                         << borrowedQty[i] - returnedQty[i]
                                         << ", Return Date: "
                                         << returnDate[i] << ")\n";

                                    totalBorrowed++;
                                }
                            }

                            if (totalBorrowed == 0) {
                                cout << "There is no borrowed equipment to return.\n";
                                break;
                            }

                            int returnChoice;

                            cout << "\nEnter record number to return (0 to go back): ";
                            cin >> returnChoice;

                            if (returnChoice == 0) {
                                cout << "Returning to equipment menu.\n";
                                break;
                            }

                            if (returnChoice < 1 || returnChoice > recordCount ||
                                returnedQty[returnChoice - 1] >= borrowedQty[returnChoice - 1]) {

                                cout << "Invalid selection.\n";
                                break;
                            }

                            int index = returnChoice - 1;
                            int equipIndex = borrowedEquip[index];

                            int remaining = borrowedQty[index] - returnedQty[index];

                            int returnQty;

                            cout << "Enter quantity to return (1-" << remaining << "): ";
                            cin >> returnQty;

                            if (returnQty >= 1 && returnQty <= remaining) {

                                eqStock[equipIndex] += returnQty;
                                userBorrowedQty[equipIndex] -= returnQty;
                                returnedQty[index] += returnQty;

                                cout << "Enter actual return date (YYYY-MM-DD): ";
                                cin >> actualReturnDate[index];

                                cout << "\nReturned successfully!\n";

                            } else {

                                cout << "Invalid return quantity.\n";
                            }
                            
                            if (actualReturnDate[index] > returnDate[index]) {
                                cout << "Returning date Overdue! Thank you.";
                            }
                            else {
                                cout << "=====Thank you.====";
                            }
                            

                            break;
                        }
                        
                        case 4: {

                            bool found = false;
                            string today;

                            cout << "\n===== YOUR BORROWING RECORDS =====\n";

                            if (recordCount == 0) {
                                cout << "No borrowed equipment found.\n";
                                break;
                            }

                            cout << "Enter today's date (YYYY-MM-DD): ";
                            cin >> today;

                            for (int i = 0; i < recordCount; i++) {

                                cout << "\nRecord No.: " << i + 1;

                                cout << "\nBorrowed Equipment: "
                                     << eqName[borrowedEquip[i]];

                                cout << "\nQuantity: "
                                     << borrowedQty[i];

                                cout << "\nReturn Date: "
                                     << returnDate[i];

                                cout << "\nActual Return Date: "
                                     << actualReturnDate[i];

                                if (returnedQty[i] == borrowedQty[i]) {

                                    cout << "\nStatus: Returned";

                                    if (actualReturnDate[i] > returnDate[i]) {
                                        cout << "\nOverdue: Yes";
                                    } else {
                                        cout << "\nOverdue: No";
                                    }

                                } else {

                                    if (returnedQty[i] > 0) {
                                        cout << "\nStatus: Partially Returned";
                                    } else {
                                        cout << "\nStatus: Borrowed";
                                    }

                                    if (today > returnDate[i]) {
                                        cout << "\nOverdue: Yes";
                                    } else {
                                        cout << "\nOverdue: No";
                                    }
                                }

                                cout << "\n-----------------------------\n";

                                found = true;
                            }

                            break;
                        }


                        case 0:

                            cout << "Returning to Dashboard...\n";
                            break;


                        default:

                            cout << "Invalid choice. Please try again.\n";
                    }

                } while (systemChoice != 0);

                break;
            }


           
            case 2: {

                cout << "\n===== MY BORROWED EQUIPMENTS =====\n";
                cout << "Borrower Name: " << borrower << endl;
                cout << "Contact Information: " << contact << endl;

                if (recordCount == 0) {

                    cout << "No borrowing records found.\n";
                    break;
                }

                string today;

                cout << "\nEnter today's date (YYYY-MM-DD): ";
                cin >> today;

                for (int i = 0; i < recordCount; i++) {

                    cout << "\nRecord No.: " << i + 1;

                    cout << "\nEquipment Name: "
                         << eqName[borrowedEquip[i]];

                    cout << "\nQuantity: "
                         << borrowedQty[i];

                    cout << "\nReturned Quantity: "
                         << returnedQty[i];

                    cout << "\nExpected Return Date: "
                         << returnDate[i];

                    cout << "\nActual Return Date: "
                         << actualReturnDate[i];

                    if (returnedQty[i] == borrowedQty[i]) {

                        cout << "\nStatus: Returned";

                        if (actualReturnDate[i] > returnDate[i]) {
                            cout << "\nOverdue: Yes";
                        } else {
                            cout << "\nOverdue: No";
                        }

                    } else {

                        if (returnedQty[i] > 0) {
                            cout << "\nStatus: Partially Returned";
                        } else {
                            cout << "\nStatus: Borrowed";
                        }

                        if (today > returnDate[i]) {
                            cout << "\nOverdue: Yes";
                        } else {
                            cout << "\nOverdue: No";
                        }
                    }

                    cout << "\n-----------------------------\n";
                }

                break;
            }
            
           
            case 0:

                cout << "\nLogging out...\n";
                cout << "Thank you for using EquipMate, " << borrower << "!\n";
                break;


            default:

                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (dashboardChoice != 0);

    return 0;
}



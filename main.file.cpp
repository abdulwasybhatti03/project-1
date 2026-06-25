#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include<iomanip>
using namespace std;
                                                                                                                   
// =======================================================
//                STRUCTURES
//=======================================================

struct Passenger {
    int id;
    string name;
    string password;
    string phone;
};

struct Flight {
    int flightNo;
    string destination;
    string date;
    string time;
    int seats;
    float fare;
};

struct Booking {
    int bookingID;
    int passengerID;
    int flightNo;
    float fare;
};

// =======================================================
//                 GLOBAL ARRAYS
//=======================================================

Passenger* passengers = nullptr;
Flight* flights = nullptr;
int pCount = 0, fCount = 0;
int seatMatrix[100][60];       


//==========================================
//   READING PASSENGERS FROM FILE AT START
//==========================================

void loadPassengers() {
    ifstream file("passengers.txt");
    pCount = 0;
    int tempId;
    string tempName, tempPass, tempPhone;

    // count records

    while (file >> tempId) {
        file.ignore();
        getline(file, tempName);
        file >> tempPass >> tempPhone;
        pCount++;
    }
    file.close();
    passengers = new Passenger[pCount];
    file.open("passengers.txt");
    for (int i = 0; i < pCount; i++) {
        file >> passengers[i].id;
        file.ignore();
        getline(file, passengers[i].name);
        file >> passengers[i].password >> passengers[i].phone;
    }
    file.close();
}

//=============================================
//     FUNCTION FOR CHANGING ADMIN PASSWORD
//=============================================
void changeAdminPassword() {
    string oldPass, newPass, fileUser, filePass;

    ifstream fin("admin.txt");
    fin >> fileUser >> filePass;
    fin.close();
    system("cls");
    system("color 0B");
    cout << "                                           ======================================================\n"
        << "                                                         CHANGE ADMIN PASSWORD                \n"
        << "                                           ======================================================\n" << endl;
    cout << "Enter current password: ";
    cin >> oldPass;

    if (oldPass != filePass) {
        cout << "Wrong password!\n";
        cout << "Press Enter to continue...";
        cin.get(); cin.get();
        return;
    }

    cout << "Enter new password: ";
    cin >> newPass;

    ofstream fout("admin.txt");
    fout << fileUser << endl << newPass;
    fout.close();
    system("color 0A");
    cout << "Password changed successfully!";
    cout << "\nPress Enter to continue...";
    cin.get(); cin.get();
}

void savePassengers() {
    ofstream file("passengers.txt");
    for (int i = 0; i < pCount; i++) {
        file << passengers[i].id << endl
            << passengers[i].name << endl
            << passengers[i].password << " "
            << passengers[i].phone << endl;
    }
    file.close();
}
//==========================================
//        LOADING FLIGHT FILE AT START
//==========================================
void loadFlights() {
    ifstream file("flights.txt");
    fCount = 0;
    Flight temp;
    while (file >> temp.flightNo >> temp.destination
        >> temp.date >> temp.time >> temp.seats >> temp.fare) {
        fCount++;
    }
    file.close();
    flights = new Flight[fCount];
    file.open("flights.txt");
    for (int i = 0; i < fCount; i++) {
        file >> flights[i].flightNo >> flights[i].destination
            >> flights[i].date >> flights[i].time
            >> flights[i].seats >> flights[i].fare;
    }
    file.close();
}

//================================================================
//         WRITING THE FLIGHT INFORMATION IN FLIGHT.TXT FILE
//================================================================
void saveFlights() {
    ofstream file("flights.txt");
    for (int i = 0; i < fCount; i++) {
        file << flights[i].flightNo << " "
            << flights[i].destination << " "
            << flights[i].date << " "
            << flights[i].time << " "
            << flights[i].seats << " "
            << flights[i].fare << endl;
    }
    file.close();
}

//  GETTING THE LAST PASSENGERS ID TO ASSIGN THE NEW PASSENGER NEW ID ACCORDING TO IT

int getLastPassengerID() {
    ifstream file("passengers.txt");
    int id = 1000;
    string name, pass, phone;
    while (file >> id) {
        file.ignore();
        getline(file, name);
        file >> pass >> phone;
    }
    file.close();
    return id;
}

//  =============================================
//           PASSENGER REGISTRATION
//=============================================

void registerPassenger() {
    system("cls");
    system("color 0B");

    // Create a new passenger
    Passenger p;
    p.id = getLastPassengerID() + 1;
    cin.ignore();
    cout << "                                          ======================================================\n"
        << "                                                     Passenger Registration                 \n"
        << "                                          ======================================================\n";
    bool flag = false;
    do {

        cout << "Enter Full Name: ";
        getline(cin, p.name);
        if (p.name.empty()) {
            cout << "Name cannot be empty. Please enter a valid name.\n";
        }
        if (p.name.length() > 50) {
            cout << "Name is too long. Please enter a name with less than 50 characters.\n";
        }

        int   count = 0;
        for (int i = 0;i < p.name.length();i++) {
            if (p.name[i] != 'A' && p.name[i] != ' ' && p.name[i] != 'B' && p.name[i] != 'C' && p.name[i] != 'D' && p.name[i] != 'E' && p.name[i] != 'F' && p.name[i] != 'G' && p.name[i] != 'H' && p.name[i] != 'I' && p.name[i] != 'J' && p.name[i] != 'K' && p.name[i] != 'L' && p.name[i] != 'M' && p.name[i] != 'N' && p.name[i] != 'O' && p.name[i] != 'P' && p.name[i] != 'Q' && p.name[i] != 'R' && p.name[i] != 'S' && p.name[i] != 'T' && p.name[i] != 'U' && p.name[i] != 'V' && p.name[i] != 'W' && p.name[i] != 'X' && p.name[i] != 'Y' && p.name[i] != 'Z') {
                cout << "Name should only be capital alphabets!\n";
                flag = true;
                break;
            }
            flag = false;
        }

    } while (p.name.empty() || p.name.length() > 50 || flag);
    do {
        cout << "Enter Password: ";
        cin >> p.password;
        if (p.password.length() < 8)
            cout << "\nPassword should be atleast 8 characters\n";
        if (p.password.empty())
            cout << "Password cannot be empty";
    } while (p.password.length() < 8 || p.password.empty());
    do {
        cout << "Enter Phone: ";
        cin >> p.phone;
        if (p.phone.length() < 11) {
            cout << "\nPHONE NUMBER SHOULD BE 11 DIGITS!!\n";
        }
    } while (p.phone.length() < 11);

    // -------------------------------
    // Dynamic memory allocation
    // -------------------------------
    Passenger* temp = new Passenger[pCount + 1]; // create new array with extra space
    for (int i = 0; i < pCount; i++)
        temp[i] = passengers[i];                // copy old passengers
    temp[pCount] = p;                           // add new passenger
    delete[] passengers;                        // free old array
    passengers = temp;                           // point to new array
    pCount++;                                    // increase count

    savePassengers();                            // save all passengers to file

    system("color 09");
    cout << "                                          ======================================================\n"
        << "                                                        REGISTRATION SUCCESSFUL                  \n"
        << "                                          ======================================================\n" << endl;
    cout << "\nYour Passenger ID: " << p.id;
    cout << "\nPress Enter to continue...";
    cin.get(); cin.get(); // wait for Enter key
}




// =======================================================
//                 FLIGHT VIEW BY ADMIN AND PASSENGER
//=======================================================

void showFlights() {
    system("cls");
    system("color 0E");
    cout << "                ======================================================\n";
    cout << "                                  AVAILABLE FLIGHTS                   \n";
    cout << "                ======================================================\n\n";

    // Print table header
    cout << left
        << setw(10) << "Flight No"
        << setw(15) << "Destination"
        << setw(12) << "Date"
        << setw(8) << "Time"
        << setw(8) << "Seats"
        << setw(8) << "Fare per Flight" << endl;

    cout << "------------------------------------------------------------------------------------\n";

    for (int i = 0; i < fCount; i++) {
        cout << left
            << setw(10) << flights[i].flightNo
            << setw(15) << flights[i].destination
            << setw(12) << flights[i].date
            << setw(8) << flights[i].time
            << setw(8) << flights[i].seats
            << setw(8) << flights[i].fare
            << endl;
        cout << "-------------------------------------------------------------------------------\n";

        
    }
    cout << endl;


    cout << "\nPress Enter to continue...";
    cin.get(); cin.get();
}
//
// =======================================================
//          GENERATE BOOKING ID
//=======================================================

int generateBookingID() {
    ifstream file("bookings.txt");
    int id, lastID = 5000;   // starting booking ID

    while (file >> id) {
        file.ignore(1000, '\n'); // skip rest of line
        lastID = id;
    }
    file.close();

    return lastID + 1;
}


// =======================================================
//             FLIGHT BOOKING AND WRITING IN FILE
//=======================================================

void bookFlight(int pid) {
    int fno;
    showFlights();
    system("cls");
    system("color 03");
    cout << "                                                  ======================================================\n"
        << "                                                                      BOOK FLIGHTS                      \n"
        << "                                                  ======================================================\n" << endl;
    cout << "Enter Flight Number: ";
    cin >> fno;

    for (int i = 0; i < fCount; i++) {
        if (flights[i].flightNo == fno && flights[i].seats > 0) {
            flights[i].seats--;

            // Find first available seat and mark it booked
            int seatNumber = -1;
            for (int j = 0; j < flights[i].seats; j++) {
                if (seatMatrix[i][j] == 0) {
                    seatMatrix[i][j] = 1;
                    seatNumber = j + 1; // seat numbers start at 1
                    break;
                }
            }

            ofstream book("bookings.txt", ios::app);
            int bid = generateBookingID();

            book << bid << " "
                << pid << " "
                << fno << " "
                << flights[i].fare << endl;
            book.close();

            saveFlights();
            system("color 02");
            cout << "                                      ======================================================\n"
                << "                                                     FLIGHT BOOKED SUCCESSFULLY                   \n"
                << "                                      ======================================================\n" << endl;
            cout << "Your Booking Id is: " << bid << endl;
            cout << "Your Seat Number: " << seatNumber << endl;
            cout << "\nPress Enter to continue...";
            cin.get(); cin.get();
            return;
        }
    }
    cout << "\nFlight Not Available!";
    cout << "\nPress Enter to continue...";
    cin.get(); cin.get();
}

// =======================================================
//              CENCEL BOOKING
//=======================================================

void cancelBooking(int pid) {
    ifstream fin("bookings.txt");
    ofstream fout("temp.txt");
    Booking b;
    int bid;
    bool found = false;
    system("color 05");
    system("cls");
    cout << "                                               ======================================================\n"
        << "                                                                  CENCEL BOOKING                     \n"
        << "                                               ======================================================\n" << endl;
    cout << "Enter Booking ID: ";
    cin >> bid;

    while (fin >> b.bookingID >> b.passengerID >> b.flightNo >> b.fare) {
        if (b.bookingID == bid && b.passengerID == pid) {
            found = true;
            cout << "\nBooking Cancelled. Refund: " << b.fare * 0.8 << endl;
            for (int i = 0; i < fCount; i++)
                if (flights[i].flightNo == b.flightNo)
                    flights[i].seats++;
        }
        else {
            fout << b.bookingID << " "
                << b.passengerID << " "
                << b.flightNo << " "
                << b.fare << endl;
        }
    }

    fin.close();
    fout.close();
    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");
    saveFlights();

    if (!found)
        cout << "\nBooking Not Found!";

    cout << "\nPress Enter to continue...";
    cin.get(); cin.get();
}

// =======================================================
//                 PASSENGER REPORT
//=======================================================

void passengerReport(int pid) {
    ifstream file("bookings.txt");
    Booking b;
    float total = 0;

    system("cls");
    system("color 0B");
    cout << "                                          ======================================================\n"
        << "                                                               PASSENGER REPORT                  \n"
        << "                                          ======================================================\n" << endl;
    bool bookings = false;
    int i = 1;
    while (file >> b.bookingID >> b.passengerID >> b.flightNo >> b.fare) {
       
        if (b.passengerID == pid) {
            bookings = true;
            //  Find destination using flight number
            string destination = "Unknown";
            for (int j = 0; j < fCount; j++) {
                if (flights[j].flightNo == b.flightNo) {
                    destination = flights[j].destination;
                    break;
                }
            }
            cout << "                                            Booking no. " << i << endl << endl;
            cout << "Booking ID   : " << b.bookingID << endl;
            cout << "Flight No    : " << b.flightNo << endl;
            cout << "Destination  : " << destination << endl;
            cout << "Fare         : " << b.fare << endl << endl;

            total += b.fare;
            i++;
        }
    }
    if (!bookings) {
        cout << "\n         ----------------You have not Booked any Flight yet-------------------\n";
    }
    cout << "\nTotal Amount Spent: " << total;
    cout << "\n\nPress Enter to continue...";
    cin.get(); cin.get();
    file.close();
}



// =======================================================
//              VIEW   PASSENGER 
//=======================================================
void viewPassengers() {
    system("cls");
    system("color 03");
    cout << "                                               ======================================================\n"
        << "                                                                   PASSENGERS                 \n"
        << "                                               ======================================================\n" << endl;
    for (int i = 0; i < pCount; i++) {
        cout << "                    Passenger " << i + 1 << endl << endl;
        cout << "Name    : " << passengers[i].name << endl;
        cout << "ID      : " << passengers[i].id << endl;
        cout << "Phone   : " << passengers[i].phone << endl;
        cout << "Password: " << passengers[i].password << endl << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.get(); cin.get();
}
// =======================================================
//               DELETE   PASSENGER 
//=======================================================
void deletePassenger() {
    int pid;
    system("cls");
    system("color 07");
    cout << "                                                        ======================================================\n"
        << "                                                                       PASSENGERS DELETION                \n"
        << "                                                        ======================================================\n" << endl;
    cout << "Enter Passenger ID to Delete: ";
    cin >> pid;

    for (int i = 0; i < pCount; i++) {
        if (passengers[i].id == pid) {
            for (int j = i; j < pCount - 1; j++)
                passengers[j] = passengers[j + 1];
            pCount--;
            savePassengers();
            cout << "\nPassenger Deleted Successfully!";
            cout << "\nPress Enter to Continue...";
            cin.get(); cin.get();
            return;
        }
    }
    cout << "\nPassenger Not Found!";
    cout << "\nPress Enter to Continue...";
    cin.get(); cin.get();
}
//========================================================
//             Passenger add by admin
//==========================================================
void adminAddPassenger() {
    system("cls");
    system("color 0B");
    Passenger p;
    p.id = getLastPassengerID() + 1;

    cout << "                                      ======================================================\n"
        << "                                                     ADD PASSENGER (ADMIN)                     \n"
        << "                                      ======================================================\n";
    cin.ignore();
    bool flag = false;
    do {
        
        cout << "Enter Full Name: ";
        getline(cin, p.name);
        if (p.name.empty()) {
            cout << "Name cannot be empty. Please enter a valid name.\n";
        }
        if (p.name.length() > 50) {
            cout << "Name is too long. Please enter a name with less than 50 characters.\n";
        }
     
        int   count = 0;
        for (int i = 0;i < p.name.length();i++) {
            if (p.name[i] != 'A' && p.name[i] != ' ' && p.name[i] != 'B' && p.name[i] != 'C' && p.name[i] != 'D' && p.name[i] != 'E' && p.name[i] != 'F' && p.name[i] != 'G' && p.name[i] != 'H' && p.name[i] != 'I' && p.name[i] != 'J' && p.name[i] != 'K' && p.name[i] != 'L' && p.name[i] != 'M' && p.name[i] != 'N' && p.name[i] != 'O' && p.name[i] != 'P' && p.name[i] != 'Q' && p.name[i] != 'R' && p.name[i] != 'S' && p.name[i] != 'T' && p.name[i] != 'U' && p.name[i] != 'V' && p.name[i] != 'W' && p.name[i] != 'X' && p.name[i] != 'Y' && p.name[i] != 'Z') {
                cout << "Name should only be capital alphabets!\n";
                flag = true;
                break;
            }
            flag = false;
        }
      
    } while (p.name.empty() || p.name.length() > 50|| flag);
    do {
        cout << "Enter Password: ";
        cin >> p.password;
        if (p.password.length() < 8)
            cout << "\nPassword should be atleast 8 characters\n";
        if (p.password.empty())
            cout << "Password cannot be empty";
    } while (p.password.length() < 8|| p.password.empty());
    do {
        cout << "Enter Phone: ";
        cin >> p.phone;
        if (p.phone.length() < 11) {
            cout << "\nPHONE NUMBER SHOULD BE 11 DIGITS!!\n";
        }
    } while (p.phone.length() < 11);
    // increase dynamic array size

    Passenger* temp = new Passenger[pCount + 1];
    for (int i = 0; i < pCount; i++)
        temp[i] = passengers[i];
    temp[pCount] = p;
    delete[] passengers;
    passengers = temp;
    pCount++;
    savePassengers();
    system("color 02");
    cout << "                                      ======================================================\n"
        << "                                                    PASSENGER ADDED SUCCESSFULLY                     \n"
        << "                                      ======================================================\n";
    cout << "\nPassenger ID: " << p.id;
    cout << "\nPress Enter to Continue...";
    cin.get(); cin.get();

}

//========================================================
//       SEARCHING FLIGHT BY FLIGHT NUMBER
// ========================================================

void searchflight() {
    int fno;
	cout << "Enter Flight Number to Search: ";
    cin >> fno;
    for (int i = 0;i < fCount;i++) {
        if (flights[i].flightNo == fno) {
            cout << "                        ================================================\n";
            cout << "                                       Flight   Found\n";
            cout << "                        ================================================\n\n";
            cout << left
                << setw(10) << "Flight No"
                << setw(15) << "Destination"
                << setw(12) << "Date"
                << setw(8) << "Time"
                << setw(8) << "Seats"
                << setw(8) << "Fare per Flight" << endl;
            cout << "------------------------------------------------------------------------------------\n";
            cout << left
                << setw(10) << flights[i].flightNo
                << setw(15) << flights[i].destination
                << setw(12) << flights[i].date
                << setw(8) << flights[i].time
                << setw(8) << flights[i].seats
                << setw(8) << flights[i].fare
                << endl;
            return;
        }

    }
    cout << "                        ================================================\n";
    cout << "                                       Flight  Not  Found\n";
    cout << "                        ================================================\n\n";
    return;
}
//========================================================
//       SEARCHING PASSENGER BY ID
// ========================================================

void searchPassengerbyId() {
	cout << "Enter Passenger ID to Search: ";
	int pid;
	cin >> pid;
    for (int i = 0; i < pCount; i++) {
        if (passengers[i].id == pid) {
			cout << "                        ================================================\n";
            cout << "                                       Passenger Found\n";
			cout << "                        ================================================\n\n";
            cout << "           Name             :              " << passengers[i].name << endl;
            cout << "           ID               :              " << passengers[i].id << endl;
            cout << "           Phone            :              " << passengers[i].phone << endl;
            cout << "           Password         :              " << passengers[i].password << endl << endl;

            return;
        }
    }
    cout << "                        ================================================\n";
    cout << "                                      Passenger Not  Found\n";
    cout << "                        ================================================\n\n";
}
void updatePassenger()
{
    cout << "Enter Passenger ID to Update : ";
    int pid;
    cin >> pid;
    for (int i = 0; i < pCount; i++) {
        if (passengers[i].id == pid) {
            cout << "                        ================================================\n";
            cout << "                                       Passenger Found\n";
            cout << "                        ================================================\n\n";
			cin.ignore();
            cout << "Enter New Full Name: ";
            getline(cin, passengers[i].name);
            cout << "Enter New Password: ";
            cin >> passengers[i].password;
            cout << "Enter New Phone: ";
            cin >> passengers[i].phone;
            savePassengers();
            cout << "\nPassenger Updated Successfully!";
            cout << "\nPress Enter to Continue...";
            cin.get(); cin.get();
            return;
        }
    }
    cout << "                        ================================================\n";
    cout << "                                      Passenger Not  Found\n";
	cout << "                        ================================================\n\n";

}
// =======================================================
//                 ADDING FLIGHT BY ADMIN
//=======================================================
void addFlight() {
    system("cls");
    system("color 09");
    cout << "                                       ======================================================\n"
        << "                                                         FLIGHT ADDITION                \n"
        << "                                       ======================================================\n" << endl;

    // Create a temporary flight object
    Flight f;

    cout << "Flight No: ";
    cin >> f.flightNo;
    cout << "Destination: ";
    cin >> f.destination;
    cout << "Date (DD.MM.YYYY): ";
    cin >> f.date;
    cout << "Departure Time(H:MIN:SEC): ";
    cin >> f.time;
    cout << "Available Seats: ";
    cin >> f.seats;
    cout << "Fare per Seat: ";
    cin >> f.fare;

    // -------------------------------
    // Dynamic memory allocation
    // -------------------------------
    Flight* temp = new Flight[fCount + 1]; // create new array with extra space
    for (int i = 0; i < fCount; i++)
        temp[i] = flights[i];             // copy old flights
    temp[fCount] = f;                     // add new flight at the end
    delete[] flights;                     // free old memory
    flights = temp;                       // point flights to new array
    fCount++;                             // increase flight count

    saveFlights();                        // save flights to file

    cout << "                                      ======================================================\n"
        << "                                                    FLIGHT ADDED SUCCESSFULLY                     \n"
        << "                                      ======================================================\n";
    cout << "\nPress Enter to Continue...";
    cin.get(); cin.get(); // wait for Enter key
}

// =======================================================
//              DELETE FLIGHT BY ADMIN
//=======================================================
void deleteFlight() {
    int fno;
    system("cls");
    system("color 04");
    cout << "                                              ======================================================\n"
        << "                                                               FLIGHT DELETION                 \n"
        << "                                              ======================================================\n" << endl;
    cout << "Enter Flight No: ";
    cin >> fno;

    for (int i = 0; i < fCount; i++) {
        if (flights[i].flightNo == fno) {
            for (int j = i; j < fCount - 1; j++)
                flights[j] = flights[j + 1];
            fCount--;
            saveFlights();
            cout << "\nFlight Deleted!";
            cout << "\nPress Enter to continue...";
            cin.get(); cin.get();
            return;
        }
    }
    cout << "\nFlight Not Found!";
    cout << "\nPress Enter to Continue...";
    cin.get(); cin.get();
}

//============================================
//    CHECKING BOOKINGS
// =====================================
//

void viewTotalBookingsAndReports() {
    ifstream file("bookings.txt");
    Booking b;

    system("cls");
    system("color 0E");

    cout << "                                     ==============================================\n";
    cout << "                                                TOTAL BOOKINGS                       \n";
    cout << "                                     ==============================================\n\n";


    cout << "------------ ALL BOOKINGS ------------\n\n";

    bool anyBooking = false;
    int i = 1;
    int total = 0;
    while (file >> b.bookingID >> b.passengerID >> b.flightNo >> b.fare) {
        anyBooking = true;
        cout << "  Booking no. " << i << endl << endl;
        cout << "Booking ID  : " << b.bookingID << endl;
        cout << "Passenger ID: " << b.passengerID << endl;
        cout << "Flight No   : " << b.flightNo << endl;
        cout << "Fare        : " << b.fare << endl;
        cout << "--------------------------------------\n";
        i++;
        total += b.fare;
    }
    cout << "\n\nTotal amount: " << total << endl;;
    if (!anyBooking) {
        cout << "No bookings found.\n";
    }

    file.close();
    cout << "Please Enter to Continue";
    cin.get();cin.get();
}
//==========================================================
//      FUNCTION FOR CHANGING PASSENGER PASSWORD BY ADMIN
//==========================================================
void changePassengerPassword() {
    int pid;
    string newPass;
    system("cls");
    system("color 08");
    cout << "                                      ======================================================\n"
        << "                                                    CHANGE PASSENGER PASSWORD                  \n"
        << "                                      ======================================================\n" << endl;
    cout << "Enter Passenger ID: ";
    cin >> pid;

    for (int i = 0; i < pCount; i++) {
        if (passengers[i].id == pid) {
            cin.ignore(); // clear buffer
            cout << "Enter New Password for " << passengers[i].name << ": ";
            getline(cin, newPass);

            passengers[i].password = newPass;
            savePassengers();
            cout << "\nPassword changed successfully!";
            cout << "\nPress Enter to continue...";
            cin.get(); cin.get();
            return;
        }
    }

    cout << "\nPassenger Not Found!";
    cout << "\nPress Enter to continue...";
    cin.get(); cin.get();
}


// =======================================================
//                 PASSENGER LOGIN
//=======================================================

bool passengerLogin(int& pid) {
    int id;
    string pass;
    system("cls");
    system("color 0B");

    cout << "                                                     ======================================================\n"
        << "                                                                   Passenger     Login                       \n"
        << "                                                    ======================================================\n";
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pass;

    for (int i = 0; i < pCount; i++) {
        if (passengers[i].id == id && passengers[i].password == pass) {
            pid = id;
            system("color 02");
            cout << "                                    ======================================================\n"
                << "                                                  LOGIN     SUCCESSFULL                  \n"
                << "                                    ======================================================\n" << endl;
            cout << "\nPress Enter to continue...";
            cin.get(); cin.get();
            return true;
        }
    }
    cout << "\nInvalid Username or Password!";
    cout << "\n If you have forgot your password ,you can contact with admin to change it.\n";
    cout << "\nPress Enter to continue...";
    cin.get(); cin.get();
    return false;
}

// =======================================================
//                 ADMIN LOGIN
//=======================================================

bool adminLogin() {
    string u, p, fileUser, filePass;

    ifstream fin("admin.txt");
    if (!fin) {
        cout << "Admin file not found!";
        cin.get(); cin.get();
        return false;
    }
    fin >> fileUser >> filePass;
    fin.close();
    system("color 05");
    system("cls");
    cout << "                                 ======================================================\n"
        << "                                                    ADMIN LOGIN                  \n"
        << "                                 ======================================================\n\n";

    cout << "Admin Username: ";
    cin >> u;
    cout << "Admin Password: ";
    cin >> p;

    if (u == fileUser && p == filePass) {
        cout << "                                    ======================================================\n"
            << "                                                  LOGIN     SUCCESSFULL                  \n"
            << "                                    ======================================================\n" << endl;
        cout << "\nPress Enter to Continue...";
        cin.get(); cin.get();
        return true;
    }
    else {
        cout << "\nInvalid Username or Password!";
        cout << "\nPress Enter to Continue...";
        cin.get(); cin.get();
        return false;
    }
}



// =======================================================
//                 PASSENGER MENU
//=======================================================

void passengerMenu(int pid) {
    int ch;
    do {
        system("cls");
        system("color 04");
        cout << "                                      ======================================================\n"
            << "                                                       PASSENGER MENU                  \n"
            << "                                      ======================================================\n" << endl;
        cout << "1. View Flights\n2. Book Flight\n3. Cancel Booking\n4. My Report\n5. Search Flight by Flight Number\n6.Logout\n";

        do {
            cout << "Enter Choice: ";
            cin >> ch;
            if (ch < 1 || ch>6) {
                cout << "Invalid choice!Enter Again...\n";
            }
        } while (ch < 1 || ch>6);


        switch (ch) {
        case 1:
            showFlights();
            break;
        case 2:
            bookFlight(pid);
            break;
        
        case 3:
            cancelBooking(pid);
            break;
        case 4:
            passengerReport(pid);
            break;
        case 5:
            system("cls");
            system("color F0");
            searchflight();
            cout << "Press Enter to Continue.....";
            cin.get();cin.get();
            break;
        case 6:
            system("color 02");
            cout << "                                       ======================================================\n"
                << "                                                         LOGGED OUT SUCCESSFULLY                \n"
                << "                                       ======================================================\n" << endl;
            cout << "Press Enter to Continue......\n";
            cin.get();  cin.get();
        }
    } while (ch != 6);
}

// =======================================================
//                ADMIN MENU
//=======================================================

void adminMenu() {
    int ch;
    do {
        system("cls");
        system("color 0B");
        cout << "                                       ======================================================\n"
            << "                                                         ADMIN MENU                 \n"
            << "                                       ======================================================\n" << endl;
        cout << "1. View Passengers\n";
        cout << "2. Delete Passenger\n";
        cout << "3. Change Passenger Password\n";
        cout << "4. Add Passenger\n";          
        cout << "5. View Flights\n";
        cout << "6. Add Flight\n";
        cout << "7. Delete Flight\n";
        cout << "8. Change Admin Password\n";
        cout << "9. Check Bookings\n";
		cout << "10. Search Passenger by ID\n";
        cout << "11. Update Passenger \n";
        cout << "12. Logout\n";
        
        do {
            cout << "Enter Choice: ";
            cin >> ch;
            if (ch < 1 || ch>12) {
                cout << "Invalid choice!Enter Again...\n";
            }
        } while (ch < 1 || ch>12);
      

        switch (ch) {
        case 1:
            viewPassengers();
            break;
        case 2: 
            deletePassenger();
            break;
        case 3:
            changePassengerPassword(); 
            break;
        case 4: 
            adminAddPassenger(); 
            break;
        case 5: 
            
            showFlights();
            break;
        case 6: 
            addFlight(); 
            break;
        case 7:
            deleteFlight(); 
            break;
        case 8: 
            changeAdminPassword(); 
            break;
        case 9:
            viewTotalBookingsAndReports();
            break;
        case 10:
			system("cls");
            system("color F0");
			searchPassengerbyId();
			cout << "\nPress Enter to Continue...";
			cin.get(); cin.get();
            break;
        case 11:
			system("cls");
            system("color 05");
			updatePassenger();
			
        case 12:
            system("color 02");
            cout << "                                       ======================================================\n"
                << "                                                         LOGGED OUT SUCCESSFULLY                \n"
                << "                                       ======================================================\n" << endl;
            cout << "Press Enter to Continue......\n";
            cin.get();  cin.get();
        }
    } while (ch != 12);
}



// =======================================================
//                 MAIN BODY
//=======================================================

int main() {
    loadPassengers();
    loadFlights();

    char ch;int pid;
    system("cls");
    system("color 04");

    cout << "                                 **************************************************" << endl;
    cout << "                                 *                                                *" << endl;
    cout << "                                 *           PAKISTAN     INTERNATIONAL           *" << endl;
    cout << "                                 *             AIRLINE   MANAGEMENT               *" << endl;
    cout << "                                 *                   SYSTEM                       *" << endl;
    cout << "                                 **************************************************" << endl << endl << endl;
    cout << "Press Enter to Continue....";
    cin.get();
    do {
       
        system("cls");
        system("color 0C");
        cout << "                                       ======================================================\n"
            << "                                                           MIAN MENU                \n"
            << "                                       ======================================================\n" << endl << endl;
        
        cout << "1. Passenger Registration\n"
           <<"2. Passenger Login\n"
          <<"3. Admin Login\n4.Exit\n";
        do {
            cout << "Enter Choice: ";
            cin >> ch;
            if (ch != '1'&&ch!='2'&& ch != '3' && ch != '4') {
                cout << "Invalid choice!Enter Again...\n";
            }
        } while (ch != '1' && ch != '2' && ch != '3' && ch != '4');
        switch (ch) {
        case '1':
            registerPassenger();
            break; 
        case '2':
            if (passengerLogin(pid))
                passengerMenu(pid); 
            break;
        case '3':
            if (adminLogin())
                adminMenu();
            break;
            case '4':
                system("color 02");
                cout << "                                       ======================================================\n"
                    << "                                                         EXITED SUCCESSFULLY                \n"
                    << "                                       ======================================================\n" << endl;
                
        }
    } while (ch != '4');
    delete[] passengers;
    delete[] flights;
    passengers = nullptr;
    flights=nullptr;
    return 0;
}

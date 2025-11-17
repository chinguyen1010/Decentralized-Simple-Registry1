#include "Registry.h" // Access to SimpleRegistry, Record, and the method declarations.
#include <iostream>
#include <chrono>
#include <limits>
#include <exception>

using namespace std;

// Helper: get current UNIX timestamp
uint64_t currentUnixTime() {
    using namespace chrono;
    return static_cast<uint64_t>(
        duration_cast<seconds>(system_clock::now().time_since_epoch()).count()
    );
}

// Helper: pretty-print a record
void printRecord(const Record& r) {
    cout << "ID: " << r.id << "\n"
         << "Owner: " << r.owner << "\n"
         << "Data: " << r.data << "\n"
         << "Timestamp: " << r.timestamp << "\n";
}

int main() {

    SimpleRegistry registry;

    while (true) {
        cout << "\n=== Decentralized Simple Registry (C++ Demo) ===\n";
        cout << "1) Create record\n";
        cout << "2) Get record\n";
        cout << "3) List all IDs\n";
        cout << "4) Exit\n";
        cout << "Choose an option: ";

        int option;
        if (!(cin >> option)) {
            cerr << "Invalid input. Exiting.\n";
            break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // --- Create a record ---
        if (option == 1) {
            string id, data, owner;

            cout << "Enter unique ID: ";
            getline(cin, id);

            cout << "Enter data: ";
            getline(cin, data);

            cout << "Enter owner: ";
            getline(cin, owner);

            try {
                registry.createRecord(id, data, owner, currentUnixTime());
                cout << "Record created successfully.\n";
            } 
            catch (const exception& e) {
                cerr << "Error: " << e.what() << "\n";
            }
        }

        // --- Get a record ---
        else if (option == 2) {
            string id;
            cout << "Enter ID: ";
            getline(cin, id);

            try {
                const Record& r = registry.getRecord(id);
                printRecord(r);
            } 
            catch (const exception& e) {
                cerr << "Error: " << e.what() << "\n";
            }
        }

        // --- List all IDs ---
        else if (option == 3) {
            auto ids = registry.listIds();
            if (ids.empty()) {
                cout << "No records exist.\n";
            } else {
                cout << "Existing IDs:\n";
                for (const auto& id : ids) cout << " - " << id << "\n";
            }
        }

        // --- Exit ---
        else if (option == 4) {
            cout << "Exiting.\n";
            break;
        }

        else {
            cout << "Unknown option.\n";
        }
    }

    return 0;
}
#include "Registry.h" //access to SimpleRegistry, Record, and the method declarations.
#include <iostream>
#include <chrono>     // for generating timestamps
#include <limits>     // for clearing input buffer
#include <exception> 


using namespace std;

//Helper function currentUnixTime: Gets current time in UNIX timestamp format
uint64_t currentUnixTime() {
    using namespace chrono;
    return static_cast<uint64_t>(
        duration_cast<seconds>(system_clock::now().time_since_epoch()).count()
    );
}

 //Helper function printRecord: print the fields inside a Record struct to see what the user see what was stored
void printRecord(const Record& r) {
    cout << "ID: " << r.id << "\n"
         << "Owner: " << r.owner << "\n"
         << "Data: " << r.data << "\n"
         << "Timestamp: " << r.timestamp << "\n";
}

int main() {
    // Create an instance of SimpleRegistry already contains the "mapping" (unordered_map<string, Record>).
    SimpleRegistry registry;

    while (true) {
        cout << "\n=== Decentralized Simple Registry (C++ Demo) ===\n";
        cout << "1) Create record\n";
        cout << "2) Get record\n";
        cout << "3) List all IDs\n";
        cout << "4) Exit\n";
        cout << "Choose an option: ";

        int option;

        // Read the user input for the menu choice.
        // If input is not a valid integer, exit.
        if (!(cin >> option)) {
            cerr << "Invalid input. Exiting.\n";
            break;
        }

        // Clear leftover characters in the input buffer.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // --- 1: Create a new record ---
        if (option == 1) {
            string id, data, owner;

            cout << "Enter unique ID: ";
            getline(cin, id);

            cout << "Enter data (text): ";
            getline(cin, data);

            cout << "Enter owner (e.g., 0xYourAddress): ";
            getline(cin, owner);

            /**
             * implement registry.createRecord() from Registry.cpp.
             * - Validates ID is non-empty
             * - Checks ID is not already used
             * - Creates a Record struct
             * - Stores it in the mapping
             
             * createRecord() can fail  → throws runtime_error
             */
            try {
                registry.createRecord(id, data, owner, currentUnixTime());
                cout << "Record created successfully.\n"; //no problem occur -> success
            } catch (const exception& e) {
              // createRecord() can fail  → throws runtime_error (like empty ID or duplicate ID)
              // The catch block receives that exception, and prints the error message so the program does not crash.
                cerr << "Error: " << e.what() << "\n";
            }

        // --- OPTION 2: Retrieve a record by ID ---
        } else if (option == 2) {
            string id;
            cout << "Enter ID: ";
            getline(cin, id);

            try {
                /**
                 * registry.getRecord(id):
                 * 
                 * - Looks in the mapping (unordered_map)
                 * - reject if no record exists
                 */
                //getRecord() can fail → throws runtime_error
                const Record& r = registry.getRecord(id);
                printRecord(r);
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << "\n";
            }

        // --- OPTION 3: List all record IDs ---
        } else if (option == 3) {

            /**
             * registry.listIds():
             * - Loops through the mapping keys
             * - Returns a vector<string> of all IDs
             */
            auto ids = registry.listIds();

            if (ids.empty()) {
                cout << "No records exist.\n";
            } else {
                cout << "Existing IDs:\n";
                for (const auto& id : ids) {
                    cout << " - " << id << "\n";
                }
            }

        // --- OPTION 4: Exit the program ---
        } else if (option == 4) {
            cout << "Exiting.\n";
            break;

        // --- Unknown menu choice ---
        } else {
            cout << "Unknown option. Try again.\n";
        }
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include "DHT.h"
using namespace std;

int main() 
{
    int idSpace = 0;
    cout << "Enter the Identifier Space: ";
    cin >> idSpace;
    idSpace = pow(2, idSpace);
    Machine* allMachines = new Machine[idSpace];

    int num = 0;
    cout << "Enter the Number of Machines: ";
    cin >> num;

    int random;
    int count = 0;
    srand(time(0));

    while (1)
    {
	    random = rand() % idSpace;
	    if (allMachines[random].isPrimaryMachine == true)
		    continue;
	    else
	    {
		    allMachines[random].isPrimaryMachine = true;
		    count++;
	    }

	    if (count >= num)
		    break;
    }

    char mId;
    char choice = ' ';
    int j = 1;

    while (1)
    {
	    cout << "Do you want to alot Machine Id to the machines? [y/n]: ";
	    cin >> choice;
	    if (toupper(choice) == 'Y')
	    {
		    for (int i = 0; i < idSpace; i++)
		    {
			    if (allMachines[i].isPrimaryMachine == true)
			    {
				    cout << "Enter Machine Id # " << j++ << " (as integer): ";
				    cin >> mId;
				    allMachines[i].machineId = mId;
			    }
			    else
				    continue;
		    }

		    break;
	    }
	    else
	    {
		    cout << "Alloting Machine Id's...  " << endl;
		    for (int i = 0; i < idSpace; i++)
		    {
			    if (allMachines[i].isPrimaryMachine == true)
				    allMachines[i].machineId = to_string(i);
			    
			    else
				    continue;   
		    }

		    cout << "Machine Id's Alloted\n";
	    }

	    break;
    }

    CircularLinkedList c1;
    for (int i = 0; i < idSpace; i++)
    {
	    c1.insertAtEnd(&allMachines[i]);
    }

   // c1.display();

    CircularLinkedList c2;
    for (int i = 0; i < idSpace; i++)
    {
        if (allMachines[i].isPrimaryMachine == true)
        {
            c2.insertAtEnd(&allMachines[i]);
        }
    }

    c2.display();

    DataPair inputData;
    char choice1 = ' ';
    int choice2 = 0;

    while (1)
    {
        cout << "Enter 'n' to exit right now or Press any key for the menu." << endl;
        cin >> choice1;

        if (choice1 == 'n')
            return 0;
        else
        {
            cout << "Press 1 to insert Key Value Pair" << endl;
            cout << "Press 2 to search a Key's Value" << endl;
            cout << "Press 3 to remove data" << endl;
            cout << "Press 4 to print the routing table of any machine" << endl;
            cout << "Press 5 to print the AVL Tree of any machine" << endl;
            cout << "Press 6 to Add a new Machine" << endl;
            cout << "Press 7 to remove any machine" << endl;
            
            cin >> choice2;

            Machine obj;

            if (choice2 == 1)
            {
                cout << "Enter your Key (In Integer): " << endl;
                cin >> inputData.key;

                cout << "Enter its corresponding Value (In String): " << endl;
                cin >> inputData.value;

                string mID;
                cout << "Enter the Machine ID to start the insertion process: " << endl;
                cin >> mID;

                c2.insertInTree(inputData, mID);
            }

            else if (choice2 == 2)
            {
                int key = 0;

                cout << "Enter your Key (In Integer): " << endl;
                cin >> key;

                string mID;
                cout << "Enter the Machine ID to start the insertion process: " << endl;
                cin >> mID;

                c1.search(key, mID);
            }

            else if (choice2 == 3)
            {
                continue;
            }
            
            else if (choice2 == 4)
            {
                string mID;

                cout << "Enter Machine ID of the Machine you want to see the routing table of" << endl;
                cin >> mID;

                DoubleList d1 = c2.getFTP();
                
                int serialNum = c2.getSerialNumber(mID);

                d1.printAll();
            }

            else if (choice2 == 5)
            {
                string mID;

                cout << "Enter Machine ID of the Machine you want to see the routing table of" << endl;
                cin >> mID;

                c2.displayAVLTrees(mID);
            }

            else if (choice2 == 6)
            {
                obj.setMachineID(to_string(obj.getSerialNum()));
                c2.insertAtEnd(&obj);
            }

            else
            {
                c2.del();
            }
        }
    }
 
    return 0;
}

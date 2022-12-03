/*
@Varun Malpani
S20210020329
Banking management system
*/
#include <bits/stdc++.h>
using namespace std;

// base class
class account
{
    int acno;
    char name[50];
    int deposit;
    char type;

public:
    account()
    {
    }
    void createAccount();
    void showAccount() const;
    void modifyAccount();
    void depositMOney(int);
    void withdrawMoney(int);
    void report() const;
    int retacno() const;
    int retdeposit() const;
    char rettype() const;
};

// function to create account
void account::createAccount()
{
    cout << "\nEnter The account No. : ";
    cin >> acno;
    cout << "\n\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter Type of The account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\nEnter The Initial amount : ";
    cin >> deposit;
    cout << "\n\n\nAccount Created..";
}

// function to show account information
void account::showAccount() const
{
    cout << "\nAccount No. : " << acno;
    cout << "\nAccount Holder Name : ";
    cout << name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance amount : " << deposit;
}

// function to modify account information
void account::modifyAccount()
{
    cout << "\nAccount No. : " << acno;
    cout << "\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance amount : ";
    cin >> deposit;
}

// function to deposit amount
void account::depositMOney(int x)
{
    deposit += x;
}

// function to withdraw money
void account::withdrawMoney(int x)
{
    deposit -= x;
}

void account::report() const
{
    cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::retacno() const
{
    return acno;
}

int account::retdeposit() const
{
    return deposit;
}

char account::rettype() const
{
    return type;
}

void writeAccount();
void displayAcc(int);
void modifyAccount(int);
void deleteAccount(int);
void displayAll();
void depositmoney(int, int);
void writeAccount()
// file system functions
{
    account ac;
    ofstream outFile;
    outFile.open("acc.dat", ios::binary | ios::app);
    ac.createAccount();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
    outFile.close();
}

// function to open a file and display account information
void displayAcc(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("acc.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\nBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            ac.showAccount();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccount number does not exist";
}

// function to open a file and modify account info
void modifyAccount(int n)
{
    bool found = false;
    account ac;
    fstream File;
    File.open("acc.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.retacno() == n)
        {
            ac.showAccount();
            cout << "\n\nEnter The New Details of account" << endl;
            ac.modifyAccount();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}

// function to delete an account record
void deleteAccount(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("acc.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() != n)
        {
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("acc.dat");
    rename("Temp.dat", "acc.dat");
    cout << "\n\n\tRecord Deleted ..";
}

void displayAll()
{
    account ac;
    ifstream inFile;
    inFile.open("acc.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

void depositmoney(int n, int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("acc.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.retacno() == n)
        {
            ac.showAccount();
            if (option == 1)
            {
                cout << "\n\n\tTO DEPOSITE AMOUNT ";
                cout << "\n\nEnter The amount to be deposited:";
                cin >> amt;
                ac.depositMOney(amt);
            }
            if (option == 2)
            {
                cout << "\n\n\tTo withdraw AMOUNT ";
                cout << "\n\nEnter The amount to be withdraw:";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
                    cout << "Insufficient balance";
                else
                    ac.withdrawMoney(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}

void Project()
{

    // change cmd color
    system("Color 8F ");
    int opt;
    system("cls");
    cout << "//***************************************************************//" << endl;
    cout << "\t\tBANNK MANAGEMENT SYSTEM" << endl;
    cout << "//***************************************************************//" << endl;

    char ch;
    int num;

    // menu
    while (ch != '8')

    {

        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        cout << "\n\n\t02. DEPOSIT AMOUNT";
        cout << "\n\n\t03. WITHDRAWMoney AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\t08. EXIT";
        cout << "\n\n\tSelect Your Option (1-8) ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            writeAccount();
            break;
        case '2':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            depositmoney(num, 1);
            break;
        case '3':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            depositmoney(num, 2);
            break;
        case '4':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            displayAcc(num);
            break;
        case '5':
            displayAll();
            break;
        case '6':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            deleteAccount(num);
            break;
        case '7':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            modifyAccount(num);
            break;
        case '8':
            cout << "\n\n\tThanks for using bank managemnt system";
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();
    }
}

int main()
{
    // main function call
    Project();
    return 0;
}

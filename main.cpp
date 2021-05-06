// Student ID #21297899
// Mim Lennig
//  main.cpp
//  Assign.2
//  COEN 244
//  Created by Miriam Lennig on 2016-02-12.
//  Copyright © 2016 Miriam Lennig. All rights reserved.
//
// Bank teller simulation where user can request one of six account actions, or "end," which means that there are no more people in line.
// Accepts account requests and puts them into a service request queue until and end command is encountered.
// At this point it beings processing the requests in the service request queue until the queue is empty.


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;


class Account {     //This class describes bank accounts
private:
    string first_name;  //First name
    string last_name;   //Last name
    int ID;                    //Account number
    double balance;     //Account balance
    
public:
    Account();
    Account (string fname, string lname, double amount);
    string rand_fname ();
    string rand_lname();
    int rand_ID ();
    double rand_balance();
    void printAccount();
    string get_fname();
    string get_lname();
    int get_ID();
    double get_balance();
    void destroyAccount();
    void deposit(double amount);
    int withdrawal(double amount);
    void printBalance();
  
};
void Account::printBalance(){
    //print balance of account
    cout << "Balance: " << balance << endl;
}
double Account::get_balance(){
    return balance;
}

string Account::get_fname(){
    return first_name;
}

string Account::get_lname(){
    return last_name;
}

int Account::get_ID(){
    return ID;
}

string Account::rand_fname(){
    //returns a random first name
    vector<string> firstName = {"Jim", "James", "Janet", "Kill" , "Jessica", "Buffy", "Willow", "Tara", "Xander", "Angel", "Lana", "Spike", "Jennifer", "Regina", "Emma", "Rupert"};
    
    int ifirst;
    
    ifirst = rand() % firstName.size();
    return firstName[ifirst];
    
}

string Account::rand_lname(){
    //returns a random last name
    vector<string> lastName  = {"Quinn", "Quicksilver", "Hargrave", "Grave", "Jones", "Summers", "Rosenberg", "Harris", "Vampire", "Maclay", "Parrilla", "Marsters", "Morrison", "Mills", "Swan", "Giles"};
    
    int ilast;
    
    ilast = rand() % lastName.size();
    return lastName[ilast];
}

int Account::rand_ID(){
    //returns a random account number
    return (rand() % 1000000) + 1000000;
}

double Account::rand_balance(){
    //returns a random account balance
    return (rand() % 1000000000)/10000.;
}

Account::Account(){
    //This is the default constructor, it assigns random values for first name, last name, account number, account balance
    first_name = rand_fname();
    last_name = rand_lname();
    ID = rand_ID();
    balance = rand_balance();
}

Account::Account(string firstname, string lastname, double quantity){
    //This constructor is used to create an account with a known first name, last name, and initial deposit.
    //The account number is assigned a random value.
    first_name = firstname;
    last_name = lastname;
    ID = rand_ID();
    balance = quantity;
}


void Account::printAccount(){
    cout << " (Name: " << first_name <<  " " << last_name << ",  ID: " << ID << ",  Balance: " << balance << ")" << endl;
}

void printAccounts (map <int, Account> Bank){
    //Print all of the accounts in the Bank
    for (map<int, Account>::iterator iter = Bank.begin(); iter != Bank.end(); iter++)
        (iter->second).printAccount();
}

void populateAccounts (map <int, Account>& Bank){
    //Populate the bank with random accounts
    int nRandomAccounts = rand() % 20 + 5;
    for (int i = 0; i < nRandomAccounts; i++) {
        Account account = *new Account();
        Bank[account.get_ID()] = account;
    }
}

class Request {     //This class encapsulates a request
public:
    string fname;
    string lname;
    int ID;
    double amount;
    string action;

    Request();
    Request(string firstname, string lastname, int accountNum, double quantity, string command);
};

Request::Request(){     //Default constructor
}

Request::Request(string firstname, string lastname, int accountNum, double quantity, string command){
    //Constructor which initializes first name, last name, account number, amount deposited or withdrawn, and request
    fname = firstname;
    lname = lastname;
    ID = accountNum;
    amount = quantity;
    action = command;
}


void Account::deposit(double amount){
    balance += amount;
}

int Account::withdrawal(double amount){
    //If possible perform a withdrawal and return 0
    //Otherwise, return 1
    if(amount > balance)
       return 1;
    balance -= amount;
    return 0;
}


int main() {
    srand(int(time(NULL)));     //Initialize random number generator with random seed
    
    map <int, Account> Bank;    //This is the container that holds the accounts
    
    populateAccounts(Bank);     //Create random accounts and put them in Bank
    
    printAccounts(Bank);        //Print out information for all the accounts in Bank
    
    queue <Request> requestQueue;       //Create a container for service requests
    
    string command;     //Service request action
    string fname;          //First name
    string lname;          //Last name
    int ID = 0;             //Initialize account number to 0
    double amount = 0;  //Initialize amount to 0
    
    while(true){
        cout << "Command (create, deposit, withdraw, close, balance, nothing, end): ";
        cin >> command;
        
        if (command == "end")
            //No more people waiting in the teller line
            break;
        
        cout << "First name: ";
        cin >> fname;
        cout << "Last name: ";
        cin >> lname;

        if (command != "create") {
            //Prompt for account number
            cout << "Account #: ";
            cin >> ID;
            while(!cin) {
                //Detect nonnumeric input and reprompt
                cout << "Illegal input." << endl;
                cin.clear();
                cin.ignore();
                cout << "Account #: ";
                cin >> ID;
            }
        }
        
        if((command == "withdraw") || (command == "deposit") || (command == "create")){
            //Promp for amount to withdraw or deposit
            cout << "Amount: ";
            cin >> amount;
            while(!cin) {
                //Detect nonnumeric input and reprompt
                cout << "Illegal input." << endl;
                cin.clear();
                cin.ignore();
                cout << "Amount: ";
                cin >> amount;
            }
        }
        
        //Use data collected above to populat a new Request object and add it to the request queue
        requestQueue.push(*new Request(fname, lname, ID, amount, command));
    }
    
    Request r;
    while(requestQueue.size()){
        //Pop a request off the request queue and store it in r
        r = requestQueue.front();
        requestQueue.pop();
        
        //Process request r
        if (r.action == "create"){
            //Check if amount is negative
            if (r.amount < 0) {
                cout << fname << " " << lname << " cannot create an account with a negative amount. No action taken." << endl;
                continue;
            }
            //Create a new account using information from service request r
            Account a = *new Account(r.fname, r.lname, r.amount);
            if(!Bank.count(r.ID)){
                //Check if acount number already exists in Bank
                cout << "Collision! Regenerating account." << endl;
                //Regenerate account with a unique account number
                Account a = *new Account(r.fname, r.lname, r.amount);
            }
            Bank[r.ID] = a;     //Put account into Bank
        }
        //Check if request name matches account name
        else if((r.fname != Bank[r.ID].get_fname()) || (r.lname != Bank[r.ID].get_lname())){
            //Request name does not match account name
            cout << "Account # " << r.ID << " name does not match. No action taken. " << endl;
            continue;
        }
       //Check if account number exists in Bank
        else if (!Bank.count(r.ID)){
            //Account number does not exist in Bank
            cout << "Account # " << r.ID << " does not exist. No action taken." << endl;
            continue;
        }
        //Check if action is legal
        else if((r.action != "deposit") && (r.action != "withdraw") && (r.action != "close") && (r.action != "balance") && (r.action != "nothing")){
            //Illegal service request
            cout << "Account # " << r.ID << " command " << r.action << " does not exist. No action taken. " << endl;
            continue;
        }
        //Check if amount is positive
        else if(r.amount < 0) {
            //Amount is negative
            cout << "Account # "<< r.ID << " cannot process a negative amount. No action taken." << endl;
            continue;
        }
        if (r.action == "deposit"){
            Bank[r.ID].deposit(r.amount);
        }
        
        if(r.action == "withdraw"){
            //Check if there are sufficient funds for the requested withdrawal
            if (r.amount <= Bank[r.ID].get_balance())
                Bank[r.ID].withdrawal(r.amount);
            else
                //Insufficient funds to process withdrawal
                cout << "Account #: " << r.ID << " has insufficient funds for a $" << r.amount << " withdrawal. No action taken." << endl;
        }
        
        if(r.action == "close"){
            Bank.erase(r.ID);
        }
        
        if((r.action == "balance") || (r.action == "nothing")){
            Bank[r.ID].printBalance();
        }
        
    }
    
    printAccounts(Bank);
    
}

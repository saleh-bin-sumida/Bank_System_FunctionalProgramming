#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

const string ClientsFileName = "F:\\Visual Studio Projects\\Bank_ATM\\Clients.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

sClient CurrentClient;

void ShowATM_MainMenue();
void ShowQuickWithdrawScreen();
void Login();

// ----------- Handle File
vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

//--------------------------

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, vector <sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
            return true;
        }

    }
    return false;
}

string ReadAccountNumber()
{
    string A;
    cout << "Enter Account Number? ";
    cin >> A;
    return A;
}

string ReadPinCode()
{
    string A;
    cout << "Enter PinCode? ";
    cin >> A;
    return A;
}

// ---------------------- Quick Withdraw --------------------

short ReadQuckWithdrawOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void DoQuickWithdraw(short Amount)
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    char answer;

    cout << "\nAre u sure u want to do this transaction y/n: \n";
    cin >> answer;

    if (answer == 'y' || answer == 'Y')
    {
        if (Amount > CurrentClient.AccountBalance)
            cout << "The Amount exceeds ur balance, Make another choice.\n";
        else
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == CurrentClient.AccountNumber)
                {
                    C.AccountBalance -= Amount;
                    CurrentClient = C;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "done Successfully. Your Balance right now is : " << CurrentClient.AccountBalance << "\n\n";
        }

    }
}

void GoBackToQuickWithdrawMenue()
{
    cout << "Press Any Key to go back to ATM Main Menue...";
    system("pause>0");
    ShowQuickWithdrawScreen();
}

void PerfromQuickWithdrawOption(short Option)
{
    switch (Option)
    {
    case 1:
    {
        system("cls");
        DoQuickWithdraw(20);
        GoBackToQuickWithdrawMenue();
        break;
    }
    case 2:
    {
        system("cls");
        DoQuickWithdraw(50);
        GoBackToQuickWithdrawMenue();
        break;
    }
    case 3:
    {
        system("cls");
        DoQuickWithdraw(100);
        GoBackToQuickWithdrawMenue();
        break;
    }
    case 4:
    {
        system("cls");
        DoQuickWithdraw(200);
        GoBackToQuickWithdrawMenue();
        break;
    }
    case 5:
    {
        system("cls");
        DoQuickWithdraw(400);
        GoBackToQuickWithdrawMenue();
        break;
    }
    case 6:
    {
        system("cls");
        DoQuickWithdraw(600);
        GoBackToQuickWithdrawMenue();
        break;
    }
    case 7:
    {
        system("cls");
        DoQuickWithdraw(800);
        GoBackToQuickWithdrawMenue();
        break;
    }
    case 8:
    {
        system("cls");
        DoQuickWithdraw(1000);
        GoBackToQuickWithdrawMenue();
        break;
    }
    case 9:
    {
        system("cls");
        ShowATM_MainMenue();
        break;
    }
    }
}

void ShowQuickWithdrawScreen()
{
    system("cls");
    cout << "============================================\n";
    cout << "\t\t Quick Withdarw\n";
    cout << "============================================\n";

    cout << "[1] 20              [2] 50\n";
    cout << "[3] 100             [4] 200\n";
    cout << "[5] 400             [6] 600\n";
    cout << "[7] 800             [8] 1000\n";
    cout << "[9] Exit\n";
    cout << "============================================\n";
    cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;

    PerfromQuickWithdrawOption(ReadQuckWithdrawOption());

}

// ----------------------- Normal Withdraw --------------------

void ShowNormalWithdrawScreen()
{
    cout << "---------------------\n";
    cout << "   Nomral Withdraw\n";
    cout << "---------------------\n\n";

    int Amount = 1;

    while (Amount % 5 != 0)
    {
        cout << "enter amount multiple of 5`s : ";
        cin >> Amount;
    }

    DoQuickWithdraw(Amount);
}

// --------- Deposit Screen -------------

void DoDeposit(int Amount)
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    char answer;

    cout << "\nAre u sure u want to do this transaction y/n: \n";
    cin >> answer;

    if (answer == 'y' || answer == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == CurrentClient.AccountNumber)
            {
                C.AccountBalance += Amount;
                CurrentClient = C;
            }
        }

        SaveCleintsDataToFile(ClientsFileName, vClients);

        cout << "done Successfully. Your Balance right now is : " << CurrentClient.AccountBalance << "\n\n";
    }

}

void ShowDepositScreen()
{
    cout << "---------------------\n";
    cout << "      Deposit\n";
    cout << "---------------------\n\n";

    int Amount = -11;
    while (Amount < 0)
    {
        cout << "Enter A postive Amount: ";
        cin >> Amount;
    }

    DoDeposit(Amount);
}

// ----------- check balance: 

void ShowCheckBalance()
{
    cout << "Your Balance is : " << CurrentClient.AccountBalance << "\n\n";

}

// ============================== Main ATM Menue

enum enATM_MainMenueOptions { enQuickWithdraw = 1, enNormalWithdraw = 2, enDeposit = 3, enCheckBalance = 4, enLogout = 5 };

short ReadATM_MainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void GoBackToATM_MainMenue()
{
    cout << "Press Any Key to go back to ATM Main Menue...";
    system("pause>0");
    ShowATM_MainMenue();
}

void PerfromATM_MainMenueOption(enATM_MainMenueOptions Option)
{
    switch (Option)
    {
    case enATM_MainMenueOptions::enQuickWithdraw:
    {
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToATM_MainMenue();
        break;
    }
    case enATM_MainMenueOptions::enNormalWithdraw:
    {
        system("cls");
        ShowNormalWithdrawScreen();
        GoBackToATM_MainMenue();
        break;
    }
    case enATM_MainMenueOptions::enDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToATM_MainMenue();
        break;
    }
    case enATM_MainMenueOptions::enCheckBalance:
    {
        system("cls");
        ShowCheckBalance();
        GoBackToATM_MainMenue();
        break;
    }
    case enATM_MainMenueOptions::enLogout:
    {
        system("cls");
        Login();
        break;
    }
    }
}


void ShowATM_MainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menu Screene \n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal WithDraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n\n";


    PerfromATM_MainMenueOption((enATM_MainMenueOptions)ReadATM_MainMenueOption());
}


void Login()
{
    system("cls");

    cout << "\n_____________________________________________________\n\n";
    cout << "\tLogin Screen";
    cout << "\n_____________________________________________________\n\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    string AccountNumber = ReadAccountNumber();
    string PinCode = ReadPinCode();

    while (!FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, vClients, CurrentClient))
    {
        cout << "Wrong AccouontName/ PinCode!!\n\n";
        AccountNumber = ReadAccountNumber();
        PinCode = ReadPinCode();
    }

    ShowATM_MainMenue();
}

int main()
{
    Login();
}


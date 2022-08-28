#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <iomanip>
#include <unistd.h>
using namespace std;

typedef struct data
{
    ifstream read;
    int num;
}check;

class Bank_account
{
private:
    char name[30];
    char gaurdian[30];
    string accountNumber;
    char phoneNumber[10];
    static char ifsc[15];
    char dob[10];
    char address[100];
    char email[50];
    string balance;

public:
    Bank_account();
private:
    void insertion();
    string AccountNoGenerator();
    double checkAccount(double);
    void display(string);
    check locate(string);
    void credit(string,string);
    void withdraw(string,string);
    void transaction();
    int valid(string);
    void correction();
    void deletion(string, ifstream &, ifstream &);
    void update(int, int, ifstream &, ofstream &, string);
    void backup();
    void deletion_backup(string, ifstream &, ifstream &);
    void transfer();
    double checkBalance(string);
    void updateRequest();
    void correctionR(string ,string, int);
    void updateR(int, int, ifstream &, ofstream &, string);
    void deleteRequest(string acc);
};
char Bank_account ::ifsc[15] = "20BCS1112";

check Bank_account ::locate(string account)
{
    string ch;
    check obj;
    obj.read.open("Bank.txt");

    while(!obj.read.eof())
    {   
        getline(obj.read,ch);
        if(ch == account)
        {
            obj.num=1;
            return obj;
        }
    }

    obj.num=0;
    return obj;
}
void Bank_account ::transfer()
{
    string from,to;
    check obj,obj2;
    string amount;
    int res;

    cout<<"\n\n\t\t\t\t\t\tEnter Account Number From You Want To Transfer Amount : ";
    cin>>from;
    obj = locate(from);
    
    if(obj.num==1)
    {
        cout<<"\n\n\t\t\t\t\t\tEnetr Account Number To You Want To Transfer Amount : ";
        cin>>to;
        obj2 = locate(to);    

        if(obj.num==1)
        {
            while(1)
            {
                cout<<"\n\n\t\t\t\t\t\tEnter Amount You Want To Transfer : ";
                cin>>amount;

                res = valid(amount);

                if(res == 0)
                {
                    cout<<"\n\n\t\t\t\t\t\tInvlid Amount !!!";
                    continue;
                }
                break;
            }

            withdraw(from,amount);
            credit(to,amount);
        }
        else
        {
            system("cls");
            cout<<"\n\n\t\t\t\t\t\tAccount Not Found !!!";
            cout<<"\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
        }
    }

    else
    {
        system("cls");
        cout<<"\n\n\t\t\t\t\t\tAccount Not Found !!!";
        cout<<"\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
        getch();
    }


}
Bank_account ::Bank_account()
{
    int choice;
    string acc;

    while (1)
    {
        system("cls");
        system("COLOR F0");
        cout << endl
             << "\t\t\t\t\t\t1.Create New Account\n\t\t\t\t\t\t2.Do Transaction" << endl;
        cout << "\t\t\t\t\t\t3.Correction\n\t\t\t\t\t\t4.Deletion Existing Account" << endl;
        cout << "\t\t\t\t\t\t5.Display Account Details\n\t\t\t\t\t\t6.Display Full list\n\t\t\t\t\t\t7.BackUp Account\n";
        cout << "\t\t\t\t\t\t8.Transfer Money\n\t\t\t\t\t\t9.Update Request\n\n\t\t\t\t\t\t10.Exit";
        cout << "\n\n\t\t\t\t\t\tEnter Your Choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("COLOR F1");
            insertion();
            break;
        }
        case 2:
        {
            system("COLOR F4");
            transaction();
            break;
        }
        case 3:
        {
            system("COLOR F2");
            correction();
            break;
        }
        case 4:
        {
            system("COLOR F4");
            system("cls");
            string del;
            ifstream out("Bank.txt");
            ifstream out2("Bank.txt");
            cout << "\n\n\t\t\t\t\t\tEnter Account Number To Delete Account : ";
            cin >> del;
            deletion(del, out, out2);
            break;
        }
        case 5:
        {
            system("COLOR F5");
            system("cls");
            cout << "\n\n\t\t\t\t\t\tEnter Account Number : ";
            cin >> acc;
            display(acc);
            cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue....";
            getch();
            system("cls");
            break;
        }
        case 6:
        {
            system("COLOR F0");
            ifstream read("Bank.txt");
            while(!read.eof())
            {
                getline(read,acc);
                if(acc == "?")
                {
                    getline(read,acc);
                    display(acc);                
                }
            }

            cout<<"\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
            system("cls");
            break;
        }
        case 7:
        {
            backup();
            break;
        }
        case 8:
        {
            system("COLOR F0");
            system("cls");
            transfer();
            break;
        }
        case 9:
        {
            updateRequest();
            break;
        }
        case 10:
        {
            system("cls");
            cout << "\n\n\n\n\n\t\t\t\t\t\tThank You";
            cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
            choice = -1;
            break;
        }
        default:
        {
            cout << "Invalid Input!!";
            system("cls");
        }
        }
        if (choice == -1)
        {
            system("cls");
            break;
        }
    }
}
void Bank_account ::backup()
{
    string account, phone, ch, ch2;
    int flag = 0, res = 0;
    ifstream read("backup.txt");
    ifstream read2("backup.txt");
    ofstream write("Bank.txt", ios::app);

    fflush(stdin);
    while (1)
    {
        cout << "\n\n\t\t\t\t\t\tEnter Account Number : ";
        getline(cin, account);

        res = valid(account);

        if (res == 0)
        {
            cout << "\n\n\t\t\t\t\t\tInvalid Input";
            continue;
        }
        break;
    }

    while (1)
    {
        cout << "\n\n\t\t\t\t\t\tEnter Phone Number : ";
        getline(cin, phone);

        res = valid(phone);

        if (phone.length() != 10)
        {
            res = 0;
        }

        if (res == 0)
        {
            cout << "\n\n\t\t\t\t\t\tInvalid Input !!!";
            continue;
        }
        break;
    }

    getline(read, ch);

    while (!read2.eof())
    {
        getline(read2, ch2);
        getline(read, ch);
        if (ch == account && flag == 0)
        {
            for (int i = 0; i < 4; i++)
            {
                getline(read, ch);
            }

            if (ch == phone)
            {
                write << "?\n";
                flag = 1;
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    getline(read2, ch2);
                }
            }
        }

        if (flag == 1)
        {
            getline(read2, ch2);
            ch = AccountNoGenerator();
            write << ch + "\n";
            while (ch2[0] != '+')
            {
                getline(read2, ch2);
                write << ch2 + "\n";
            }
            system("cls");
            write.close();
            cout << "\n\n\t\t\t\t\tAccount Successfully Recovered !!!";
            cout << "\n\n\t\t\t\t\tPress Any Key To Continue.....";
            getch();
            system("cls");
            ifstream in("backup.txt");
            ifstream in2("backup.txt");
            deletion_backup(account, in, in2);
            break;
        }
    }
    if (flag == 0)
    {
        system("cls");
        cout << "\n\n\t\t\t\t\tAccount Not Found !!!";
        cout << "\n\n\t\t\t\t\tPress Any Key To Continue.....";
        getch();
        system("cls");
    }
}

void Bank_account ::deletion_backup(string acc, ifstream &read, ifstream &read2)
{
    ofstream write("temp.txt");
    string ch, ch2;
    char choice[10];
    int flag = 0, flag2 = 0;

    while (1)
    {
        cout << "\n\t\t\t\t\t\tDo You Want To Delete Account From Backup(y/n) : ";
        cin >> choice;
        if ((choice[0] == 'y' || choice[0] == 'Y' || choice[0] == 'n' || choice[0] == 'N') && strlen(choice) == 1)
        {
            break;
        }
    }

    cout << "\n\n\t\t\t\t\t\tEnter Any Key To Confirm.......";
    getch();

    if (choice[0] == 'y' || choice[0] == 'Y')
    {
        getline(read, ch);

        while (!read2.eof())
        {
            getline(read, ch);
            getline(read2, ch2);

            if (ch == acc)
            {
                flag = 1;
                while (ch2[0] != '+')
                {
                    getline(read2, ch2);
                    getline(read, ch);
                }
                getline(read2, ch2);
            }

            write << ch2 + "\n";
        }

        write.close();
        if (flag == 0)
        {
            system("cls");
            cout << "\n\n\t\t\t\t\t\tAccount Not Found !!!!";
            cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
            system("cls");
        }
        else if (flag == 1)
        {
            ofstream write("backup.txt");
            ifstream read("temp.txt");

            while (!read.eof())
            {
                getline(read, ch);
                write << ch + "\n";
            }

            write.close();
            system("cls");
            cout << "\n\n\t\t\t\t\t\tAccount Deleted Sucessfully";
            cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
            system("cls");
        }
    }

    else
    {
        system("cls");
        cout << "\n\n\t\t\t\t\t\tAccount Not Deleted";
        cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
        getch();
        system("cls");
    }
}
int Bank_account ::valid(string ch)
{
    int i = 0, flag = 0;

    while (ch[i] != '\0')
    {
        if (ch[i] < '0' || ch[i] > '9')
        {
            return 0;
        }

        if (ch[i] == '.')
        {
            if (flag == 1)
            {
                return 0;
            }
            flag++;
        }

        i++;
    }

    return 1;
}

void Bank_account ::update(int i, int j, ifstream &read, ofstream &write, string data)
{
    string ch;

    for (int m = 0; m < i; m++)
    {
        getline(read, ch);
        write << ch + "\n";
    }

    getline(read, ch);
    data = data +"\n";
    write << data;

    while (!read.eof())
    {
        getline(read, ch);
        write << ch + "\n";
    }

    write.close();
}
void Bank_account ::correction()
{
    string account, ch;
    int flag = 0, choice;
    string data;
    ifstream read("Bank.txt");
    ofstream write("temp.txt");

    cout << "\n\n\t\t\t\t\t\tEnter Account Number : ";
    cin >> account;

    while (!read.eof())
    {
        getline(read, ch);
        write << ch + "\n";

        if (ch == account)
        {
            flag = 1;
            break;
        }
    }

    if (flag == 1)
    {
        system("cls");
        display(account);
        cout << "\n\n\t\t\t\t\t\tWhat Do You Want To Update\n\n\t\t\t\t\t\t1.Name\n\t\t\t\t\t\t2.Guardian's Name\n\t\t\t\t\t\t3.Date Of Birth\n\t\t\t\t\t\t4.Phone Number\n\t\t\t\t\t\t5.Address\n\t\t\t\t\t\t6.Email ID\n\n";
        cout << "\n\t\t\t\t\t\tEnter Your Choice : ";
        cin >> choice;

        if (choice >= 1 && choice <= 6)
        {
            cout<<"\n\n\t\t\t\t\t\tEnter Data : ";
            fflush(stdin);
            getline(cin,data);
            update(choice - 1, choice, read, write, data);

            ifstream in("temp.txt");
            ofstream out("Bank.txt");

            while (!in.eof())
            {
                getline(in, ch);
                out << ch + "\n";
            }

            out.close();

            system("cls");
            display(account);
            cout << "\n\n\t\t\t\t\t\tUpdated Sucessfully";
            cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
            system("cls");
        }
        else
        {
            system("cls");
            cout << "\n\n\t\t\t\t\t\tInvlaid Input";
            cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
            system("cls");
        }
    }
    else
    {
        system("cls");
        cout << "\n\n\t\t\t\t\t\tAccount Not Found !!";
        cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
        getch();
        system("cls");
    }
}

double Bank_account ::checkAccount(double num)
{
    ifstream read("Bank.txt");
    string ch;
    long long int num2;

    while (!read.eof())
    {
        getline(read, ch);

        if (ch == "?")
        {
            getline(read, ch);
            num2 = stoi(ch);

            if (num2 == num)
            {
                return 1;
            }
        }
    }

    return 0;
}

void Bank_account ::transaction()
{
    string account, amount;
    int res;
    int choice;

    while (1)
    {
        cout << "\n\n\t\t\t\t\t\tEnter Account Number : ";
        cin >> account;

        res = valid(account);

        if (res == 0)
        {
            cout << "\n\n\t\t\t\t\t\tInvlid Input";
            continue;
        }

        break;
    }

    while (1)
    {
        cout << "\n\n\t\t\t\t\t\tEnter Amount : ";
        cin >> amount;

        res = valid(amount);

        if (res == 0)
        {
            cout << "\n\n\t\t\t\t\t\tInvalid Amount!!";
            continue;
        }

        break;
    }

    while (1)
    {
        cout << "\n\n\t\t\t\t\t\t1.Deposite Money\n\t\t\t\t\t\t2.Withdraw Money\n\n\t\t\t\t\t\tEnter Your choice : ";
        cin >> choice;

        if (choice == 1)
        {
            credit(account, amount);
            break;
        }
        else if (choice == 2)
        {
            
            withdraw(account, amount);
            break;
        }
        else
        {
            cout << "\t\t\t\t\t\tInvalid Input!!!";
        }
    }

}

void Bank_account ::withdraw(string account,string temp)
{
    ifstream read("Bank.txt");
    ofstream write("temp.txt");
    string current;
    double amount, balance;
    int i, flag = 0, flag2 = 0, res;

    system("cls");

    amount = stod(temp);

    while (!read.eof())
    {
        getline(read, current);
        write << current + "\n";
        if (current == account)
        {
            flag2 = 1;
            for (i = 0; i < 6; i++)
            {
                getline(read, current);
                write << current + "\n";
            }

            getline(read, current);

            balance = stod(current);
            if (balance >= amount)
            {
                balance = balance - amount;

                current = to_string(balance);

                write << current + "\n";

                flag = 1;
            }
        }
    }

    write.close();
    if (flag == 1 && flag2 == 1)
    {
        ofstream out("Bank.txt");
        ifstream in("temp.txt");

        while (!in.eof())
        {
            getline(in, current);
            out << current + "\n";
        }
        out.close();

        system("cls");
        cout << "\n\n\t\t\t\t\t\tMoney Sucessfully Debited";
        balance = checkBalance(account);
        cout<<"\n\n\t\t\t\t\t\tRemaining Balance : "<<balance;
        cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
        getch();
        system("cls");
    }
    else if (flag == 0 && flag2 == 1)
    {
        system("cls");
        cout << "\n\n\t\t\t\t\t\tInsufficient Balance";
        cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
        getch();
        system("cls");
    }

    else if (flag == 0 && flag2 == 0)
    {
        system("cls");
        cout << "\n\n\t\t\t\t\t\tAccount Not Found";
        cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
        getch();
        system("cls");
    }
}

void Bank_account ::credit(string account,string temp)
{
    ifstream read("Bank.txt");
    ofstream write("temp.txt");
    string current;
    double amount, balance;
    int i, flag = 0,res;

    amount = stod(temp);

    while (!read.eof())
    {
        getline(read, current);
        write << current + "\n";
        if (current == account)
        {
            flag = 1;
            for (i = 0; i < 6; i++)
            {
                getline(read, current);
                write << current + "\n";
            }

            getline(read, current);

            balance = std::stod(current);
            balance = balance + amount;

            current = to_string(balance);

            write << current + "\n";
        }
    }

    write.close();

    if (flag == 1)
    {
        ofstream out("Bank.txt");
        ifstream in("temp.txt");

        while (!in.eof())
        {
            getline(in, current);
            out << current + "\n";
        }
        out.close();
        system("cls");
        cout << "\t\t\t\t\t\tMoney Sucessfully Deposited";
        balance = checkBalance(account);
        cout<<"\n\n\t\t\t\t\t\tRemaining Balance : "<<balance;
        cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
        getch();
        system("cls");
    }

    else if (flag == 0)
    {
        system("cls");
        cout << "\n\n\t\t\t\t\t\tAccount Not Found\n\n";
        cout << "\t\t\t\t\t\tPress Any Key To Continue.....";
        getch();
        system("cls");
    }
}

void Bank_account ::deletion(string acc, ifstream &read, ifstream &read2)
{
    ofstream write("temp.txt");
    ofstream backup("backup.txt", ios::app);
    string ch, ch2;
    char choice[10];
    int flag = 0, flag2 = 0;

    while (1)
    {
        cout << "\n\t\t\t\t\t\tDo You Want To Permanantely Delete Account (y/n) : ";
        cin >> choice;
        if ((choice[0] == 'y' || choice[0] == 'Y' || choice[0] == 'n' || choice[0] == 'N') && strlen(choice) == 1)
        {
            break;
        }
    }

    cout << "\n\n\t\t\t\t\t\tEnter Any Key To Confirm.......";
    getch();

    if (choice[0] == 'y' || choice[0] == 'Y')
    {
        getline(read, ch);

        while (!read2.eof())
        {
            getline(read, ch);
            getline(read2, ch2);

            if (ch == acc)
            {
                flag = 1;
                backup << ch2 + "\n";
                while (ch2[0] != '+')
                {
                    getline(read2, ch2);
                    getline(read, ch);
                    backup << ch2 + "\n";
                }
                getline(read2, ch2);
            }

            write << ch2 + "\n";
        }

        write.close();
        if (flag == 0)
        {
            system("cls");
            cout << "\n\n\t\t\t\t\t\tAccount Not Found !!!!";
            cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
            system("cls");
        }
        else if (flag == 1)
        {
            ofstream write("Bank.txt");
            ifstream read("temp.txt");

            while (!read.eof())
            {
                getline(read, ch);
                write << ch + "\n";
            }

            write.close();
            system("cls");
            cout << "\n\n\t\t\t\t\t\tAccount Deleted Sucessfully";
            cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
            system("cls");
        }
    }

    else
    {
        system("cls");
        cout << "\n\n\t\t\t\t\t\tAccount Not Deleted";
        cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
        getch();
        system("cls");
    }
}

void Bank_account ::insertion()
{
    string temp, temp2 = "\n", account;
    ofstream out("Bank.txt", ios ::app);
    int res = 0;

    system("cls");

    account = AccountNoGenerator();
    out << "\n?\n";
    out << account + "\n";

    cout << "\n\t\t\t\t\t\tEnter Account Holder Name : ";
    fflush(stdin);
    gets(name);

    temp = name + temp2;
    out << temp;

    cout << "\t\t\t\t\t\tEnter gaurdian Name : ";
    fflush(stdin);
    gets(gaurdian);

    temp = gaurdian + temp2;
    out << temp;

    cout << "\t\t\t\t\t\tEnter Date Of Birth (DD\\MM\\YYYY) : ";
    fflush(stdin);
    gets(dob);

    temp = dob + temp2;
    out << temp;

    while (1)
    {
        cout << "\t\t\t\t\t\tEnter Phone Number : ";
        cin >> phoneNumber;
        res = valid(phoneNumber);
        if (strlen(phoneNumber) != 10)
        {
            res = 0;
        }
        if (res == 0)
        {
            cout << "\n\n\t\t\t\t\t\tInvalid Input\n\n";
            continue;
        }
        break;
    }

    temp = phoneNumber + temp2;
    out << temp;

    cout << "\t\t\t\t\t\tEnter Address : ";
    fflush(stdin);
    gets(address);

    temp = address + temp2;
    out << temp;

    cout << "\t\t\t\t\t\tEnter Email : ";
    fflush(stdin);
    gets(email);

    temp = email + temp2;
    out << temp;

    while (1)
    {
        cout << "\t\t\t\t\t\tEnter Amount To Deposite : ";
        cin >> balance;

        res = valid(balance);

        if (res == 0)
        {
            cout << "\n\n\t\t\t\t\t\tInvalid Input\n\n";
            continue;
        }
        break;
    }

    temp = balance;
    out << temp;

    out << "\n+ ";
    cout << "\n\n\t\t\t\t\t\tYour Account Number Is  : " << account;
    cout << "\n\n\t\t\t\t\t\tData Saved Press Any Key To Confirm.....";
    getch();
    system("cls");
}

string Bank_account ::AccountNoGenerator()
{
    char temp;
    string temp2;
    long long int num = 0;
    int flag = 0;
    ifstream in("Bank.txt");

    if (in.peek() <= 0)
    {
        temp2 = "1000000000";
    }

    else
    {
        while (!in.eof())
        {
            temp = in.get();
            if (temp == '?')
            {
                in >> temp2;
            }
        }
        num = stoi(temp2);
        while (1)
        {
            num++;
            flag = checkAccount(num);
            if (flag == 0)
            {
                break;
            }
        }

        temp2 = to_string(num);
    }

    return temp2;
}

void Bank_account ::display(string acc)
{

    cout << "\n\n\t\t\t\t\t\t ~~~~~~~~~~~  CU Bank ~~~~~~~~~~~\n\n";

    ifstream out("Bank.txt");
    ifstream out2("Bank.txt");
    char ch2;
    string ch;
    char choice;
    int flag = 0;

    while (!out.eof())
    {
        ch2 = out.get();

        if (ch2 == '?')
        {
            out >> ch;

            if (ch == acc)
            {
                cout << "\t\t\t\t\t\t------------------------------------------------------------------";
                cout << "\n\n\t\t\t\t\t\t ~~~~~~~~~~~  Account Details ~~~~~~~~~~~\n\n";
                cout << "\t\t\t\t\t\tAccount Number          : " << ch << endl
                     << endl;
                out.ignore();
                getline(out, ch);
                cout << "\t\t\t\t\t\tIFSC code               : " << ifsc << endl;
                cout << "\t\t\t\t\t\tAccount Holder's Name   : " << ch << endl;
                getline(out, ch);
                cout << "\t\t\t\t\t\tGuardians Name          : " << ch << endl;
                out >> ch;
                cout << "\t\t\t\t\t\tDate Of Birth(DD\\MM\\YY) : " << ch << endl;
                out >> ch;
                cout << "\t\t\t\t\t\tPhone Number            : " << ch << endl;
                out.ignore();
                getline(out, ch);
                cout << "\t\t\t\t\t\tAddress                 : " << ch << endl;
                out >> ch;
                cout << "\t\t\t\t\t\tEmail ID                : " << ch << endl
                     << endl;
                out >> ch;
                cout << "\t\t\t\t\t\tCurrent Balance         : $ " << ch << endl;
                cout << "\t\t\t\t\t\t------------------------------------------------------------------" << endl;
                flag = 1;
                break;
            }
        }
    }

    if (flag == 0)
    {
        cout << "\n\nAccount Not Found!!!";
    }
}

double Bank_account ::checkBalance(string account)
{
    string balance;
    check obj;
    double amount;

   obj = locate(account);

   for(int i=0;i<7;i++) 
   {
       getline(obj.read,balance);
   }

   amount = stod(balance);

   return amount;

}

void Bank_account ::deleteRequest(string account)
{
    ofstream write("temp.txt");
    ifstream read("Request.txt");
    ifstream read2("Request.txt");
    string ch, ch2;
    char choice[10];


    cout << "\n\n\t\t\t\t\t\tEnter Any Key To Confirm.......";
    getch();

    getline(read, ch);

    while (!read2.eof())
    {
        getline(read, ch);
        getline(read2, ch2);

        if (ch == account)
        {
            while (ch2[0] != '+')
            {
                getline(read2, ch2);
                getline(read, ch);
            }
            getline(read2, ch2);
        }

        if(ch2!="?")
        {
            write << ch2 + "\n";
        }
    } 
    write.close();
    ofstream write2("Request.txt");
    ifstream read3("temp.txt");

    while (!read3.eof())
    {
        getline(read3, ch);
        write2 << ch + "\n";
    }

    write.close();
}
void Bank_account :: correctionR(string account,string data,int choice)
{
    string ch;
    char cho;
    int flag = 0,i=0;
    ifstream read("Bank.txt");
    ofstream write("temp.txt");
    
    cout<<"\n\n\t\t\t\t\t\tAccount Number : "<<account<<endl;

    while(1)
    {
        display(account);

        cout<<"\n\n\t\t\t\t\t\tRequest For :";
        if(choice == 1)
        {
            cout<<"\n\n\t\t\t\t\t\tName :"<<data;
        }
        else if(choice == 2)
        {
            cout<<"\n\n\t\t\t\t\t\tGardian's Name :"<<data;
        }
        else if(choice == 3)
        {
            cout<<"\n\n\t\t\t\t\t\tDOB :"<<data;
        }
        else if(choice == 4)
        {
            cout<<"\n\n\t\t\t\t\t\tPhone :"<<data;
        }
        else if(choice == 5)
        {
            cout<<"\n\n\t\t\t\t\t\tAddress :"<<data;
        }
        else if(choice == 6)
        {
            cout<<"\n\n\t\t\t\t\t\tEmail :"<<data;
        }
        cout<<"\n\n\t\t\t\t\t\tDo You Want To Update (y/n) : ";
        cin>>cho;

        if(cho == 'y' || cho == 'Y')
        {
            while (!read.eof())
            {
                getline(read, ch);
                write << ch + "\n";

                if (ch == account)
                {
                    flag = 1;
                    break;
                }
            }
            system("cls");

            if (choice >= 1 && choice <= 6)
            {
                update(choice - 1, choice, read, write, data);

                ifstream in("temp.txt");
                ofstream out("Bank.txt");

                while (!in.eof())
                {
                    getline(in, ch);
                    out << ch + "\n";
                }

                out.close();

                system("cls");
                display(account);
                cout << "\n\n\t\t\t\t\t\tUpdated Sucessfully";
                cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
                getch();
                system("cls");
                break;
            }
        }
        else if(cho == 'n' || cho == 'N')
        {
            system("cls");
            cout << "\n\n\t\t\t\t\t\tAccount Not Updated !!";
            cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
            system("cls");
            break;
        }

        else
        {
            system("cls");
            cout << "\n\n\t\t\t\t\t\tInvlid Input !!";
            cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
            system("cls");
        }
    }
}
void Bank_account ::updateRequest()
{
    string ch,ch2,account;
    int choice,flag=0;
    ifstream read("Request.txt");
    ifstream read2("Request.txt");

    getline(read,ch);

    while(!read.eof())
    {
        getline(read,ch);
        getline(read2,ch2);
        if(ch2 == "?")
        {
            while(1)
            {
                getline(read,ch);
                if(ch=="+")
                {
                    break;
                }
                getline(read2,ch2);
                choice = stoi(ch);
                getline(read,ch);
                if(flag==0)
                {
                    flag=1;
                    account = ch2;
                }
                correctionR(account,ch,choice);
                getline(read2,ch2);
            }
            deleteRequest(account);
            getline(read,ch);
            getline(read2,ch2);
        }
    }

}
int main()
{
    Bank_account obj;
    return 0;
}
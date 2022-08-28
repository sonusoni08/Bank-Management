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

class User
{
    string userName;
    char password[30];
    char pin[7];
    string accountNumber;
    static string ifsc;

public:
    User();
    check find(string,string);
    void registration();
    void login();
    void transfer(string);
    void balance();
    int validateUserName(string);
    void display(string);
    void credit(string,string);
    check locate(string);
    double checkBalance(string);
    void withdraw(string,string);
    void loginAccess(string);
    void requestForUpdate(string);
};

string User :: ifsc = "20BCS1112";

User ::User()
{   
    int choice;

    while(1)
    {
        system("cls");
        cout<<"\n\n\t\t\t\t\t\t1.Registration\n\t\t\t\t\t\t2.Login\n\t\t\t\t\t\t3.Exit";
        cout<<"\n\n\t\t\t\t\t\tEnter Your Choice : ";
        cin>>choice;
        if(choice==1)
        {
            registration();
        }
        else if(choice==2)
        {
            login();
        }
        else if(choice==3)
        {
            break;
        }
        else
        {
            cout<<"\n\n\t\t\t\t\t\tInvalid Input";
            cout<<"\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
        }
    }
}
check User ::locate(string account)
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
double User ::checkBalance(string account)
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
void User ::credit(string account,string temp)
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
void User ::withdraw(string account,string temp)
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

            balance = std::stod(current);
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
void User ::transfer(string account1)
{
    int choice;
    string account,amount;

    cout<<"\n\n\t\t\t\t\t\tEnter Account Number To Send Money : ";
    fflush(stdin);
    getline(cin,account);

    cout<<"\n\n\t\t\t\t\t\tEnter Amount : ";
    getline(cin,amount);

    while(1)
    {
        cout<<"\n\n\t\t\t\t\t\t1.Transfer To Same Bank\n2.Different Bank Acoount\n\n\t\t\t\t\t\tEnter Your Choice : ";
        cin>>choice;

        if(choice==1)
        {
            system("cls");
            withdraw(account1,amount);
            credit(account,amount);
        }

        else if(choice == 2)
        {
            system("cls");
            withdraw(account1,amount);
        }

        else
        {
            cout<<"\n\n\n\n\t\t\t\t\t\tInvalid Input";
            cout<<"\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
            getch();
            system("cls");
        }
        break;
    }

}

void User :: login()
{
    string name,ch;
    char pass[30];
    char a;
    int i=0,flag=0;
    ifstream read("user.txt");

    cout<<"\n\n\t\t\t\t\t\tEnter User Name : ";
    fflush(stdin);
    getline(cin,name);

    cout<<"\n\n\t\t\t\t\t\tEnter Password : ";
    while (1)
    {
        a = getch();
        if(a>'!' && a<'z')
        {
            pass[i++] = a;
            cout << "*";
        }

        if (a == '\b' && i >= 1)
        {
            cout << "\b \b";
            i--;
        }
        else if (a == '\r')
        {
            pass[i] = '\0';
            break;
        }
    }

    while(!read.eof())
    {
        getline(read,ch);
        if(ch[0] == '?')
        {
            getline(read,ch);
            if(ch==name)
            {
                getline(read,ch);
                if(ch == pass)
                {
                    getline(read,ch);
                    getline(read,ch);
                    flag=1;
                    break;
                }
            }
        }
    }

    if(flag==1)
    {
        accountNumber = ch;
        system("cls");
        loginAccess(accountNumber);
    }

    else
    {
        cout<<"\n\n\t\t\t\t\t\tAccount Not Found !!!";
        cout<<"\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
        getch();
    }

}
void User ::display(string acc)
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
        cout << "\n\nAccount Not check!!!";
    }
    cout<<"\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
    getch();
}

void User ::registration()
{
    check data;
    string acc, ch, temp,phone;
    char a;
    int i = 0,res;
    ofstream write("user.txt", ios::app);

    cout << "\n\n\t\t\t\t\t\tEnter Account Number : ";
    fflush(stdin);
    getline(cin, acc);

    cout<<"\n\n\t\t\t\t\t\tEnter Phone Number Registered With Account : ";
    fflush(stdin);
    getline(cin,phone);

    data = find(acc,phone);

    getline(data.read, ch);

    if (data.num == 1)
    {
        write << ch + "\n";
        while(1)
        {
            system("cls");
            cout << "\n\n\t\t\t\t\t\tCreate User Name : ";
            getline(cin, userName);

            res = validateUserName(userName);

            if(res==0)
            {
                cout<<"\n\n\t\t\t\t\t\tUser Name Already Taken Try Another";
                cout<<"\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
                getch();
                continue;
            }
            break;

        }
        while (1)
        {
            i = 0;

            cout << "\n\n\t\t\t\t\t\tCreate Password : ";
            while (1)
            {
                a = getch();
                if(a>'!' && a<'z')
                {
                    password[i++] = a;
                    cout << "*";
                }

                if (a == '\b' && i >= 1)
                {
                    cout << "\b \b";
                    i--;
                }
                else if (a == '\r')
                {
                    password[i] = '\0';
                    break;
                }

            }

            cout << "\n\n\n\t\t\t\t\t\tConfirm Password : ";
            getline(cin, temp);

            if (temp != password)
            {
                cout << "\t\t\t\t\t\tPasswords Not Match !!";
                cout << "\n\n\t\t\t\t\t\tPress Any Key To Retry !!";
                getch();
                continue;
            }
            else
            {
                break;
            }
        }
        write<<userName+"\n";
        write<<temp+"\n";

        system("cls");

        while (1)
        {

            cout << "\n\n\t\t\t\t\t\tCreate PIN For Transiction(6 - digit) : ";
            i = 0;
            while (i != 6)
            {
                a = getch();

                if (a >= '0' && a <= '9')
                {
                    pin[i++] = a;
                    cout << "*";
                }

                if (a == '\b' && i >= 1)
                {
                    cout << "\b \b";
                    i--;
                }
                else if (i == 6)
                {
                    pin[i] = '\0';
                    break;
                }
            }
            i = 0;
            cout << "\n\n\t\t\t\t\t\tConfirm PIN : ";
            cin >> temp;

            if (pin != temp)
            {
                cout << "\n\n\t\t\t\t\t\tPIN Not Match !!! ";
                cout << "\n\n\t\t\t\t\t\tPress Any Key To Re-enter !!!";
                getch();
                continue;
            }
            break;
        }
        write<<temp+"\n"+acc+"\n+\n";
    }

    else if (data.num == 0)
    {
        system("cls");
        cout << "\n\n\t\t\t\t\t\tAccount Not Found !!!";
        cout<<"\n\n\t\t\t\t\t\tPress Any key To Continue.....";
        getch();
    }
}

void User ::requestForUpdate(string account)
{
    int choice[6],i=0,flag=0;
    string ch,ch2;
    ofstream write("Request.txt",ios::app);

    write<<"?\n"+account+"\n";

    while(i!=6)
    {
        system("cls");
        flag=0;
        display(account);
        cout << "\n\n\t\t\t\t\t\tWhat Do You Want To Update\n\n\t\t\t\t\t\t1.Name\n\t\t\t\t\t\t2.Guardian's Name";
        cout<<"\n\t\t\t\t\t\t3.Date Of Birth\n\t\t\t\t\t\t4.Phone Number\n\t\t\t\t\t\t5.Address\n\t\t\t\t\t\t6.Email ID\n\n";
        cout << "\n\t\t\t\t\t\tEnter Your Choice : ";
        fflush(stdin);
        cin >> choice[i];

        if(choice[i]>=1 && choice[i]<=6)
        {
            for(int m=0;m<i;m++)
            {
                if(choice[i] == choice[m])
                {
                    flag=1;
                    break;
                }
            }

            if(flag==0)
            {
                cout<<"\n\n\t\t\t\t\t\tEnter Data : ";
                fflush(stdin);
                getline(cin,ch);
                ch2 = to_string(choice[i]);
                write<<ch2+"\n"+ch+"\n";
                cout << "\n\n\t\t\t\t\t\tRequest Sent";
                cout << "\n\n\t\t\t\t\t\tPress Any Key To Continue.....";
                getch();
                i++;
            }
            else
            {
                cout<<"\n\n\t\t\t\t\t\tRequest Already sent !!!";
            }
            
            
            system("cls");
        }
    
        else if(choice[i] == 7)
        {
            i++;
            write<<"+\n";
            write.close();
            break;
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

    write<<"+\n";
    write.close();

}
void User ::loginAccess(string account)
{
    int choice;
    cout<<"\n\n\t\t\t\t\t\t1.Display\n\t\t\t\t\t\t2.Transfer\n\t\t\t\t\t\t3.Request For Data Update\n\t\t\t\t\t\t4.Exit";
    cout<<"\n\n\t\t\t\t\t\tEnter Your Choice : ";
    cin>>choice;

    switch(choice)
    {
        case 1:
        {
            system("cls");
            display(account);
            break;
        }
        case 2:
        {
            system("cls");
            transfer(account);
            break;
        }
        case 3:
        {
            system("cls");
            requestForUpdate(account);
            break;
        }
        case 4:
        {
            system("cls");
            cout<<"\n\n\n\nThankyou";
            cout<<"\n\nPress Any Key To Continue......";
            getch();
        }

    }
}
int User ::validateUserName(string str)
{
    ifstream read("user.txt");
    string ch;

    while(!read.eof())
    {
        getline(read,ch);
        if(ch[0]=='?')
        {
            getline(read,ch);
            if(ch==str)
            {
                return 0;
            }
        }
    }
    return 1;
}
check User ::find(string str,string phone)
{
    string ch, ch2;
    check obj;
    ifstream in("Bank.txt");
    obj.read.open("Bank.txt");

    while (!in.eof())
    {
        getline(in, ch);
        getline(in, ch);

        if (ch == str)
        {
            for(int m=0;m<4;m++)
            {
            getline(in,ch);
            }
            if(ch == phone)
            {
                obj.num = 1;
                return obj;
            }
        }

        while (!in.eof())
        {
            getline(obj.read, ch2);
            getline(in, ch);

            if (ch == str)
            {
            for(int m=0;m<4;m++)
            {
                getline(in,ch);
            }
                getch();
                if(ch == phone)
                {
                    obj.num = 1;
                    return obj;
                }
            }
        }
    }
    obj.num = 0;
    return obj;
}
int main()
{
    User obj;
    // obj.registration();

    return 0;
}
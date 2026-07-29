#include <iostream>
#include<string>
#include<vector>
#include<iomanip>
#include <conio.h>
#include<fstream>
using namespace std;
const string CLIENT_DATA = "ClientsData.txt";
const string USER_DATA = "UsersData.txt";

enum enMainMenueOptions
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eTransactions = 6, eManageUsers = 7, eLogOut = 8
};
enum enTransactionOptions
{
	eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenue = 4
};
enum enManageUserOptions
{
	eListUsers = 1, eAddNewUser = 2,
	eDeleteUser = 3, eUpdateUser = 4,
	eFindUser = 5, eMainMenue2 = 6
};
enum enPermissionMenue {
	FullAccess = -1, ShowClientListPer = 1, AddNewClientPer = 2, DeleteCLientPer = 4, UpdateClientPer = 8, FindClientPer = 16,
	TransactionsMenuePer = 32, ManageUsersPer = 64
};


void ShowMainMenue();
void ShowTransactionsMenue();
void ShowLoginScreen();
void ShowManageUserScreen();
void AddDataLineToFile(string FlieLocation, string LineToAdd)
{
	fstream File;
	File.open(FlieLocation, ios::out | ios::app);
	if (File.is_open())
	{	
		File << LineToAdd << endl;
	}
}
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance=0;
	bool MarkForDelete = false;

};
struct stUser
{
	string Username = " ";
	string Password = " ";
	short Permission = 0;
	bool MarkForDelete = false;
};
 stUser CURRUNT_USER;
vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord;

	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}
string ConvertClientRecordToLine(sClient ClientInfo, string Seperator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += ClientInfo.AccountNumber + Seperator;
	stClientRecord += ClientInfo.PinCode + Seperator;
	stClientRecord += ClientInfo.Name + Seperator;
	stClientRecord += ClientInfo.Phone + Seperator;
	stClientRecord += to_string(ClientInfo.AccountBalance);
	return stClientRecord;
}
string ConvertUserRecordToLine(stUser UserInfo, string Seperator = "#//#")
{
	string stUserRecord = "";
	stUserRecord += UserInfo.Username+Seperator;
	stUserRecord += UserInfo.Password + Seperator;
	stUserRecord += to_string( UserInfo.Permission )+ Seperator;
	return stUserRecord;
}
sClient ConvertLineToClientRecord(string Line, string Seperator = "#//#")
{
	sClient sClient;
	vector<string>vClientRecord;

	vClientRecord = SplitString(Line, Seperator);

	sClient.AccountNumber = vClientRecord[0];
	sClient.PinCode = vClientRecord[1];
	sClient.Name = vClientRecord[2];
	sClient.Phone = vClientRecord[3];
	sClient.AccountBalance = stoi(vClientRecord[4]);

	return sClient;


}
vector<sClient>LoadClientDataFromFile(string FileLoction)
{
	vector<sClient> vClient;
	fstream MyFile;
	MyFile.open(CLIENT_DATA, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient C;
		while (getline(MyFile, Line))
		{
			C = ConvertLineToClientRecord(Line);
			vClient.push_back(C);
		}
		MyFile.close();
	}
	return vClient;
}
vector<sClient> SaveClientDataToFile(string FileLoction, vector<sClient>Clients)
{
	fstream MyFile;
	MyFile.open(FileLoction, ios::out);
	if (MyFile.is_open())
	{

		string Line;

		for (sClient& C : Clients)
		{
			if (C.MarkForDelete == false)
			{
				Line = ConvertClientRecordToLine(C);

				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
	return Clients;
}
stUser ConvertLineToUserRecord(string Line, string Sperator = "#//#")
{
	stUser User;
	vector<string>vUser;

	vUser = SplitString(Line, Sperator);

	User.Username = vUser[0];
	User.Password = vUser[1];
	User.Permission = static_cast<short>(stoi(vUser[2]));

	return User;

}

vector<stUser>LoadUserDataFromFile(string FileLocation)
{
	vector<stUser>vUsers;
	fstream MyFile;
	MyFile.open(FileLocation, ios::in);
	if (MyFile.is_open())
	{
		stUser User;
		string Line;
		while (getline(MyFile, Line))
		{
			User = ConvertLineToUserRecord(Line);
			vUsers.push_back(User);
		}
		MyFile.close();
	}
	return vUsers;
}
bool FindUserByUsernameAndPassword(string Username, string Password, vector<stUser>& vUsers, stUser& UserFounded)
{


	for (stUser& U : vUsers)
	{
		if (Username == U.Username && Password == U.Password)
		{
			UserFounded = U;
			return true;
		}
	}
	return false;
}
short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 8]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
void PrintClientData(sClient& Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber
		<< "| " << setw(10) << Client.PinCode
		<< "| " << setw(30) << Client.Name
		<< "| " << setw(15) << Client.Phone
		<< "| " << setw(15) << Client.AccountBalance
		<< "|\n";
}

void ShowAllClientsScreen()
{
	vector<sClient> Clients = LoadClientDataFromFile(CLIENT_DATA);


	cout << "\n\t\t\t\t\tClient List (" << Clients.size() << ") Client(s).\n\n";

	cout << "-----------------------------------------------------------------------------------------------\n";

	cout << "| " << left << setw(15) << "Account Number"
		<< "| " << setw(10) << "Pin Code"
		<< "| " << setw(30) << "Client Name"
		<< "| " << setw(15) << "Phone Number"
		<< "| " << setw(15) << "Balance"
		<< "|\n";

	cout << "-----------------------------------------------------------------------------------------------\n";

	if (Clients.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In the System! ";
	}
	else
	{
		for (sClient& C : Clients)
		{
			PrintClientData(C);

		}
	}
	cout << "-----------------------------------------------------------------------------------------------\n";

}


void GoBackToMainMenue()
{
	cout << "\n \n Press Any Key To Back To Main Menue Screen ....... ";
	system("pause>0");
	ShowMainMenue();


}
bool ClientExistsByAccountNumber(string FileLocation, string AccountNumber)
{

	fstream MyFile;
	MyFile.open(CLIENT_DATA, ios::in);
	if (MyFile.is_open())
	{

		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToClientRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}


		}
		MyFile.close();

	}
	return false;
}
sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number? ";

	getline(cin >> ws, Client.AccountNumber);
	while (ClientExistsByAccountNumber(CLIENT_DATA, Client.AccountNumber))
	{
		cout << "\nClient with [" << Client.AccountNumber << "]already exists, Enter another Account Number ? ";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}
void AddNewClient()
{
	sClient NewClient;
	NewClient = ReadNewClient();
	AddDataLineToFile(CLIENT_DATA, ConvertClientRecordToLine(NewClient));

}
void AddNewClients()
{
	char Answer = 'N';
	do
	{
		system("cls");
		cout << "Adding New Client :\n \n";
		AddNewClient();

		cout << "Client Added Successfully , do you want to Add new Clients ? (Y/N)  ";
		cin >> Answer;

	} while (toupper(Answer) == 'Y');

}
bool HasPermission(stUser& user, enPermissionMenue permission)
{
	return user.Permission == FullAccess ||
		(user.Permission & permission) == permission;
}
string ReadAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;

}
bool FindClientByAccountNumber(string AccountNumber, vector<sClient>Clients, sClient& FoundedClient)
{
	for (sClient& C : Clients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			FoundedClient = C;
			return true;
		}
	}
	return false;
}
bool MarkClientForDelete(string AccountNumber, vector<sClient>& Clients)
{
	for (sClient& C : Clients)
	{
		if (AccountNumber == C.AccountNumber)
		{
			C.MarkForDelete = true;
			return true;

		}

	}

	return false;

}
void PrintAccountDetails(sClient Client)
{
	cout << "\n";
	cout << "=====================================================\n";
	cout << "\t\tClient Details\n";
	cout << "=====================================================\n";

	cout << left << setw(20) << "Account Number" << ": " << Client.AccountNumber << endl;
	cout << left << setw(20) << "Pin Code" << ": " << Client.PinCode << endl;
	cout << left << setw(20) << "Name" << ": " << Client.Name << endl;
	cout << left << setw(20) << "Phone Number" << ": " << Client.Phone << endl;
	cout << left << setw(20) << "Balance" << ": " << Client.AccountBalance << endl;

	cout << "=====================================================\n";

}
void PrintUserDetails(stUser User)
{
	cout << "\n";
	cout << "=====================================================\n";
	cout << "\tUser Details\n";
	cout << "=====================================================\n";
	cout << left << setw(15) << "User Name : " << User.Username << endl;
	cout << left << setw(15) << "User Password: " << User.Password << endl;
	cout << left << setw(20) << "User Permition Number: " << User.Permission << endl;
	cout << "=====================================================\n";

}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> Clients)
{
	sClient Client;
	char Answer = 'N';
	if (FindClientByAccountNumber(AccountNumber, Clients, Client))
	{
		PrintAccountDetails(Client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			MarkClientForDelete(AccountNumber, Clients);
			SaveClientDataToFile(CLIENT_DATA, Clients);
			Clients = LoadClientDataFromFile(CLIENT_DATA);
			cout << "\n\nClient Deleted Successfully.";
			return true;

		}

	}
	return false;


}
void AddNewClientsScreen()
{
	cout << "----------------------------------\n";
	cout << "\tAdd new clients screen \n";
	cout << "----------------------------------\n";
	AddNewClients();
}
void DeleteClientScreen()
{

	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	vector<sClient> vClients = LoadClientDataFromFile(CLIENT_DATA);
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);

}
sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>vClients)
{
	sClient Client;
	char Answer = 'N';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintAccountDetails(Client);
		cout << "Are you sure about update THIS CLIENT ? .....  ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			for (sClient& C : vClients)
			{
				if (AccountNumber == C.AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;

				}
			}
			SaveClientDataToFile(CLIENT_DATA, vClients);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	return false;

}
void UpdateClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";
	vector <sClient> vClients = LoadClientDataFromFile(CLIENT_DATA);
	string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);

}
void ShowFindClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadClientDataFromFile(CLIENT_DATA);
	sClient Client;
	string AccountNumber = ReadAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintAccountDetails(Client);
	else
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}
void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}


void GoBackToTransactionsMenue()
{
	cout << "Press Any Key To Back To Transactions Menue ...... ";
	system("pause>0");
	ShowTransactionsMenue();

}
short ReadTransactionsMenueOption()
{
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
int AddBalance(int Number, sClient& Client)
{
	return (Client.AccountBalance += Number);

}
void DepositBalanceByAccountNumber(string AccountNumber, vector<sClient>vClients)
{
	unsigned int DepositAmount = 0;
	char Answer = 'N';
	if (ClientExistsByAccountNumber(CLIENT_DATA, AccountNumber))
	{

		for (sClient& C : vClients)
		{
			if (AccountNumber == C.AccountNumber)
			{
				PrintAccountDetails(C);

				cout << " \n Please Enter How Much Do You Want To Add:  "; cin >> DepositAmount;

				cout << " \n Are You Sure About This Deposit ? (Y/N)  "; cin >> Answer;

				if (toupper(Answer) == 'Y')
				{

					AddBalance(DepositAmount, C);
					cout << " \n Balance After Add (" << DepositAmount << ") is " << C.AccountBalance << endl;
					vClients = SaveClientDataToFile(CLIENT_DATA, vClients);
					return;
				}
				else
				{
					GoBackToTransactionsMenue();
				}
			}
		}

	}
	else
	{
		cout << "This Account Number Is Not Exist ! \n";
		return;
	}

}
void ShowDepositScreen()
{
	cout << "========================================================================\n";
	cout << "\t\t\t\t Welcome To Deposit Screen\n";
	cout << "========================================================================\n";

	string AccountNumber = ReadAccountNumber();
	vector<sClient>vClients = LoadClientDataFromFile(CLIENT_DATA);
	DepositBalanceByAccountNumber(AccountNumber, vClients);



}

void WithDrawBalanceByAccountNumber(string AccountNumber, vector<sClient>vClients)
{
	int WithdrawAmount = 0;
	char Answer = 'N';
	sClient Client;
	if (ClientExistsByAccountNumber(CLIENT_DATA, AccountNumber))
	{
		for (sClient& C : vClients)
		{
			if (AccountNumber == C.AccountNumber)
			{
				PrintAccountDetails(C);

				cout << "Please Enter The Amout To Withdraw : "; cin >> WithdrawAmount;
				while (WithdrawAmount > C.AccountBalance)
				{
					cout << " \n Amount Exceeds The Balance you can withdraw up to ( " << C.AccountBalance << " ) \n";
					cout << "Enter Another Ammount : "; cin >> WithdrawAmount;

				}
				cout << "\n Are you Sure Abount This Withdraw ? (Y/N) ";
				cin >> Answer;
				if (toupper(Answer) == 'Y')
				{
					AddBalance((-1 * WithdrawAmount), C);
					cout << " \n Balance After Withdraw (" << WithdrawAmount << ") is " << C.AccountBalance << endl;
					vClients = SaveClientDataToFile(CLIENT_DATA, vClients);
					return;
				}
				else
				{
					GoBackToTransactionsMenue();
				}

			}
		}
	}
	else
	{
		cout << "This Account Number Is Not Exist ! \n";
		return;
	}

}
void ShowWithdrawScreen()
{
	cout << "========================================================================\n";
	cout << "\t\t\t\t Welcome To Withdraw Screen\n";
	cout << "========================================================================\n";

	string AccountNumber = ReadAccountNumber();
	vector<sClient>vClients = LoadClientDataFromFile(CLIENT_DATA);
	WithDrawBalanceByAccountNumber(AccountNumber, vClients);

}
long int CalculateTotalBalances(vector<sClient>vClients)
{
	long int Summation = 0;

	for (sClient& C : vClients)
	{
		Summation += C.AccountBalance;
	}
	return Summation;

}
void PrintClientBalanceData(sClient Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber
		<< "| " << setw(30) << Client.Name
		<< "| " << setw(15) << Client.AccountBalance
		<< "|\n";
}
void ShowTotalBalancesScreen()
{
	vector<sClient>Clients = LoadClientDataFromFile(CLIENT_DATA);

	cout << "\n\t\t\t\t\tClient List (" << Clients.size() << ") Client(s).\n\n";

	cout << "------------------------------------------------------------------\n";

	cout << "| " << left << setw(15) << "Account Number"
		<< "| " << setw(30) << "Client Name"
		<< "| " << setw(15) << "Balance"
		<< "|\n";

	cout << "------------------------------------------------------------------\n";

	if (Clients.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In the System! ";
	}
	else
	{
		for (sClient& C : Clients)
		{
			PrintClientBalanceData(C);

		}
	}
	cout << "------------------------------------------------------------------\n";
	cout << "\n\t\t\t\t\t TOTAL BALANCES : " << CalculateTotalBalances(Clients) << " .\n";

}
short ReadManageUserScreenOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
bool FindUserByUserName(string UsernameToSearch, stUser& UserFounded, vector<stUser>vUsersToSearch)
{

	for (stUser& U : vUsersToSearch)
	{
		if (U.Username == UsernameToSearch)
		{
			UserFounded = U;
			return true;
		}
	}
	return false;
}
bool CheckUserPassword(stUser User)
{
	string Password;
	cout << "Please Enter The Password :  ";
	cin >> Password;
	return (Password == User.Password);
}
vector<stUser>SaveUserDataToFile(string FileLocation, vector<stUser> vUsers)
{
	fstream MyFile;
	MyFile.open(FileLocation, ios::out);
	if (MyFile.is_open())
	{
		string Line;
		for (stUser& U : vUsers)
		{
			if (U.MarkForDelete == false)
			{
				Line = ConvertUserRecordToLine(U);
				MyFile << Line << endl;

			}

		}
		MyFile.close();
	}
	return vUsers;

}
string ReadUserName()
{
	string Username;
	cout << "Please Enter User Name : ";
	getline(cin >> ws, Username);

	return Username;
}

void PrintUserData(const stUser& User)
{
	cout << "| " << left << setw(30) << User.Username
		<< "| " << setw(20) << User.Password
		<< "| " << setw(12) << User.Permission
		<< "|\n";
}

void ShowListUserScreen()
{
	vector<stUser> vUsers = LoadUserDataFromFile(USER_DATA);

	cout << "\n\t\t\t\tUser List ("
		<< vUsers.size() << ") User(s).\n\n";

	cout << "---------------------------------------------------------------------\n";

	cout << "| " << left << setw(30) << "Username"
		<< "| " << setw(20) << "Password"
		<< "| " << setw(12) << "Permission"
		<< "|\n";

	cout << "---------------------------------------------------------------------\n";

	if (vUsers.empty())
	{
		cout << "\t\tNo users available in the system.\n";
	}
	else
	{
		for (const stUser& User : vUsers)
		{
			PrintUserData(User);
		}
	}

	cout << "---------------------------------------------------------------------\n";
}
short ReadUserPermissions(stUser &User)
{
	char Answer = 'n';
	cout << "Do You Want To Give Full Access? (Y/N)? \n";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		User.Permission = FullAccess;
	}
	else
	{
		cout << "What Do You Want To Give ? \n";
		cout << "-------------------------------------------\n";

		cout << "List Clients ? (Y/N)? \n";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			User.Permission = User.Permission | ShowClientListPer;
			Answer = 'n';
		}
		cout << "Add New Clients ? (Y/N)? \n";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			User.Permission = User.Permission | AddNewClientPer;
			Answer = 'n';
		}
		cout << "Delete Clients ? (Y/N)? \n";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			User.Permission = User.Permission | DeleteCLientPer;
			Answer = 'n';
		}
		cout << "Update Clients ? (Y/N)? \n";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			User.Permission = User.Permission | UpdateClientPer;
			Answer = 'n';
		}
		cout << "Transactions ? (Y/N)? \n";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			User.Permission = User.Permission | TransactionsMenuePer;
			Answer = 'n';
		}
		cout << "Manage Users ? (Y/N)? \n";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			User.Permission = User.Permission | ManageUsersPer;
			Answer = 'n';
		}

	}
	return User.Permission;
}
bool IsUserHere(string Username, vector<stUser>vUsers)
{
	for (stUser& U : vUsers)
	{
		if (Username == U.Username)
		{
			return true;
		}


	}
	return false;

}

void AddNewUser()
{
	stUser NewUser;
		cout << "Please Enter Username :   ";getline(cin >> ws, NewUser.Username);
		cout << "Please Enter Password :   ";getline(cin, NewUser.Password);

		if (IsUserHere(NewUser.Username, LoadUserDataFromFile(USER_DATA)))
		{ 
			cout << "This Name is Already Exist Please Try Again....\n\n";

		}
		else
		{
			NewUser.Permission = ReadUserPermissions(NewUser);


			string Line;
			Line = ConvertUserRecordToLine(NewUser);

			AddDataLineToFile(USER_DATA, Line);
			printf("\n User Added Successfuly ! \n");
		}

		
	
}
void AddNewUsers()
{
	char Answer = 'N';
	do
	{
		
		AddNewUser();

		cout << "Do you want to add new User? (Y/N)? \n";
		cin >> Answer;
		

	} while (toupper(Answer) == 'Y');

}
void ShowAddNewUserScreen()
{ 
	

	cout << "========================================================================\n";
	cout << "\t\t\t Welcome To Add New User Screen\n";
	cout << "========================================================================\n";

	AddNewUsers();


};
bool DeleteUser(string Username,vector<stUser>vUsers)
{
	char Answer = 'N';
	stUser UserToDelete;
	if (FindUserByUserName(Username, UserToDelete, vUsers))
	{
		PrintUserDetails(UserToDelete);
		cout << "Are you sure About THIS User? (Y/N)? \n";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			CheckUserPassword(UserToDelete);

			for (stUser& U : vUsers)
			{

				if (U.Username == UserToDelete.Username)
				{
					U.MarkForDelete = true;
				}

			}
			SaveUserDataToFile(USER_DATA, vUsers);

		}
		cout << "User Deleted Successfully !\n";
		return true;
	}
	else
	{
		cout << "User Didn't Found Please Try Again !\n";
		return false;
		
	}
		
	

}

void ShowDeleteUserScreen()
{


	cout << "========================================================================\n";
	cout << "\t\t\t Welcome To Delete  User Screen\n";
	cout << "========================================================================\n";

	string Username = ReadUserName();
	vector<stUser>vUsers = LoadUserDataFromFile(USER_DATA);
	
	DeleteUser(Username,vUsers);

};





void ShowFindUserScreen()

{
	
	cout << "========================================================================\n";
	cout << "\t\t\t Welcome To Find User Screen\n";
	cout << "========================================================================\n";
	stUser User;
	if (FindUserByUserName(ReadUserName(), User, LoadUserDataFromFile(USER_DATA)))
	{
		PrintUserDetails(User);
	}
	else
	{
		cout << "User Your Are Searching for is NOT found please try Again ! \n";
	}


};



bool UpdateUser(string Username,string FileLocation, vector<stUser> vUsers)
{
	char Answer='N';
	stUser UserToUpdate;
	
	if (FindUserByUserName(Username, UserToUpdate, vUsers))
	{
		
		PrintUserDetails(UserToUpdate);

		cout << "Are You Sure About This User ? \n";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			for (stUser& U : vUsers)
			{
				if (Username == U.Username)
				{
					if (CheckUserPassword(UserToUpdate))
					{
						U.Permission = 0;
						ReadUserPermissions(U);
						SaveUserDataToFile(FileLocation, vUsers);
					}
					else
					{
						cout << "Wrong Password Please Try Again ! ";
						return false;
					}
				}
			
				
			}
			

		}
		else
		{
	
			return false;
		}
	}
	else
	{
		cout << "User Didn't Found !";
		return false;
	}

}
void ShowUpdateUserScreen() 
{ 
	cout << "========================================================================\n";
	cout << "\t\t\t Welcome To Update User Screen\n";
	cout << "========================================================================\n";
	
	vector<stUser>Users = LoadUserDataFromFile(USER_DATA);
	if (UpdateUser(ReadUserName(), USER_DATA, Users))
	{
		cout << "User Updated Successfully ! ";
	}




};
void GoBackToManageUserScreen() 
{ 
	cout << "\n \n Press Any Key To Back To User Management Screen ....... ";
	system("pause>0");
	ShowManageUserScreen();
};
void GoBackToLoginScreen()
{
	ShowLoginScreen();
}

void PerformMangeUserScreenOption(enManageUserOptions ManageUserOption)
{
	switch (ManageUserOption)
	{
	case eListUsers:
	{
		system("cls");
		ShowListUserScreen();
		GoBackToManageUserScreen();
		break;
	}
	case eAddNewUser:
	{
		system("cls");
		ShowAddNewUserScreen();
		GoBackToManageUserScreen();
		break;
	}
	case eDeleteUser:
	{
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageUserScreen();
		break;
	}
	case eFindUser:
	{
		system("cls");
		ShowFindUserScreen();
		GoBackToManageUserScreen();
		break;
	}
	case eUpdateUser:
	{
		system("cls");
		ShowUpdateUserScreen();
		GoBackToManageUserScreen();
		break;
	}
	case eMainMenue2:
	{
		
		GoBackToMainMenue();
		break;
	}
	break;
	}
}


void PerformTransactionsMenueOption(enTransactionOptions TransactonOption)
{
	switch (TransactonOption)
	{
	case eDeposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenue();
		break;

	}
	case eWithdraw:
	{
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionsMenue();
		break;
	}
	case eTotalBalances:
	{
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenue();
		break;

	}
	case eMainMenue:
	{
		system("cls");
		ShowMainMenue();
		break;

	}


	}
}

void DeniedAccessDeniedScreen()
{
	cout << "\n\n-------------------------------------------------\n\n";
	cout << "Access Denied \n You dont have Permission to do this, \n Please Contact Your Admin. \n ";
	cout << "-------------------------------------------------\n\n";

}

void PerformMainMenueOption(enMainMenueOptions MainMenueOption,stUser UserToCheckPer)
{
	switch (MainMenueOption)
	{

	case eListClients:
	{
		if (HasPermission(UserToCheckPer, ShowClientListPer))
		{
			system("cls");
			ShowAllClientsScreen();
			GoBackToMainMenue();
			break;
		}
		else
		{
			system("cls");
			DeniedAccessDeniedScreen();
			GoBackToMainMenue();
			break;
		}
	
	}
	case eAddNewClient:
	{
		if (HasPermission(UserToCheckPer, AddNewClientPer))
		{
			system("cls");
			AddNewClientsScreen();
			GoBackToMainMenue();
			break;
		}
		else
		{
			system("cls");
			DeniedAccessDeniedScreen();
			GoBackToMainMenue();
			break;
		}

	}
	case eDeleteClient:
	{
		if (HasPermission(UserToCheckPer, DeleteCLientPer))
		{
			system("cls");
			DeleteClientScreen();
			GoBackToMainMenue();
			break;
		}
		else
		{
			system("cls");
			DeniedAccessDeniedScreen();
			GoBackToMainMenue();
			break;
		}
	}

	case eUpdateClient:
	{
		if (HasPermission(UserToCheckPer, UpdateClientPer))
		{
			system("cls");
			UpdateClientScreen();
			GoBackToMainMenue();
			break;
		}
		else
		{
			system("cls");
			DeniedAccessDeniedScreen();
			GoBackToMainMenue();
			break;
		}

	}
	case eFindClient:
	{
		if (HasPermission(UserToCheckPer, FindClientPer))
		{
			system("cls");
			ShowFindClientScreen();
			GoBackToMainMenue();
			break;
		}
		else
		{
			system("cls");
			DeniedAccessDeniedScreen();
			GoBackToMainMenue();
			break;
		}
	}
	case eTransactions:
	{
		if (HasPermission(UserToCheckPer, TransactionsMenuePer))
		{
			system("cls");
			ShowTransactionsMenue();

			break;
		}
		else
		{
			system("cls");
			DeniedAccessDeniedScreen();
			GoBackToMainMenue();
			break;
		}


	}
	case eManageUsers:
	{
		if (HasPermission(UserToCheckPer, ManageUsersPer))
		{
			system("cls");
			ShowManageUserScreen();
			break;
		}
		else
		{
			system("cls");
			DeniedAccessDeniedScreen();
			GoBackToMainMenue();
			break;
		}
	}
	case eLogOut:
	{
		system("cls");
		GoBackToLoginScreen();
	}
	break;

	}
}
void ShowManageUserScreen()
{
	system("cls");
	cout << "========================================================================\n";
	cout << "\t\t\tWelcome To User Management Screen\n";
	cout << "========================================================================\n";
	cout << "          [1] List Users.\n";
	cout << "          [2] Add New User.\n";
	cout << "          [3] Delete User.\n";
	cout << "          [4] Update User.\n";
	cout << "          [5] Find User.\n";
	cout << "          [6] Main Menue.\n";
	cout << "========================================================================\n";
	PerformMangeUserScreenOption((enManageUserOptions)ReadManageUserScreenOption());
}
void ShowMainMenue()
{
	system("cls");
	cout << "========================================================================\n";
	cout << "\t\t\tMain Menue Screen\n";
	cout << "========================================================================\n";

	cout << "          [1] Show Client List.\n";
	cout << "          [2] Add New Client.\n";
	cout << "          [3] Delete Client.\n";
	cout << "          [4] Update Client.\n";
	cout << "          [5] Find Client.\n";
	cout << "          [6] Transactions.\n";
	cout << "          [7] Manage Users.\n";
	cout << "          [8] Logout.\n";

	cout << "========================================================================\n";
	PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption(),CURRUNT_USER);

}
void ShowTransactionsMenue()
{
	system("cls");
	cout << "========================================================================\n";
	cout << "\t\t\t\tTransactions Menue\n";
	cout << "========================================================================\n";
	cout << "          [1] Deposit.\n";
	cout << "          [2] Withdraw.\n";
	cout << "          [3] Total Balances.\n";
	cout << "          [4] Main Menue.\n";
	cout << "========================================================================\n";

	PerformTransactionsMenueOption((enTransactionOptions)ReadTransactionsMenueOption());
}



void Login()
{

	vector<stUser> vUsers = LoadUserDataFromFile(USER_DATA);

	
		string Username, Password;
		

		cout << "Please Enter Your Username: ";
		getline(cin >> ws, Username);

		cout << "Please Enter Your Password: ";
		getline(cin, Password);

		if (FindUserByUsernameAndPassword(Username, Password, vUsers, CURRUNT_USER))
			ShowMainMenue();
		else
		{
			cout << "The Username or Password you entered is wrong!\n"
				<< "Please try again...\n";
			system("pause");
			ShowLoginScreen();
		}
		
	
	

}
void ShowLoginScreen()
{
	system("cls");
	cout << "========================================================================\n";
	cout << "\t\t\tWelcome To Login Screen \n";
	cout << "========================================================================\n";

	Login();
}



int main()
{
	
	ShowLoginScreen();
	system("pause");
	return 0;
}



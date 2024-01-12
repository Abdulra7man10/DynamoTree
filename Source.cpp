#include "Queue.h"
#include "AVLTree.h"
#include "HashTable.h"
#include "DateTime.h"
#include "User.h"
#include "System.h"
#include "Post.h"
#include <vector>
#include <iomanip>
#include <string>
#include "other.h"

int main()
{
	System s;
	int ch;
	ch = IsValid(1,2,"Do you want to 1) sign-in , 2) sign_up ? ");
	
	if (ch == 1)
	{
		int x = 0;
		string username="", password="";
		do
		{
			if (x == 1)
				cout << "username doesn't exist :(\n" , username="", password="";
			else if (x == 2)
				cout << "password incorrect :(\n" , password="";
			if(username != "") cout << "username : "; cin >> username;
			if(password != "") cout << "password : "; cin >> password;
			x = s.sign_in(username, password);
		} while(x != 3);
	}

	else if (ch == 2)
	{
		int x = 0;
		string username = "", password = "";
		do
		{
			if (x == 1)
				cout << "username exist :(\n", username = "", password = "";
			cout << "username : "; cin >> username;
			cout << "password : "; cin >> password;
			x = s.sign_up(username, password);
		} while (x != 2);
	}

	//edit , profile , post , all posts , search

	int choice;
	do
	{
		system("cls");
		cout << "1- Profile\n"
			<< "2- Create a post\n"
			<< "3- Users posts\n"
			<< "4- edit info\n"
			<< "5- Search\n"
			<< "0- Exit\n";
		choice = IsValid(0,5, "Choose option : ");
		string text; char ch;
		vector<vector<Post*>> v;
		switch (choice)
		{
		case 1:
			s.display_profile();
			break;

		case 2:
		{
			cout << "Write a description : ";
			cin.ignore();
			getline(cin, text);
			s.create_post(text);
		}
		break;

		case 3:
		{
			v = s.get_all_posts();
			for (size_t i = 0; i < v.size(); i++)
			{
				size_t j = 0;
				for (; j < v[i].size(); j++)
				{
					ch = 0;
					cout << *v[i][j] << endl;
					cout << "\n-----------------------------\n\n";
					ch = IsValid(1, 4, "[1] Comment , [2] Like , [3] Next post , [4] Exit ? ");
					if (ch == 1)
					{
						string text;
						cout << "Write a comment : "; cin.ignore();
						getline(cin, text);
						s.create_comment(text, v[i][j]);
						cout << "\nDONE :)\n";
					}
					else if (ch == 2)
					{
						s.create_like(v[i][j]);
						cout << "\nDONE :)\n";
					}
					else if (ch == 4)
						break;
				}
				if (ch == 4)
				{
					break;
				}

			}
		}
		break;

		case 4:
			ch = IsValid(1, 2, "Edit what ? [1] username , [2] password : ");
			s.edit_info(ch);
			break;

		case 5:
			cout << "Write username : "; cin >> text;
			s.display_user(text);
			break;

		case 0:
			cout << "Program endded :)\n";
		}
		system("pause");
	} while (choice != 0);

	return 0;
}
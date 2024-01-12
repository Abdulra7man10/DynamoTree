#pragma once
#include "user.h"
#include "HashTable.h"
#include "AVLTree.h"
#include <vector>
#include "Post.h"

class System
{
private:
	HashTable<user> users{};
    user* ptr_user;

public:
    System()
    { }

    user* get_user()
    {
        return ptr_user;
    }

    int sign_in(string username, string pass)
    {
        // 1:username not found
        user t(username, pass, "");

        if (!users.search(t))
            return 1;

        // 2:pass wrong
        user* foundUser = users[t];
        if (foundUser->getPassword() != pass)
            return 2;

        // 3:done
        ptr_user = foundUser;
        return 3;
    }

    int sign_up(string username, string password, string path="")
    {
        user t(username, "", "");

        //username is exist
        if (users.search(t))
            return 1;

        user* new_user = new user(username, password, path);
        users.insert(*new_user);
        ptr_user = new_user;

        //done
        return 2;
    }

    int edit_info(int choice)
    {
        string str;
        switch (choice)
        {
        case 1:
            cout << "old username : " << ptr_user->getUsername() << endl;
            cout << "Eneter new username : "; cin >> str;
            ptr_user->setUsername(str);
            break;
        case 2:
            cout << "old password : " << ptr_user->getPassword() << endl;
            cout << "Eneter new password : "; cin >> str;
            ptr_user->setPassword(str);
            break;
        }
        return 2;
    }

    int create_post(string text = "", string path = "")
    {
        ptr_user->create_post(text, path);
        return 1;
    }

    void create_comment(string text, Post* ptr_post)
    {
        ptr_user->create_comment(text, ptr_post);
    }

    void create_like(Post* ptr_post)
    {
        ptr_user->create_like(ptr_post);
    }

    void displayAll()
    {
        users.print_all();
    }

    int display_user(string username)
    {
        user t(username, "", "");
        if (!users.search(t))
            return 1;

        cout << *users[t] << endl;
        return 2;
    }

    void display_profile()
    {
        ptr_user->display_user_act();
    }

    vector<vector<Post*>> get_all_posts()
    {
        vector<vector<Post*>> v;

        for (size_t i = 0; i < users.getTableSize(); i++)
        {
            size_t num_avl = users[i].count();
            for (size_t j = 0; j < num_avl; j++)
            {
                v.push_back(users[i][j].data.getPosts());
            }
        }
        return v;

    }
};


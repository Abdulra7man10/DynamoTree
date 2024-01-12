#pragma once

#include <string>
#include "Queue.h"
#include "activity.h"
#include "Post.h"
#include "Comment.h"
#include "Like.h"
#include <vector>
using namespace std;

class activity; // Forward declaration

class user {
private:
    string username;
    string password;
    string photo_path;
    Queue<activity*> activities;

public:
    user(const std::string& us, const std::string& pass, const std::string& path);
    user(const user& other);
    void setUsername(const std::string& us);
    void setPassword(const std::string& pass);
    void setPhotoPath(const std::string& path);
    string getUsername() const;
    string getPassword() const;
    string getPhotoPath() const;
    Queue<activity*>& getActivities();
    vector<Post*> getPosts();
    void create_post(const std::string& text = "", const std::string& path = "");
    void create_comment(string text, Post* p);
    void create_like(Post* p);
    user& operator=(const user& other);
    bool operator==(const user& other) const;
    operator string() const;
    void display_activity();
    void display_user_act();
    friend std::ostream& operator<<(std::ostream& os, const user& u);
    friend bool operator<(const user& left, const user& right);
    friend bool operator>(const user& left, const user& right);
};

#include "user.h"

user::user(const std::string& us, const std::string& pass, const std::string& path)
    : username(us), password(pass), photo_path(path) {}

user::user(const user& other) : username(other.username), password(other.password), 
                                photo_path(other.photo_path), activities(other.activities)
{ }


void user::setUsername(const std::string& us) {
    username = us;
}

void user::setPassword(const std::string& pass) {
    password = pass;
}

void user::setPhotoPath(const std::string& path) {
    photo_path = path;
}

std::string user::getUsername() const {
    return username;
}

std::string user::getPassword() const {
    return password;
}

std::string user::getPhotoPath() const {
    return photo_path;
}

Queue<activity*>& user::getActivities() {
    return activities;
}

vector<Post*> user::getPosts()
{
    vector<Post*> v;

    for (size_t i = 0; i < activities.getSize(); i++)
    {
        Post* post = dynamic_cast<Post*>(activities[i]);
        if (post)
            v.push_back(post);
    }

    return v;
}

void user::create_post(const std::string& text, const std::string& path) {
    activity* temp;
    if (!text.empty() && !path.empty())
        temp = new Post(this, text, path);
    else if (text.empty())
        temp = new Post(this, path, true);
    else
        temp = new Post(this, text, false);

    activities.enQueue(temp);
}

void user::create_comment(string text, Post* p)
{
    activity* temp = new Comment(this, text, p);
    activities.enQueue(temp);
}

void user::create_like(Post* p)
{
    activity* temp = new Like(this, p);
    activities.enQueue(temp);
}

user& user::operator=(const user& other) 
{
    if (this != &other) {
        username = other.username;
        password = other.password;
        photo_path = other.photo_path;
        activities = other.activities;
    }
    return *this;
}

bool user::operator==(const user& other) const 
{
    return username == other.username;
}

user::operator string() const 
{
    return username;
}

void user::display_activity() 
{
    activities.Display();
}

ostream& operator<<(std::ostream& os, const user& u) 
{
    os << u.getUsername() << endl;
    os << u.getPassword() << endl;
    //u.display_activity();
    return os;
}

void user::display_user_act()
{
    cout << getUsername() << endl;
    cout << getPassword() << endl;
    display_activity();
}


bool operator<(const user& left, const user& right)
{
    return left.getUsername() < right.getUsername();
}


bool operator>(const user& left, const user& right)
{
    return left.getUsername() > right.getUsername();
}


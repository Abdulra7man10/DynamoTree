#include "activity.h"
#include "user.h" // Include other necessary headers

activity::activity(user* u) : dateTime(true), ptr_user(u) {}

user* activity::get_user() const {
    return ptr_user;
}

void activity::display(std::ostream& os) const {
    os << get_user()->getUsername() << std::endl;
    os << dateTime << std::endl;
}

std::ostream& operator<<(std::ostream& os, const activity& act) {
    act.display(os);
    return os;
}

activity& activity::operator=(const activity& other) 
{
    if (this != &other) {
        // Copy the dateTime from other activity
        dateTime = other.dateTime;

        // Assuming user has a proper copy constructor
        if (ptr_user != nullptr) {
            delete ptr_user;
            ptr_user = nullptr;
        }
        ptr_user = new user(*(other.ptr_user));
    }
    return *this;
}
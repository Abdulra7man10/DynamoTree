#pragma once

#include <iostream>
#include "DateTime.h"

class user; // Forward declaration

class activity {
private:
    DateTime dateTime;

public:
    user* ptr_user;
    activity(user* u);

    user* get_user() const;

    virtual void display(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const activity& act);

    virtual activity& operator=(const activity& other);
};

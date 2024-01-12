#pragma once
#include "activity.h"
#include "Post.h"
class Like : public activity
{
	Post* ptr_post;
public:
	Like(user* u, Post* p) :activity(u), ptr_post(p)
	{}
	Post* get_post()
	{
		return ptr_post;
	}

	void display(std::ostream& os) const override 
	{
		activity::display(os);  // Call the base class display
		os << "Liked a post." << std::endl;
	}
	bool operator==(const Like& l) const
	{
		return false;
	}

};
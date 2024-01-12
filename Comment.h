#pragma once
#include "activity.h"
#include "Post.h"
class Comment : public activity
{
	string text;
	Post* ptr_post;
public:
	Comment(user* u, string s, Post* p) :activity(u), text(s), ptr_post(p)
	{}
	void edit(string s)
	{
		text = s;
	}
	string get_comment()
	{
		return text;
	}
	Post* get_post()
	{
		return ptr_post;
	}

	void display(std::ostream& os) const override {
		activity::display(os);  // Call the base class display
		os << "Text: " << text << std::endl;
	}

	bool operator==(const Comment& c) const
	{
		return false;
	}
};
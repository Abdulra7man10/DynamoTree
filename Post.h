#pragma once
#include"activity.h"
#include<vector>
class Like;
class Comment;

class Post : public activity
{
	string description = "";
	string path_photo = "";
	vector<Like*>likes;
	vector<Comment*>comments;


public:
	Post(user* u, string s, string p) :activity(u), description(s), path_photo(p)
	{}
	Post(user* u, string p, bool flag) : activity(u)
	{
		(flag) ? path_photo = p : description = p;

	}

	//Post(string d) : description(d) { }

	void edit_description(string s)
	{
		description = s;
	}
	void edit_photo(string s)
	{
		path_photo = s;
	}
	string get_description()
	{
		return description;
	}
	string get_photo()
	{
		return path_photo;
	}
	void push_comment(Comment* ptr_comment)
	{
		comments.push_back(ptr_comment);
	}
	void push_like(Like* ptr_like)
	{
		likes.push_back(ptr_like);
	}
	size_t size_comment() { return comments.size(); }
	size_t size_like() { return likes.size(); }

	void display(std::ostream& os) const override {
		activity::display(os);  // Call the base class display
		os << "Description: " << description <<endl;
	}
	bool operator==(const Post& p) const
	{
		return false;
	}

	Post& operator=(const Post& other)
	{
		if (this != &other)
		{
			activity::operator=(other);  // Call the base class assignment operator

			// Copy the attributes specific to Post
			description = other.description;
			path_photo = other.path_photo;
			likes = other.likes;  // Assuming Like has a proper copy constructor
			comments = other.comments;  // Assuming Comment has a proper copy constructor
		}
		return *this;
	}

};
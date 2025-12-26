#include <User.h>

User::User(int id, string userName, string hashedPassword)
    : _id(id), _userName(userName), _hashedPassword(hashedPassword)
{
}

User::~User() {}




int User::getId() const {
    return _id;
}

string User::getUserName() const {
    return _userName;
}

string User::getHashedPassword() const {
    return _hashedPassword;
}

void User::setId(int id) {
    _id = id;
}

void User::setUserName(const string& userName) {
    _userName = userName;
}

void User::setHashedPassword(const string& hashedPassword) {
    _hashedPassword = hashedPassword;
}
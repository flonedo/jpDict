#ifndef TEMPORARYUSER_H
#define TEMPORARYUSER_H
#include<user.h>

class admin: public user{
private:
    virtual QString getLabel()const;
    static std::string universalUsername;
    static std::string universalPassword;
public:
    admin(std::string un, std::string pw): user(un,pw){}
    virtual admin* clone()const;
    virtual void exportUserData(QXmlStreamWriter &) const;
};

#endif // TEMPORARYUSER_H

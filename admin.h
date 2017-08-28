#ifndef ADMIN_H
#define ADMIN_H
#include<user.h>

class admin: public user{
private:
    virtual QString getLabel()const;
public:
    admin(std::string un, std::string pw): user(un,pw){}
    virtual admin* clone()const;
    virtual void exportUserData(QXmlStreamWriter &) const;
    virtual std::string getInfo()const;
};
#endif // ADMIN_H

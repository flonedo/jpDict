#ifndef USER_H
#define USER_H
#include<string>
#include <QString>
#include<QXmlStreamWriter>


class user{
private:
    std::string username;
    std::string password;
    virtual QString getLabel()const=0;
public:
    user(std::string un, std::string pw): username(un), password(pw){}
    virtual ~user(){}
    virtual user* clone()const =0;
    bool operator==(const user&) const;
    bool operator!=(const user&)const;
    std::string getUsername()const;
    std::string getPassword()const;
    void setPassword(std::string);
    void setUsername(std::string);
    void exportData(QXmlStreamWriter&)const;
    virtual void exportUserData(QXmlStreamWriter&)const;
    virtual std::string getInfo()const;
};




#endif // USER_H

#ifndef TEACHER_H
#define TEACHER_H
#include<user.h>
class teacher: public user{
private:
    virtual QString getLabel()const;
public:
    teacher(std::string un, std::string pw): user(un,pw){}
    virtual teacher* clone()const;
    virtual void exportUserData(QXmlStreamWriter &) const;
    virtual std::string getInfo()const;
};

#endif // TEACHER_H

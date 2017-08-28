#ifndef STUDENT_H
#define STUDENT_H
#include <user.h>

class student: public user{
private:
     virtual QString getLabel()const;
     unsigned int level;
public:
    student(std::string un, std::string pw, unsigned int l): user(un, pw), level(l){}
    void setLevel(unsigned int);
    student* clone()const;
    virtual void exportUserData(QXmlStreamWriter&)const;
    virtual std::string getInfo()const;
    unsigned int getLevel()const;
};


#endif // STUDENT_H

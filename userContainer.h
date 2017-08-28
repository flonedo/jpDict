#ifndef USERCONTAINER_H
#define USERCONTAINER_H
#include <user.h>
#include <teacher.h>
#include <student.h>
#include <admin.h>
#include <list>
#include <QString>


class userContainer {
private:
    std::list<user*> userList;
    static QString label;
    static QString defaultFile;
    QString getDefaultFile();
    QString getLabel();
public:
    userContainer(){}
    bool addUser(user*); //restituisce bool a segnalare il successo dell'operazione
    bool removeUser(std::string);
    user* search(std::string)const;
    std::list<user*> search(int lev=-1)const;
    std::list<user*> searchTeachers()const;
    void changePassword(user*, std::string);
    bool fileImport();
    bool fileExport();
    void adm();
    void clean();
};

#endif // USERLIST_H

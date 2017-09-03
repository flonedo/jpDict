#include <userContainer.h>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>



user* userContainer::search(std::string uName)const{
    for(std::list<user*>::const_iterator it=userList.begin(); it != userList.end(); ++it){
        if(uName == (*it)->getUsername()){
            return *it;
        }
    }
    return 0;
}

bool userContainer::isInContainer(std::string uName)const{
    for(std::list<user*>::const_iterator it=userList.begin(); it != userList.end(); ++it){
        if(uName == (*it)->getUsername()){
            return true;
        }
    }
    return false;
}

std::list<user*> userContainer::searchTeachers()const{
    std::list<user*> res;
    for(std::list<user*>::const_iterator it=userList.begin(); it != userList.end(); ++it){
        teacher* tp=dynamic_cast<teacher*>(*it);
        if(tp){
            res.push_back((*it)->clone());
        }
    }
    return res;
}

std::list<user*> userContainer::search(int lev)const{ //se non è specificato un livello valido, restituisce tutti gli studenti
    std::list<user*> res;
    for(std::list<user*>::const_iterator it=userList.begin(); it != userList.end(); ++it){
        student* sp=dynamic_cast<student*>(*it);
        if(sp && lev != 0 && sp->getLevel() == lev){
            res.push_back((*it)->clone());
        }
        else{
            if(sp && lev == 0){
                res.push_back((*it)->clone());
            }
        }
    }
    return res;
}

bool userContainer::addUser(user* u){
    if(u && !search(u->getUsername())){
        userList.push_back(u->clone());
        return true;
    }
    return false;
}

bool userContainer::removeUser(std::string uName){
    for(std::list<user*>::const_iterator it=userList.begin(); it != userList.end(); ++it){
        if(uName == (*it)->getUsername()){
            delete *it;
            userList.erase(it);
            return true;
        }
    }
    return 0;
}

QString userContainer::getDefaultFile(){
    return "userdata.xml";
}

QString userContainer::getLabel(){
    return "USERS";
}



bool userContainer::fileExport(){
    QFile file (getDefaultFile());
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter output(&file);
    output.setAutoFormatting(true);
    output.writeStartDocument();
    output.writeStartElement(getLabel());
    for(std::list<user*>::const_iterator it=userList.begin(); it != userList.end(); ++it){
        (*it)->exportData(output);
    }
    output.writeEndElement();
    output.writeEndDocument();
    file.close();

}

bool userContainer::fileImport(){
    bool success=false;
    clean();
    QFile file(getDefaultFile());
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QXmlStreamReader in(&file);
        while(in.readNextStartElement()){
            if(in.name() == getLabel()){
                while(in.readNextStartElement()){
                    QString className=in.name().toString();
                    user* u=0;
                    std::string userName;
                    std::string passWord;
                    unsigned int level;
                    if(className == "ADMIN"){
                        in.readNextStartElement();
                        if(in.name() == "USERNAME"){
                            userName=(in.readElementText()).toStdString();
                        }
                        in.readNextStartElement();
                        if(in.name() == "PASSWORD"){
                            passWord=(in.readElementText()).toStdString();
                        }
                        u=new admin(userName, passWord);
                    }
                    else{
                        if(className == "TEACHER"){
                            in.readNextStartElement();
                            if(in.name() == "USERNAME"){
                                userName=(in.readElementText()).toStdString();
                            }
                            in.readNextStartElement();
                            if(in.name() == "PASSWORD"){
                                passWord=(in.readElementText()).toStdString();
                            }
                            u=new teacher(userName, passWord);
                        }
                        else{
                            if(className == "STUDENT"){
                                in.readNextStartElement();
                                if(in.name() == "USERNAME"){
                                    userName=(in.readElementText()).toStdString();
                                }
                                in.readNextStartElement();
                                if(in.name() == "PASSWORD"){
                                    passWord=(in.readElementText()).toStdString();
                                }
                                in.readNextStartElement();
                                if(in.name() == "LEVEL"){
                                    level=in.readElementText().toInt();
                                }
                                u=new student(userName, passWord, level);
                            }
                        }
                    }
                    if(u){
                        addUser(u);
                        delete u;
                        success=true;
                    }
                    in.skipCurrentElement();
                }
            }
        }

    }
    file.close();
    return success;
}

void userContainer:: clean(){
    for(std::list<user*>::iterator it=userList.begin(); it != userList.end(); ++it){
        delete *it;
        userList.erase(userList.begin(),userList.end());
    }
}

void userContainer::adm(){
    clean();
    user* ad=new admin("admin","admin");
    addUser(ad);
}

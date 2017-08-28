#include <user.h>

bool user::operator==(const user& u)const{
    return(username == u.username && password == u.password);
}

bool user::operator!=(const user& u)const{
    return !(username == u.username && password == u.password);
}



std::string user::getUsername()const{
    return username;
}

std::string user::getPassword()const{
    return password;
}

void user::setPassword(std::string pw){
    password=pw;
}

void user::setUsername(std::string un){
    username=un;
}

void user::exportData(QXmlStreamWriter& out)const{
    out.writeStartElement(getLabel());
    exportUserData(out);
    out.writeEndElement();
}

void user::exportUserData(QXmlStreamWriter& out)const{
    out.writeTextElement("USERNAME", QString::fromStdString(getUsername()));
    out.writeTextElement("PASSWORD", QString::fromStdString(getPassword()));
}

std::string user:: getInfo()const{
    std::string info;
    info.append("Username: ");
    info.append(username);
    return info;
}

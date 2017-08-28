#include <teacher.h>

QString teacher::getLabel()const{
    return "TEACHER";
}
teacher* teacher::clone()const{
    return new teacher(*this);
}


void teacher:: exportUserData(QXmlStreamWriter & out) const{
    user::exportUserData(out);
}


std::string teacher::getInfo()const{
    std::string info="Teacher\n";
    info.append(user::getInfo());
    return info;

}

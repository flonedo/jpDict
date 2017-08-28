#include <student.h>

void student::setLevel(unsigned int l){
    level=l;
}

student* student::clone()const{
    return new student(*this);

}

void student::exportUserData(QXmlStreamWriter& out) const{
    user::exportUserData(out);
    out.writeTextElement("LEVEL", QString::number(level,10));
}

QString student::getLabel()const{
    return "STUDENT";
}

unsigned int student:: getLevel()const{
    return level;
}

std::string student::getInfo()const{
    QString info="Student";
    info.append("\n");
    info.append(QString::fromStdString(user::getInfo()));
    info.append("\nJLPT level: N");
    info.append(QString::number(level,10));
    return info.toStdString();
}

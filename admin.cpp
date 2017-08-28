#include <admin.h>


QString admin::getLabel()const{
    return "ADMIN";
}
admin* admin::clone()const{
    return new admin(*this);
}


void admin:: exportUserData(QXmlStreamWriter & out) const{
    user::exportUserData(out);
}

std::string admin::getInfo()const{
    std::string info="Admin\n";
    info.append(user::getInfo());
    return info;
}

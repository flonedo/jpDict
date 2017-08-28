#include "mainwindow.h"
#include <QApplication>
#include<userContainer.h>
#include<kanjicontainer.h>
#include<dictionary.h>
#include<login.h>
#include<workpanel.h>
#include<qmessagebox.h>
#include<panelwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    userContainer USERLIST;
    if(!USERLIST.fileImport()){
        USERLIST.adm();
        USERLIST.fileExport();
        QMessageBox error;
        error.setText("Error. Unable to open user file.");
        error.setWindowTitle("Error");
        error.show();
        error.exec();
    }
    user* LOGUSER=0;
    login* LOGIN=new login(USERLIST, &LOGUSER);
    bool exit=false;
    while(!exit){
        LOGUSER=0;
        LOGIN->clear();
        LOGIN->exec();
        if(LOGUSER == 0){
            exit=true;
        }
        else{
            bool relog=false;
            panelWindow PW(USERLIST, LOGUSER, relog);
            PW.setWindowModality(Qt::ApplicationModal);
            PW.show();
            a.exec();
            if(!relog){
                exit=true;
            }
        }

    }

return 0;



}

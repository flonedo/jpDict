#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<userContainer.h>
#include<login.h>


#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H

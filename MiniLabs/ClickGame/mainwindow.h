#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "counter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void MyButtonClick();

private:
    Ui::MainWindow *ui;
    Counter c;
};
#endif // MAINWINDOW_H

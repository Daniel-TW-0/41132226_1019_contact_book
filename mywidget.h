#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

void Write(QString Filename, QString str);

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
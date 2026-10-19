#include "mywidget.h"
#include "ui_mywidget.h"
#include <QTableWidgetItem>
#include <QStringList>

QString mFilename = "C:/Qt_example/test/myfile.txt";

void Write(QString Filename, QString str)
{
    QFile mFile(Filename);

    if (!mFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "could not open file for write";
        return;
    }

    QTextStream out(&mFile);
    out << str;
    mFile.flush();
    mFile.close();
}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);
    QStringList ColTitle;
    ColTitle << QStringLiteral("學號")
             << QStringLiteral("班級")
             << QStringLiteral("姓名")
             << QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels(ColTitle);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    QTableWidgetItem *inputRow1 = new QTableWidgetItem(ui->lineEdit->text());
    QTableWidgetItem *inputRow2 = new QTableWidgetItem(ui->lineEdit_2->text());
    QTableWidgetItem *inputRow3 = new QTableWidgetItem(ui->lineEdit_3->text());
    QTableWidgetItem *inputRow4 = new QTableWidgetItem(ui->lineEdit_4->text());

    int targetRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(targetRow);

    ui->tableWidget->setItem(targetRow, 0, inputRow1);
    ui->tableWidget->setItem(targetRow, 1, inputRow2);
    ui->tableWidget->setItem(targetRow, 2, inputRow3);
    ui->tableWidget->setItem(targetRow, 3, inputRow4);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

void MyWidget::on_pushButton_2_clicked()
{
    QString str = "";
    int rows = ui->tableWidget->rowCount();
    int cols = ui->tableWidget->columnCount();

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            QTableWidgetItem *item = ui->tableWidget->item(r, c);
            if (item)
            {
                str += item->text() + ",";
            }
        }
        str += "\n";
    }

    Write(mFilename, str);
}

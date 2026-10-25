#include "mywidget.h"
#include "ui_mywidget.h"
#include <QTableWidgetItem>
#include <QStringList>

QString mFilename = "C:/Qt_example/41132226_1019_contact_book/csv/myfile.csv";

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
    ui->tableWidget->setItem(targetRow, 3, inputRow4);
    ui->tableWidget->setItem(targetRow, 2, inputRow3);

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
        QStringList rowData;
        for (int c = 0; c < cols; ++c)
        {
            QTableWidgetItem *item = ui->tableWidget->item(r, c);
            rowData << (item ? item->text() : "");
        }
        str += rowData.join(",") + "\n";
    }

    Write(mFilename, str);
}

void MyWidget::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        QStringLiteral("選擇要匯入的檔案"),
        ".", // 開啟當前專案目錄
        QStringLiteral("CSV 檔案 (*.csv);;所有檔案 (*.*)")
        );

    if (fileName.isEmpty())
        return;

    QFile mFile(fileName);
    if (!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "無法開啟檔案！";
        return;
    }

    QTextStream in(&mFile);
    ui->tableWidget->setRowCount(0);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QStringList dataList = line.split(",");
        int targetRow = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(targetRow);

        for (int c = 0; c < dataList.size() && c < 4; ++c)
        {
            ui->tableWidget->setItem(targetRow, c, new QTableWidgetItem(dataList[c]));
        }
    }

    mFile.close();
}
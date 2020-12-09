#include "editborrowdialog.h"
#include "ui_editborrowdialog.h"
#include <QDate>
#include <QMessageBox>

editBorrowDialog::editBorrowDialog(QWidget *parent, QString returndate) :
    QDialog(parent),
    ui(new Ui::editBorrowDialog)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::fromString(returndate, "dd.MM.yyyy"));
}

editBorrowDialog::~editBorrowDialog()
{
    delete ui;
}

void editBorrowDialog::on_buttonBox_rejected()
{
    reject();
}

void editBorrowDialog::on_buttonBox_accepted()
{
    QMessageBox msgBox;
    if(ui->dateEdit->text().isEmpty() ||
            ui->dateEdit->date() <= QDate::currentDate()){
        msgBox.setText("Pole musi być wypełnione datą dzień dłuższą od dzisiaj!");
        msgBox.exec();
    }else {
        accept();
    }

}

QString editBorrowDialog::returndate() const{
    return ui->dateEdit->text();
}

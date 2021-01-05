#include "editclientdialog.h"
#include "ui_editclientdialog.h"
#include <QMessageBox>
#include "others.h"

editClientDialog::editClientDialog(QWidget *parent,  QString name, QString surname, QString pesel, QString phone, QString email) :
    QDialog(parent),
    ui(new Ui::editClientDialog)
{
    ui->setupUi(this);

    ui->peselClientEdit->setMaxLength(11);
    ui->phoneClientEdit->setMaxLength(9);

    ui->nameClientEdit->setText(name);
    ui->surnameClientEdit->setText(surname);
    ui->peselClientEdit->setText(pesel);
    ui->phoneClientEdit->setText(phone);
    ui->emailClientEdit->setText(email);

}

editClientDialog::~editClientDialog()
{
    delete ui;
}

void editClientDialog::on_buttonBox_accepted()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Błąd");
    bool peselConversion, phoneConversion;
    ui->peselClientEdit->text().toULongLong(&peselConversion);
    ui->phoneClientEdit->text().toUInt(&phoneConversion);

    if(
            ui->nameClientEdit->text().isEmpty() ||
            ui->surnameClientEdit->text().isEmpty() ||
            ui->peselClientEdit->text().isEmpty() ||
            ui->phoneClientEdit->text().isEmpty() ||
            ui->emailClientEdit->text().isEmpty())
    {
        msgBox.setText("Wszystkie pola muszą być wypełnione!");
        msgBox.exec();
    }else{
        if(peselConversion && phoneConversion && ui->peselClientEdit->text().length() == 11 && ui->phoneClientEdit->text().length() == 9 && Email_check(ui->emailClientEdit->text()))
            accept();

        if(!peselConversion || ui->peselClientEdit->text().length() < 11){
            msgBox.setText("Błąd!  Sprawdź poprawność numeru pesel!");
            msgBox.exec();
        }
        if(!phoneConversion || ui->phoneClientEdit->text().length() < 9){
            msgBox.setText("Błąd!  Sprawdź poprawność numeru telefonu!");
            msgBox.exec();
        }
        if(!Email_check(ui->emailClientEdit->text())) {
            msgBox.setText("Błąd! Sprawdź poprawność adresu email!");
            msgBox.exec();
        }
    }
}

void editClientDialog::on_buttonBox_rejected()
{
    reject();
}

QString editClientDialog::name() const{
    return ui->nameClientEdit->text();
}

QString editClientDialog::surname() const{
    return ui->surnameClientEdit->text();
}

QString editClientDialog::pesel() const{
    return ui->peselClientEdit->text();
}

QString editClientDialog::phone() const{
    return ui->phoneClientEdit->text();
}

QString editClientDialog::email() const{
    return ui->emailClientEdit->text();
}


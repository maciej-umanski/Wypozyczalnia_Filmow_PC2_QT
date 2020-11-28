#include "addclientdialog.h"
#include "ui_addClientDialog.h"
#include "QMessageBox"

AddClientDialog::AddClientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClientDialog)
{
    ui->setupUi(this);
}

AddClientDialog::~AddClientDialog()
{
    delete ui;
}

void AddClientDialog::on_buttonBox_accepted()
{
    QMessageBox msgBox;
    bool peselConversion, phoneConversion;
    ui->peselClientEdit->text().toInt(&peselConversion);
    ui->phoneClientEdit->text().toInt(&phoneConversion);

    if(peselConversion && phoneConversion)
        accept();
    if(!peselConversion){
        msgBox.setText("Błąd!  Sprawdź poprawność numeru pesel!");
        msgBox.exec();
    }
    if(!phoneConversion){
        msgBox.setText("Błąd!  Sprawdź poprawność numeru telefonu!");
        msgBox.exec();
    }

}

void AddClientDialog::on_buttonBox_rejected()
{
    reject();
}

QString AddClientDialog::name() const{
    return ui->nameClientEdit->text();
}

QString AddClientDialog::surname() const{
    return ui->surnameClientEdit->text();
}

int AddClientDialog::pesel() const{
    bool ok;
    int ret = ui->peselClientEdit->text().toInt(&ok);
    if(ok)
        return ret;
    else
        return 0;
}

int AddClientDialog::phone() const{
    bool ok;
    int ret = ui->phoneClientEdit->text().toInt(&ok);
    if(ok)
        return ret;
    else
        return 0;
}

QString AddClientDialog::email() const{
    return ui->emailClientEdit->text();
}

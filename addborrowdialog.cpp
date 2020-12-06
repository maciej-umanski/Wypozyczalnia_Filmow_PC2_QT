#include "addborrowdialog.h"
#include "ui_addborrowdialog.h"
#include <QDate>
#include <QMessageBox>
#include <QString>

addBorrowDialog::addBorrowDialog(QWidget *parent, QTableWidget *clientsTable, QTableWidget *moviesTable) :
    QDialog(parent),
    ui(new Ui::addBorrowDialog)
{
    ui->setupUi(this);

    //PRZEPISANIE TABELI KLIENTÓW
    for(int i=0;i<clientsTable->rowCount();i++) {
        ui->borrowsClientsTable->insertRow(i);
        for(int j=0;j<clientsTable->columnCount();j++){
            QString temp = clientsTable->item(i, j)->text();
            ui->borrowsClientsTable->setItem(i, j, new QTableWidgetItem(temp));
        }
    }
    //PRZEPISANIE TABELI FILMÓW
    for(int i=0;i<moviesTable->rowCount();i++) {
        ui->borrowsMoviesTable->insertRow(i);
        for(int j=0;j<moviesTable->columnCount();j++){
            QString temp = moviesTable->item(i, j)->text();
            ui->borrowsMoviesTable->setItem(i, j, new QTableWidgetItem(temp));
        }
    }
    ui->borrowdate->setDate(QDate::currentDate());
    ui->returndate->setDate(QDate::currentDate());
}

addBorrowDialog::~addBorrowDialog()
{
    delete ui;
}


void addBorrowDialog::on_buttonBox_rejected()
{
    reject();
}

QString addBorrowDialog::return_date() const {
    return ui->returndate->text();
}

QString addBorrowDialog::borrow_date() const {
    return ui->borrowdate->text();
}

QString addBorrowDialog::arrear() const {
    return "0";
}

QString addBorrowDialog::title() const {
    return ui->chosenMovieLabel->text();
}

QString addBorrowDialog::name() const {
    return ui->chosenClientName->text();
}

QString addBorrowDialog::surname() const {
    return ui->chosenClientSurname->text();
}


void addBorrowDialog::on_borrowsMoviesTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    ui->chosenMovieLabel->setText(ui->borrowsMoviesTable->item(currentRow, 0)->text());
}

void addBorrowDialog::on_borrowsClientsTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    ui->chosenClientName->setText(ui->borrowsClientsTable->item(currentRow, 0)->text());
    ui->chosenClientSurname->setText(ui->borrowsClientsTable->item(currentRow, 1)->text());
}

void addBorrowDialog::on_buttonBox_accepted()
{
    QMessageBox msgBox;
    QDate borrowdate = ui->borrowdate->date(),
            returndate = ui->returndate->date();
    int datediff = borrowdate.daysTo(returndate);
    if(
            ui->chosenClientName->text() == "BRAK" ||
            ui->chosenMovieLabel->text() == "BRAK")
    {
        msgBox.setText("Wszystkie pola muszą być wypełnione!");
        msgBox.exec();
    }
    else if(datediff < 1) {
            msgBox.setText("Minimalny czas wypożyczenia wynosi 1 dzień!");
            msgBox.exec();
        }
    else {
        accept();
    }
}

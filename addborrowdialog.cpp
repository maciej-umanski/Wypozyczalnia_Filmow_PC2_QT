#include "addborrowdialog.h"
#include "ui_addborrowdialog.h"
#include <QDate>
#include <QMessageBox>
#include <QString>

int clientRow, movieRow;
QTableWidget *moviesTableTemp;

addBorrowDialog::addBorrowDialog(QWidget *parent, QTableWidget *clientsTable, QTableWidget *moviesTable) :
    QDialog(parent),
    ui(new Ui::addBorrowDialog)
{
    ui->setupUi(this);
    ui->borrowsClientsTable->setSortingEnabled(true);
    ui->borrowsMoviesTable->setSortingEnabled(true);

    //PRZEPISANIE TABELI KLIENTÓW
    for(int i=0;i<clientsTable->rowCount();i++) {
        ui->borrowsClientsTable->insertRow(i);
        for(int j=0;j<clientsTable->columnCount();j++){
            QString temp = clientsTable->item(i, j)->text();
            ui->borrowsClientsTable->setItem(i, j, new QTableWidgetItem(temp));
        }
    }

    /* Twój stary kod, nie usuwam na wypadek gdybyś coś potrzebował
    for(int i=0;i<moviesTable->rowCount();i++) {
        ui->borrowsMoviesTable->insertRow(i);
        for(int j=0;j<moviesTable->columnCount();j++){
            QString temp = moviesTable->item(i, j)->text();
            ui->borrowsMoviesTable->setItem(i, j, new QTableWidgetItem(temp));
        }
    }*/

    //PRZEPISANIE TABELI FILMÓW
    for(int i = 0; i < moviesTable->rowCount();i++){
       if(moviesTable->item(i,DOSTEPNE)->text().toInt() > 0){
           ui->borrowsMoviesTable->insertRow(ui->borrowsMoviesTable->rowCount());
           int currentRow = ui->borrowsMoviesTable->rowCount()-1;
           for(int j = 0; j < moviesTable->columnCount(); j++){
               QString temp = moviesTable->item(i, j)->text();
               ui->borrowsMoviesTable->setItem(currentRow, j, new QTableWidgetItem(temp));
           }
       }
    }

    ui->borrowdate->setDate(QDate::currentDate());
    ui->returndate->setDate(QDate::currentDate());

    moviesTableTemp = moviesTable;
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

QString addBorrowDialog::charge() const {
    return ui->chargevalue->text();
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

int addBorrowDialog::chosenClientRow() const{
    return clientRow;
}

int addBorrowDialog::chosenMovieRow() const{
    QString title = ui->borrowsMoviesTable->item(movieRow,TYTUL)->text();
    QString director = ui->borrowsMoviesTable->item(movieRow,REZYSER)->text();
    QString genre = ui->borrowsMoviesTable->item(movieRow,GATUNEK)->text();
    QString year = ui->borrowsMoviesTable->item(movieRow,ROK)->text();

    QList<QTableWidgetItem *> repeated_items = moviesTableTemp->findItems(title, Qt::MatchExactly);

    for(int i = 0; i < repeated_items.size() ; i++){
        int match_item = 0;
        QString search_table[4] = {title, director, genre, year};
        int row = repeated_items[i]->row();
        for(int j = 0; j < 4; j++){
            QTableWidgetItem *item = moviesTableTemp->item(row, j);
            if(item->text() == search_table[j])
                match_item++;
        }
        if(match_item == 4){
            return row;
        }
    }
    return 0;
}

void addBorrowDialog::on_borrowsMoviesTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    ui->chosenMovieLabel->setText(ui->borrowsMoviesTable->item(currentRow, 0)->text());
    movieRow = currentRow;
}

void addBorrowDialog::on_borrowsClientsTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    ui->chosenClientName->setText(ui->borrowsClientsTable->item(currentRow, 0)->text());
    ui->chosenClientSurname->setText(ui->borrowsClientsTable->item(currentRow, 1)->text());
    clientRow = currentRow;
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

void addBorrowDialog::on_searchClientButton_clicked()
{
    if(ui->searchClientField->text().isEmpty()){
        for(int i = 0; i < ui->borrowsClientsTable->rowCount(); i++){
            ui->borrowsClientsTable->showRow(i);
        }
    }else{
        QString searchedPhrase = ui->searchClientField->text();
        QList<QTableWidgetItem *> foundItems = ui->borrowsClientsTable->findItems(searchedPhrase, Qt::MatchContains);

        for(int i = 0; i < ui->borrowsClientsTable->rowCount(); i++){
            ui->borrowsClientsTable->hideRow(i);
        }

        for(int i = 0; i < foundItems.size(); i++){
            ui->borrowsClientsTable->showRow(foundItems[i]->row());
        }
    }

}

void addBorrowDialog::on_searchMovieButton_clicked()
{
    if(ui->searchMovieField->text().isEmpty()){
        for(int i = 0; i < ui->borrowsMoviesTable->rowCount(); i++){
            ui->borrowsMoviesTable->showRow(i);
        }
    }else{
        QString searchedPhrase = ui->searchMovieField->text();
        QList<QTableWidgetItem *> foundItems = ui->borrowsMoviesTable->findItems(searchedPhrase, Qt::MatchContains);

        for(int i = 0; i < ui->borrowsMoviesTable->rowCount(); i++){
            ui->borrowsMoviesTable->hideRow(i);
        }

        for(int i = 0; i < foundItems.size(); i++){
            ui->borrowsMoviesTable->showRow(foundItems[i]->row());
        }
    }
}

void addBorrowDialog::on_searchClientField_returnPressed()
{
    addBorrowDialog::on_searchClientButton_clicked();
}

void addBorrowDialog::on_searchMovieField_returnPressed()
{
    addBorrowDialog::on_searchMovieButton_clicked();
}

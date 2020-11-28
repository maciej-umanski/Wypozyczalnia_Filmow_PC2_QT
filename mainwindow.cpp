#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <addclientdialog.h>
#include <addmoviedialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addClientButton_clicked()
{
    AddClientDialog addClientDialog;
    int ret = addClientDialog.exec();
    if(ret == QDialog::Rejected)
        return;

    QString name = addClientDialog.name();
    QString surname = addClientDialog.surname();
    QString email = addClientDialog.email();
    QString pesel = addClientDialog.pesel();
    QString phone = addClientDialog.phone();

    QList<QTableWidgetItem *> ItemList = ui->clientsTable->findItems(pesel, Qt::MatchExactly);

    if(ItemList.count() > 0){
        QMessageBox msgBox;
        msgBox.setText("Klient o danym peselu już istnieje w bazie!");
        msgBox.exec();
        return;
    }

    ui->clientsTable->insertRow(ui->clientsTable->rowCount());
    int currentRow = ui->clientsTable->rowCount()-1;
    ui->clientsTable->setItem(currentRow, IMIE, new QTableWidgetItem(name));
    ui->clientsTable->setItem(currentRow, NAZWISKO, new QTableWidgetItem(surname));
    ui->clientsTable->setItem(currentRow, EMAIL, new QTableWidgetItem(email));
    ui->clientsTable->setItem(currentRow, PESEL, new QTableWidgetItem(pesel));
    ui->clientsTable->setItem(currentRow, TELEFON, new QTableWidgetItem(phone));
    ui->clientsTable->setItem(currentRow, POSIADANE_FILMY, new QTableWidgetItem("0"));

}

void MainWindow::on_delClientButton_clicked()
{
    QMessageBox msgBox;
    QList<QTableWidgetItem *> items = ui->clientsTable->selectedItems();
    if(items.isEmpty()){
        msgBox.setText("Żadna z kolumn nie jest wybrana!");
        msgBox.exec();
    }else if(items.size() > 6){
        msgBox.setText("Wybrano więcej niż 1 kolumnę!");
        msgBox.exec();
    }else{
        if(items[5]->text().toInt()!=0){
            msgBox.setText("Nie można usunąć klienta ponieważ ma on aktualnie wypożyczony film!");
            msgBox.exec();
            return;
        }
        if(QMessageBox::Yes == QMessageBox::question(this, tr("Usuwanie klienta"), tr("Czy na pewno chcesz kontyunuować?"))){
            int rowToRemove = ui->clientsTable->row(items[0]);
            ui->clientsTable->removeRow(rowToRemove);
        }
    }
}

void MainWindow::on_clientsTable_cellClicked(int row, int column)
{
    ui->clientsTable->selectRow(row);
}

void MainWindow::on_moviesTable_cellClicked(int row, int column)
{
    ui->moviesTable->selectRow(row);
}

void MainWindow::on_delMovieButton_clicked()
{
    QMessageBox msgBox;
    QList<QTableWidgetItem *> items = ui->moviesTable->selectedItems();
    if(items.isEmpty()){
        msgBox.setText("Żadna z kolumn nie jest wybrana!");
        msgBox.exec();
    }else if(items.size() > 6){
        msgBox.setText("Wybrano więcej niż 1 kolumnę!");
        msgBox.exec();
    }else{
        if(items[5]->text().toInt()==0){
            msgBox.setText("Nie można usunąć filmu ponieważ wszystkie egzemplarze są wypożyczone!");
            msgBox.exec();
            return;
        }
        if(QMessageBox::Yes == QMessageBox::question(this, tr("Usuwanie filmu"), tr("Czy na pewno chcesz kontyunuować?"))){
            int rowToRemove = ui->moviesTable->row(items[0]);
            ui->moviesTable->removeRow(rowToRemove);
        }
    }
}

void MainWindow::on_addMovieButton_clicked()
{
    addMovieDialog addMovieDialog;
    int ret = addMovieDialog.exec();
    if(ret == QDialog::Rejected)
        return;

    QString title = addMovieDialog.title();
    QString director = addMovieDialog.director();
    QString genre = addMovieDialog.genre();
    QString year = addMovieDialog.year();
    QString count = addMovieDialog.count();

    // TODO: sprawdzanie czy film istnieje i zwiększanie jego ilości

    ui->moviesTable->insertRow(ui->moviesTable->rowCount());
    int currentRow = ui->moviesTable->rowCount()-1;

    ui->moviesTable->setItem(currentRow, TYTUL, new QTableWidgetItem(title));
    ui->moviesTable->setItem(currentRow, REZYSER, new QTableWidgetItem(director));
    ui->moviesTable->setItem(currentRow, GATUNEK, new QTableWidgetItem(genre));
    ui->moviesTable->setItem(currentRow, ROK, new QTableWidgetItem(year));
    ui->moviesTable->setItem(currentRow, WYPOZYCZONE, new QTableWidgetItem("0"));
    ui->moviesTable->setItem(currentRow, DOSTEPNE, new QTableWidgetItem(count));
}

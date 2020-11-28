#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <addclientdialog.h>

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
    int pesel = addClientDialog.pesel();
    int phone = addClientDialog.phone();

    //TODO: sprawdzanie czy klient istnieje już w bazie.


    ui->clientsTable->insertRow(ui->clientsTable->rowCount());
    int currentRow = ui->clientsTable->rowCount()-1;
    ui->clientsTable->setItem(currentRow, IMIE, new QTableWidgetItem(name));
    ui->clientsTable->setItem(currentRow, NAZWISKO, new QTableWidgetItem(surname));
    ui->clientsTable->setItem(currentRow, EMAIL, new QTableWidgetItem(email));
    ui->clientsTable->setItem(currentRow, PESEL, new QTableWidgetItem(QString::number(pesel)));
    ui->clientsTable->setItem(currentRow, TELEFON, new QTableWidgetItem(QString::number(phone)));
    ui->clientsTable->setItem(currentRow, POSIADANE_FILMY, new QTableWidgetItem(QString::number(0)));

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

}

void MainWindow::on_addMovieButton_clicked()
{


}

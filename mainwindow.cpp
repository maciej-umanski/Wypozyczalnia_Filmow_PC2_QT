#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <addclientdialog.h>
#include <addmoviedialog.h>
#include <editclientdialog.h>
#include <editmoviedialog.h>

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

    QTableWidgetItem *name_item = new QTableWidgetItem(name);
    QTableWidgetItem *surname_item = new QTableWidgetItem(surname);
    QTableWidgetItem *email_item = new QTableWidgetItem(email);
    QTableWidgetItem *pesel_item = new QTableWidgetItem(pesel);
    QTableWidgetItem *phone_item = new QTableWidgetItem(phone);
    QTableWidgetItem *count_item = new QTableWidgetItem("0");

    name_item->setFlags(name_item->flags() ^ Qt::ItemIsEditable);
    surname_item->setFlags(surname_item->flags() ^ Qt::ItemIsEditable);
    email_item->setFlags(email_item->flags() ^ Qt::ItemIsEditable);
    pesel_item->setFlags(pesel_item->flags() ^ Qt::ItemIsEditable);
    phone_item->setFlags(phone_item->flags() ^ Qt::ItemIsEditable);
    count_item->setFlags(count_item->flags() ^ Qt::ItemIsEditable);

    ui->clientsTable->setItem(currentRow, IMIE, name_item);
    ui->clientsTable->setItem(currentRow, NAZWISKO, surname_item);
    ui->clientsTable->setItem(currentRow, EMAIL, email_item);
    ui->clientsTable->setItem(currentRow, PESEL, pesel_item);
    ui->clientsTable->setItem(currentRow, TELEFON, phone_item);
    ui->clientsTable->setItem(currentRow, POSIADANE_FILMY, count_item);

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
        if(items[4]->text().toInt()==0){
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
    QString available = addMovieDialog.available();

    QList<QTableWidgetItem *> repeated_items = ui->moviesTable->findItems(title, Qt::MatchExactly);

    for(int i = 0; i < repeated_items.size() ; i++){
        int match_item = 0;
        QString search_table[4] = {title, director, genre, year};
        int row = repeated_items[i]->row();
        for(int j = 0; j < 4; j++){
            QTableWidgetItem *item = ui->moviesTable->item(row, j);
            if(item->text() == search_table[j])
                match_item++;
        }
        if(match_item == 4){
            if(QMessageBox::Yes == QMessageBox::question(this, tr("Edycja filmu"), tr("W bazie już istnieje taki film, czy chcesz złączyć ilość egzemplarzy?"))){
                QTableWidgetItem *item = ui->moviesTable->item(row, 4);
                int data = available.toInt();
                data = data + item->text().toInt();
                item->setText(QString::number(data));
            }
            return;
        }

    }

    QTableWidgetItem *title_item = new QTableWidgetItem(title);
    QTableWidgetItem *director_item = new QTableWidgetItem(director);
    QTableWidgetItem *genre_item = new QTableWidgetItem(genre);
    QTableWidgetItem *year_item = new QTableWidgetItem(year);
    QTableWidgetItem *available_item = new QTableWidgetItem(available);
    QTableWidgetItem *borrowed_item = new QTableWidgetItem("0");

    title_item->setFlags(title_item->flags() ^ Qt::ItemIsEditable);
    director_item->setFlags(director_item->flags() ^ Qt::ItemIsEditable);
    genre_item->setFlags(genre_item->flags() ^ Qt::ItemIsEditable);
    year_item->setFlags(year_item->flags() ^ Qt::ItemIsEditable);
    available_item->setFlags(available_item->flags() ^ Qt::ItemIsEditable);
    borrowed_item->setFlags(borrowed_item->flags() ^ Qt::ItemIsEditable);


    ui->moviesTable->insertRow(ui->moviesTable->rowCount());
    int currentRow = ui->moviesTable->rowCount()-1;

    ui->moviesTable->setItem(currentRow, TYTUL, title_item);
    ui->moviesTable->setItem(currentRow, REZYSER, director_item);
    ui->moviesTable->setItem(currentRow, GATUNEK, genre_item);
    ui->moviesTable->setItem(currentRow, ROK, year_item);
    ui->moviesTable->setItem(currentRow, DOSTEPNE, available_item);
    ui->moviesTable->setItem(currentRow, WYPOZYCZONE, borrowed_item);
}

void MainWindow::on_editClientButton_clicked()
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
            msgBox.setText("Nie można edytować klienta ponieważ ma on aktualnie wypożyczony film!");
            msgBox.exec();
            return;
        }

        QString bufor_pesel = items[2]->text();

        editClientDialog editClientDialog(nullptr, items[0]->text(), items[1]->text(), items[2]->text(), items[3]->text(), items[4]->text());
        int ret = editClientDialog.exec();
        if(ret == QDialog::Rejected)
            return;

        QString name = editClientDialog.name();
        QString surname = editClientDialog.surname();
        QString email = editClientDialog.email();
        QString pesel = editClientDialog.pesel();
        QString phone = editClientDialog.phone();

        QList<QTableWidgetItem *> ItemList = ui->clientsTable->findItems(pesel, Qt::MatchExactly);

        int row_bufor = items[0]->row();

        if(pesel == bufor_pesel || (pesel != bufor_pesel && ItemList.count() == 0)){
            ui->clientsTable->item(row_bufor,IMIE)->setText(name);
            ui->clientsTable->item(row_bufor,NAZWISKO)->setText(surname);
            ui->clientsTable->item(row_bufor,PESEL)->setText(pesel);
            ui->clientsTable->item(row_bufor,TELEFON)->setText(phone);
            ui->clientsTable->item(row_bufor,EMAIL)->setText(email);
        }else{
            QMessageBox msgBox;
            msgBox.setText("Inny Klient o danym peselu już istnieje w bazie!");
            msgBox.exec();
            return;
        }
    }
}

void MainWindow::on_editMovieButton_clicked()
{
    QList<QTableWidgetItem *> items = ui->moviesTable->selectedItems();
    QMessageBox msgBox;
    if(items.isEmpty()){
        msgBox.setText("Żaden wiersz nie został wybrany!");
        msgBox.exec();
    }else if(items.size() > 6){
        msgBox.setText("Wybrano więcej niż 1 wiersz!");
        msgBox.exec();
    }else{
        if(items[4]->text().toInt()==0){
            msgBox.setText("Nie można edytować filmu ponieważ wszystkie egzemplarze są wypożyczone!");
            msgBox.exec();
            return;
        }

        int selected_row = items[0]->row();

        editMovieDialog editMovieDialog(nullptr, items[TYTUL]->text(), items[REZYSER]->text(), items[GATUNEK]->text() ,items[ROK]->text(), items[DOSTEPNE]->text());
        int ret = editMovieDialog.exec();
        if(ret == QDialog::Rejected)
            return;

        QString title = editMovieDialog.title();
        QString director = editMovieDialog.director();
        QString genre = editMovieDialog.genre();
        QString year = editMovieDialog.year();
        QString available = editMovieDialog.available();

        QList<QTableWidgetItem *> repeated_items = ui->moviesTable->findItems(title, Qt::MatchExactly);

        for(int i = 0; i < repeated_items.size() ; i++){
            int match_item = 0;
            QString search_table[4] = {title, director, genre, year};
            int row = repeated_items[i]->row();
            for(int j = 0; j < 4; j++){
                QTableWidgetItem *item = ui->moviesTable->item(row, j);
                if(item->text() == search_table[j]){
                    match_item++;

                }
            }
            if(match_item == 4 && row != selected_row){
                if(QMessageBox::Yes == QMessageBox::question(this, tr("Edycja filmu"), tr("W bazie już istnieje taki film, czy chcesz złączyć ilość egzemplarzy?"))){
                    QTableWidgetItem *item = ui->moviesTable->item(row, 4);
                    int data = available.toInt();
                    data = data + item->text().toInt();
                    item->setText(QString::number(data));
                    ui->moviesTable->removeRow(selected_row);
                }
                break;
            }else{
                ui->moviesTable->item(selected_row, TYTUL)->setText(title);
                ui->moviesTable->item(selected_row, REZYSER)->setText(director);
                ui->moviesTable->item(selected_row, GATUNEK)->setText(genre);
                ui->moviesTable->item(selected_row, ROK)->setText(year);
                ui->moviesTable->item(selected_row, DOSTEPNE)->setText(available);
            }
        }
    }
}

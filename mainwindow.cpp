#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <addclientdialog.h>
#include <addmoviedialog.h>
#include <editclientdialog.h>
#include <editmoviedialog.h>
#include <addborrowdialog.h>
#include <editborrowdialog.h>
#include <QDate>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QTextCodec>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    ui->setupUi(this);
    ui->actionWczytaj_bazy_z_pliku->trigger();
    ui->clientsTable->setSortingEnabled(true);
    ui->moviesTable->setSortingEnabled(true);
    ui->borrowsTable->setSortingEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Wyjście", "Czy na pewno chcesz zakończyć program?", QMessageBox::Yes | QMessageBox::No))
    {
        ui->actionZapisz_do_pliku->trigger();
        event->accept();
    }

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
    }else if(items[POSIADANE_FILMY]->text().toInt()!=0){
        msgBox.setText("Nie można usunąć klienta ponieważ ma on aktualnie wypożyczony film!");
        msgBox.exec();
        return;
    }else if(QMessageBox::Yes == QMessageBox::question(this, tr("Usuwanie klienta"), tr("Czy na pewno chcesz kontyunuować?"))){
        int rowToRemove = ui->clientsTable->row(items[0]);
        ui->clientsTable->removeRow(rowToRemove);
    }
}

void MainWindow::on_delMovieButton_clicked()
{
    QMessageBox msgBox;
    QList<QTableWidgetItem *> items = ui->moviesTable->selectedItems();
    if(items.isEmpty()){
        msgBox.setText("Żadna z kolumn nie jest wybrana!");
        msgBox.exec();
    }else if(items[DOSTEPNE]->text().toInt()==0){
        msgBox.setText("Nie można usunąć filmu ponieważ wszystkie jego egzemplarze są tymczasowo wypożyczone!");
        msgBox.exec();
        return;
    }else if(items[WYPOZYCZONE]->text().toInt() != 0){
        if(QMessageBox::Yes == QMessageBox::question(this, tr("Usuwanie filmu"), tr("Niektóre egzemplarze filmu są wypożyczone! Czy chcesz usunąć wszystkie dostępne egzemplarze?"))){
            QTableWidgetItem *item = ui->moviesTable->item(items[0]->row(), DOSTEPNE);
            item->setText(QString::number(0));
        }
        return;
    }else if(QMessageBox::Yes == QMessageBox::question(this, tr("Usuwanie filmu"), tr("Czy na pewno chcesz kontyunuować?"))){
        int rowToRemove = ui->moviesTable->row(items[0]);
        ui->moviesTable->removeRow(rowToRemove);
    }
}

void MainWindow::on_addBorrowButton_clicked()
{

    addBorrowDialog addBorrowDialog(this, ui->clientsTable, ui->moviesTable);
    int ret = addBorrowDialog.exec();
    if(ret == QDialog::Rejected)
        return;


    QString borrowDate = addBorrowDialog.borrow_date();
    QString returnDate = addBorrowDialog.return_date();
    QString name = addBorrowDialog.name();
    QString surname = addBorrowDialog.surname();
    QString title = addBorrowDialog.title();
    QString charge = addBorrowDialog.charge();


    QList<QTableWidgetItem *> repeated_items = ui->borrowsTable->findItems(title, Qt::MatchExactly);

    for(int i=0; i<repeated_items.size(); i++) {
        int match_item = 0;
        QString search_table[3] = {name, surname, title};
        int row = repeated_items[i]->row();
        for(int j=0; j<3;j++) {
            QTableWidgetItem *item = ui->borrowsTable->item(row, j);
            if(item->text() == search_table[j])
                match_item++;
        }
        if(match_item==3) {
            QMessageBox::information(this, tr("Istniejace wypożyczenie"),tr("W bazie już istnieje takie wypożyczenie!\nWybierz inny film."));
            return;
        }
    }

    QTableWidgetItem *title_item = new QTableWidgetItem(title);
    QTableWidgetItem *name_item = new QTableWidgetItem(name);
    QTableWidgetItem *surname_item = new QTableWidgetItem(surname);
    QTableWidgetItem *borrowdate_item = new QTableWidgetItem(borrowDate);
    QTableWidgetItem *returndate_item = new QTableWidgetItem(returnDate);
    QTableWidgetItem *charge_item = new QTableWidgetItem(charge);

    ui->borrowsTable->insertRow(ui->borrowsTable->rowCount());
    int currentRow = ui->borrowsTable->rowCount()-1;

    ui->borrowsTable->setItem(currentRow, IMIE, name_item);
    ui->borrowsTable->setItem(currentRow, NAZWISKO, surname_item);
    ui->borrowsTable->setItem(currentRow, TITLE, title_item);
    ui->borrowsTable->setItem(currentRow, DATA_WYPOZYCZENIA, borrowdate_item);
    ui->borrowsTable->setItem(currentRow, DATA_ZWROTU, returndate_item);
    ui->borrowsTable->setItem(currentRow, KOSZT, charge_item);

    //dodawanie info do tablic głównych//
    int chosenClientRow = addBorrowDialog.chosenClientRow();
    int ownedMoviesCount = ui->clientsTable->item(chosenClientRow,POSIADANE_FILMY)->text().toInt();
    ownedMoviesCount++;
    ui->clientsTable->item(chosenClientRow,POSIADANE_FILMY)->setText(QString::number(ownedMoviesCount));

    int chosenMovieRow = addBorrowDialog.chosenMovieRow();
    int freeMoviesCount = ui->moviesTable->item(chosenMovieRow, DOSTEPNE)->text().toInt();
    int borrowedMoviesCount = ui->moviesTable->item(chosenMovieRow, WYPOZYCZONE)->text().toInt();
    freeMoviesCount--;
    borrowedMoviesCount++;
    ui->moviesTable->item(chosenMovieRow,DOSTEPNE)->setText(QString::number(freeMoviesCount));
    ui->moviesTable->item(chosenMovieRow,WYPOZYCZONE)->setText(QString::number(borrowedMoviesCount));



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
                QTableWidgetItem *item = ui->moviesTable->item(row, DOSTEPNE);
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

void MainWindow::on_editBorrowButton_2_clicked()
{
    QMessageBox msgBox;
    QList<QTableWidgetItem *> items = ui->borrowsTable->selectedItems();
    if(items.isEmpty()) {
        msgBox.setText("Żaden wiersz nie został wybrany!");
        msgBox.exec();
        return;
    }else if (items.size() > 6) {
        msgBox.setText("Wybrano więcej niż jeden wiersz!");
        msgBox.exec();
        return;
    }

    editBorrowDialog editBorrowDialog(nullptr, items[4]->text());
    int ret = editBorrowDialog.exec();
    if(ret == QDialog::Rejected)
        return;

    QString returndate = editBorrowDialog.returndate();

    if(QDate::fromString(returndate, "dd.MM.yyyy") <= QDate::currentDate()) {
        msgBox.setText("Wypożyczenie należy przedłużyć o conajmniej jeden dzień od dzisiaj!");
        msgBox.exec();
    }
    else {
        ui->borrowsTable->item(items[0]->row(), DATA_ZWROTU)->setText(returndate);
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
        if(items[DOSTEPNE]->text().toInt()==0){
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
                    QTableWidgetItem *item = ui->moviesTable->item(row, DOSTEPNE);
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

void MainWindow::on_addDefaultData_triggered()
{
    QTableWidgetItem *title_item = new QTableWidgetItem("Hobbit");
    QTableWidgetItem *director_item = new QTableWidgetItem("Jan Brzechwa");
    QTableWidgetItem *genre_item = new QTableWidgetItem("Horror");
    QTableWidgetItem *year_item = new QTableWidgetItem("2020");
    QTableWidgetItem *available_item = new QTableWidgetItem("10");
    QTableWidgetItem *borrowed_item = new QTableWidgetItem("0");

    ui->moviesTable->insertRow(ui->moviesTable->rowCount());
    int currentRow = ui->moviesTable->rowCount()-1;


    //ui->moviesTable->setItem(currentRow, 0, new QTableWidgetItem("TempID")); //DO ZMIANY TEMP DODAWANIE ID
    ui->moviesTable->setItem(currentRow, TYTUL, title_item);
    ui->moviesTable->setItem(currentRow, REZYSER, director_item);
    ui->moviesTable->setItem(currentRow, GATUNEK, genre_item);
    ui->moviesTable->setItem(currentRow, ROK, year_item);
    ui->moviesTable->setItem(currentRow, DOSTEPNE, available_item);
    ui->moviesTable->setItem(currentRow, WYPOZYCZONE, borrowed_item);

    // NASTEPNY FILM //

    title_item = new QTableWidgetItem("Harry Potter");
    director_item = new QTableWidgetItem("J.K. Baczyński");
    genre_item = new QTableWidgetItem("Kreskówka");
    year_item = new QTableWidgetItem("1923");
    available_item = new QTableWidgetItem("4");
    borrowed_item = new QTableWidgetItem("0");

    ui->moviesTable->insertRow(ui->moviesTable->rowCount());
    currentRow = ui->moviesTable->rowCount()-1;

    //ui->moviesTable->setItem(currentRow, 0, new QTableWidgetItem("TempID")); //DO ZMIANY TEMP DODAWANIE ID
    ui->moviesTable->setItem(currentRow, TYTUL, title_item);
    ui->moviesTable->setItem(currentRow, REZYSER, director_item);
    ui->moviesTable->setItem(currentRow, GATUNEK, genre_item);
    ui->moviesTable->setItem(currentRow, ROK, year_item);
    ui->moviesTable->setItem(currentRow, DOSTEPNE, available_item);
    ui->moviesTable->setItem(currentRow, WYPOZYCZONE, borrowed_item);

    // NASTEPNY FILM //

    title_item = new QTableWidgetItem("Incepcja");
    director_item = new QTableWidgetItem("Bronisław Komorowski");
    genre_item = new QTableWidgetItem("Musical");
    year_item = new QTableWidgetItem("1999");
    available_item = new QTableWidgetItem("12");
    borrowed_item = new QTableWidgetItem("0");

    ui->moviesTable->insertRow(ui->moviesTable->rowCount());
    currentRow = ui->moviesTable->rowCount()-1;

    //ui->moviesTable->setItem(currentRow, 0, new QTableWidgetItem("TempID")); //DO ZMIANY TEMP DODAWANIE ID
    ui->moviesTable->setItem(currentRow, TYTUL, title_item);
    ui->moviesTable->setItem(currentRow, REZYSER, director_item);
    ui->moviesTable->setItem(currentRow, GATUNEK, genre_item);
    ui->moviesTable->setItem(currentRow, ROK, year_item);
    ui->moviesTable->setItem(currentRow, DOSTEPNE, available_item);
    ui->moviesTable->setItem(currentRow, WYPOZYCZONE, borrowed_item);

    // NASTEPNY FILM //

    title_item = new QTableWidgetItem("Mały Książe");
    director_item = new QTableWidgetItem("Michael Bay");
    genre_item = new QTableWidgetItem("Film Grozy");
    year_item = new QTableWidgetItem("1233");
    available_item = new QTableWidgetItem("1");
    borrowed_item = new QTableWidgetItem("0");

    ui->moviesTable->insertRow(ui->moviesTable->rowCount());
    currentRow = ui->moviesTable->rowCount()-1;

    //ui->moviesTable->setItem(currentRow, 0, new QTableWidgetItem("TempID")); //DO ZMIANY TEMP DODAWANIE ID
    ui->moviesTable->setItem(currentRow, TYTUL, title_item);
    ui->moviesTable->setItem(currentRow, REZYSER, director_item);
    ui->moviesTable->setItem(currentRow, GATUNEK, genre_item);
    ui->moviesTable->setItem(currentRow, ROK, year_item);
    ui->moviesTable->setItem(currentRow, DOSTEPNE, available_item);
    ui->moviesTable->setItem(currentRow, WYPOZYCZONE, borrowed_item);

    // NASTEPNY FILM //

    title_item = new QTableWidgetItem("Gambit Królowej");
    director_item = new QTableWidgetItem("Netflix");
    genre_item = new QTableWidgetItem("Nie wiem");
    year_item = new QTableWidgetItem("413");
    available_item = new QTableWidgetItem("44");
    borrowed_item = new QTableWidgetItem("0");

    ui->moviesTable->insertRow(ui->moviesTable->rowCount());
    currentRow = ui->moviesTable->rowCount()-1;

    //ui->moviesTable->setItem(currentRow, 0, new QTableWidgetItem("TempID")); //DO ZMIANY TEMP DODAWANIE ID
    ui->moviesTable->setItem(currentRow, TYTUL, title_item);
    ui->moviesTable->setItem(currentRow, REZYSER, director_item);
    ui->moviesTable->setItem(currentRow, GATUNEK, genre_item);
    ui->moviesTable->setItem(currentRow, ROK, year_item);
    ui->moviesTable->setItem(currentRow, DOSTEPNE, available_item);
    ui->moviesTable->setItem(currentRow, WYPOZYCZONE, borrowed_item);

    // NASTEPNY KLIENT //

    ui->clientsTable->insertRow(ui->clientsTable->rowCount());
    currentRow = ui->clientsTable->rowCount()-1;

    QTableWidgetItem *name_item = new QTableWidgetItem("Maciej");
    QTableWidgetItem *surname_item = new QTableWidgetItem("Umański");
    QTableWidgetItem *email_item = new QTableWidgetItem("maciek@buziaczek.pl");
    QTableWidgetItem *pesel_item = new QTableWidgetItem("12345678909");
    QTableWidgetItem *phone_item = new QTableWidgetItem("123123123");
    QTableWidgetItem *count_item = new QTableWidgetItem("0");

    //ui->clientsTable->setItem(currentRow, 0, new QTableWidgetItem("TempID")); //DO ZMIANY TEMP DODAWANIE ID
    ui->clientsTable->setItem(currentRow, IMIE, name_item);
    ui->clientsTable->setItem(currentRow, NAZWISKO, surname_item);
    ui->clientsTable->setItem(currentRow, EMAIL, email_item);
    ui->clientsTable->setItem(currentRow, PESEL, pesel_item);
    ui->clientsTable->setItem(currentRow, TELEFON, phone_item);
    ui->clientsTable->setItem(currentRow, POSIADANE_FILMY, count_item);

    // NASTEPNY KLIENT //

    ui->clientsTable->insertRow(ui->clientsTable->rowCount());
    currentRow = ui->clientsTable->rowCount()-1;

    name_item = new QTableWidgetItem("Jakub");
    surname_item = new QTableWidgetItem("Witaś");
    email_item = new QTableWidgetItem("lubieamine@op.pl");
    pesel_item = new QTableWidgetItem("31231232112");
    phone_item = new QTableWidgetItem("321321312");
    count_item = new QTableWidgetItem("0");

    //ui->clientsTable->setItem(currentRow, 0, new QTableWidgetItem("TempID")); //DO ZMIANY TEMP DODAWANIE ID
    ui->clientsTable->setItem(currentRow, IMIE, name_item);
    ui->clientsTable->setItem(currentRow, NAZWISKO, surname_item);
    ui->clientsTable->setItem(currentRow, EMAIL, email_item);
    ui->clientsTable->setItem(currentRow, PESEL, pesel_item);
    ui->clientsTable->setItem(currentRow, TELEFON, phone_item);
    ui->clientsTable->setItem(currentRow, POSIADANE_FILMY, count_item);

    // NASTEPNY KLIENT //

    ui->clientsTable->insertRow(ui->clientsTable->rowCount());
    currentRow = ui->clientsTable->rowCount()-1;

    name_item = new QTableWidgetItem("Krystian");
    surname_item = new QTableWidgetItem("Kołomański");
    email_item = new QTableWidgetItem("hehehaha@op.pl");
    pesel_item = new QTableWidgetItem("11111111111");
    phone_item = new QTableWidgetItem("321333312");
    count_item = new QTableWidgetItem("0");

    //ui->clientsTable->setItem(currentRow, 0, new QTableWidgetItem("TempID")); //DO ZMIANY TEMP DODAWANIE ID
    ui->clientsTable->setItem(currentRow, IMIE, name_item);
    ui->clientsTable->setItem(currentRow, NAZWISKO, surname_item);
    ui->clientsTable->setItem(currentRow, EMAIL, email_item);
    ui->clientsTable->setItem(currentRow, PESEL, pesel_item);
    ui->clientsTable->setItem(currentRow, TELEFON, phone_item);
    ui->clientsTable->setItem(currentRow, POSIADANE_FILMY, count_item);

    // NASTEPNY KLIENT //

    ui->clientsTable->insertRow(ui->clientsTable->rowCount());
    currentRow = ui->clientsTable->rowCount()-1;

    name_item = new QTableWidgetItem("Marcin");
    surname_item = new QTableWidgetItem("Najman");
    email_item = new QTableWidgetItem("xDDDDD@XD.pl");
    pesel_item = new QTableWidgetItem("55544411323");
    phone_item = new QTableWidgetItem("997");
    count_item = new QTableWidgetItem("0");

    //ui->clientsTable->setItem(currentRow, 0, new QTableWidgetItem("TempID")); //DO ZMIANY TEMP DODAWANIE ID
    ui->clientsTable->setItem(currentRow, IMIE, name_item);
    ui->clientsTable->setItem(currentRow, NAZWISKO, surname_item);
    ui->clientsTable->setItem(currentRow, EMAIL, email_item);
    ui->clientsTable->setItem(currentRow, PESEL, pesel_item);
    ui->clientsTable->setItem(currentRow, TELEFON, phone_item);
    ui->clientsTable->setItem(currentRow, POSIADANE_FILMY, count_item);

    // NASTEPNY KLIENT //

    ui->clientsTable->insertRow(ui->clientsTable->rowCount());
    currentRow = ui->clientsTable->rowCount()-1;

    name_item = new QTableWidgetItem("Stefan");
    surname_item = new QTableWidgetItem("Walaszek");
    email_item = new QTableWidgetItem("patologia@XD.pl");
    pesel_item = new QTableWidgetItem("32332145612");
    phone_item = new QTableWidgetItem("112");
    count_item = new QTableWidgetItem("0");

    //ui->clientsTable->setItem(currentRow, 0, new QTableWidgetItem("TempID")); //DO ZMIANY TEMP DODAWANIE ID
    ui->clientsTable->setItem(currentRow, IMIE, name_item);
    ui->clientsTable->setItem(currentRow, NAZWISKO, surname_item);
    ui->clientsTable->setItem(currentRow, EMAIL, email_item);
    ui->clientsTable->setItem(currentRow, PESEL, pesel_item);
    ui->clientsTable->setItem(currentRow, TELEFON, phone_item);
    ui->clientsTable->setItem(currentRow, POSIADANE_FILMY, count_item);

    ui->addDefaultData->setDisabled(true);
}



void MainWindow::on_searchClientButton_clicked()
{
    if(ui->searchClientField->text().isEmpty()){
        for(int i = 0; i < ui->clientsTable->rowCount(); i++){
            ui->clientsTable->showRow(i);
        }
    }else{
        QString searchedPhrase = ui->searchClientField->text();
        QList<QTableWidgetItem *> foundItems = ui->clientsTable->findItems(searchedPhrase, Qt::MatchContains);

        for(int i = 0; i < ui->clientsTable->rowCount(); i++){
            ui->clientsTable->hideRow(i);
        }

        for(int i = 0; i < foundItems.size(); i++){
            ui->clientsTable->showRow(foundItems[i]->row());
        }
    }
}

void MainWindow::on_searchBorrowsButton_clicked()
{
    if(ui->searchBorrowField->text().isEmpty()){
        for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
            ui->borrowsTable->showRow(i);
        }
    }else{
        QString searchedPhrase = ui->searchBorrowField->text();
        QList<QTableWidgetItem *> foundItems = ui->borrowsTable->findItems(searchedPhrase, Qt::MatchContains);

        for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
            ui->borrowsTable->hideRow(i);
        }

        for(int i = 0; i < foundItems.size(); i++){
            ui->borrowsTable->showRow(foundItems[i]->row());
        }
    }
}

void MainWindow::on_searchMovieButton_clicked()
{
    if(ui->searchMovieField->text().isEmpty()){
        for(int i = 0; i < ui->moviesTable->rowCount(); i++){
            ui->moviesTable->showRow(i);
        }
    }else{
        QString searchedPhrase = ui->searchMovieField->text();
        QList<QTableWidgetItem *> foundItems = ui->moviesTable->findItems(searchedPhrase, Qt::MatchContains);

        for(int i = 0; i < ui->moviesTable->rowCount(); i++){
            ui->moviesTable->hideRow(i);
        }

        for(int i = 0; i < foundItems.size(); i++){
            ui->moviesTable->showRow(foundItems[i]->row());
        }
    }
}

void MainWindow::on_searchBorrowField_returnPressed()
{
    MainWindow::on_searchBorrowsButton_clicked();
}

void MainWindow::on_searchClientField_returnPressed()
{
    MainWindow::on_searchClientButton_clicked();
}

void MainWindow::on_searchMovieField_returnPressed()
{
    MainWindow::on_searchMovieButton_clicked();
}

void MainWindow::on_delBorrowButton_clicked()
{
    QMessageBox msgBox;
    QList<QTableWidgetItem *> items = ui->borrowsTable->selectedItems();
    if(items.isEmpty()){
        msgBox.setText("Żadna z kolumn nie jest wybrana!");
        msgBox.exec();
    }else{
        int rowToRemove = ui->borrowsTable->row(items[0]);
        QDate borrowdate, returndate;
        borrowdate = QDate::fromString(ui->borrowsTable->item(rowToRemove, DATA_WYPOZYCZENIA)->text(), "dd.MM.yyyy");
        returndate = QDate::fromString(ui->borrowsTable->item(rowToRemove, DATA_ZWROTU)->text(), "dd.MM.yyyy");
        int datediff = borrowdate.daysTo(returndate);
        int datetonow = returndate.daysTo(QDate::currentDate());
        int cena = (ui->borrowsTable->item(rowToRemove, 5)->text()).split(" ")[0].toInt();
        int naleznosc = datediff * cena + datetonow*cena;

        if(datetonow > 0) {
            //DORZUCIĆ KARE
            msgBox.setText("Wypożyczenie oddane po terminie!\nKara zostanie doliczona do rachunku.\nNależność do zapłaty: "+QString::number(naleznosc)+"zł.");
            msgBox.exec();
            ui->borrowsTable->removeRow(rowToRemove);
        }
        else {
           msgBox.setText("Należność do zapłaty: "+QString::number(naleznosc)+"zł.");
           msgBox.exec();
           ui->borrowsTable->removeRow(rowToRemove);
        }
   }
}



void MainWindow::on_actionZapisz_do_pliku_triggered()
{
    QString path("databases/");
    QDir dir;
    if(!dir.exists(path))
        dir.mkpath(path);

    QFile f_clients(path + "clientsTable.csv");
    QFile f_movies(path + "moviesTable.csv");
    QFile f_borrows(path + "borrowsTable.csv");

    if(QMessageBox::No == QMessageBox::question(this, tr("Zapis baz danych"), tr("Czy chcesz zapisać bazy danych?"))){
        return;
    }

    if (f_clients.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream data(&f_clients);
        QStringList strList;

        for(int i = 0; i < ui->clientsTable->rowCount(); i++){
            strList.clear();
            for(int j = 0; j < ui->clientsTable->columnCount(); j++){
                strList << ui->clientsTable->item(i,j)->text();
            }
            data << strList.join(";")+"\n";
        }
        f_clients.close();
    }


    if (f_movies.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream data(&f_movies);
        QStringList strList;

        for(int i = 0; i < ui->moviesTable->rowCount(); i++){
            strList.clear();
            for(int j = 0; j < ui->moviesTable->columnCount(); j++){
                strList << ui->moviesTable->item(i,j)->text();
            }
            data << strList.join(";")+"\n";
        }
        f_movies.close();
    }

    if (f_borrows.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream data(&f_borrows);
        QStringList strList;

        for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
            strList.clear();
            for(int j = 0; j < ui->borrowsTable->columnCount(); j++){
                strList << ui->borrowsTable->item(i,j)->text();
            }
            data << strList.join(";")+"\n";
        }
        f_borrows.close();
    }
}

void MainWindow::on_actionWczytaj_bazy_z_pliku_triggered()
{
    QString path("databases/");
    QDir dir;
    if(!dir.exists(path))
        dir.mkpath(path);

    QFile f_clients(path + "clientsTable.csv");
    QFile f_movies(path + "moviesTable.csv");
    QFile f_borrows(path + "borrowsTable.csv");

    if(QMessageBox::No == QMessageBox::question(this, tr("Odczyt baz danych"), tr("Czy chcesz wczytać bazy danych?"))){
        return;
    }

    if(!(f_clients.exists() || f_movies.exists() || f_borrows.exists())){
        QMessageBox msgBox;
        msgBox.setText("Pliki baz danych nie istnieją lub są niekompletne!");
        msgBox.exec();
        return;
    }

    ui->clientsTable->clearContents();
    ui->clientsTable->setRowCount(0);
    ui->moviesTable->clearContents();
    ui->moviesTable->setRowCount(0);
    ui->borrowsTable->clearContents();
    ui->borrowsTable->setRowCount(0);

    QString data;
    QStringList rowOfData;
    QStringList rowData;
    data.clear();
    rowOfData.clear();
    rowData.clear();

    if (f_clients.open(QFile::ReadOnly)){
        data = f_clients.readAll();
        rowOfData = data.split("\n");
        f_clients.close();
    }

    for (int x = 0; x < rowOfData.size(); x++)
    {
        rowData = rowOfData.at(x).split(";");
        ui->clientsTable->insertRow(ui->clientsTable->rowCount());
        int currentRow = ui->clientsTable->rowCount()-1;
        for (int y = 0; y < rowData.size(); y++)
        {
            ui->clientsTable->setItem(currentRow,y,new QTableWidgetItem(rowData[y]));
        }
    }
    ui->clientsTable->removeRow(ui->clientsTable->rowCount()-1);

    data.clear();
    rowOfData.clear();
    rowData.clear();

    if (f_movies.open(QFile::ReadOnly)){
        data = f_movies.readAll();
        rowOfData = data.split("\n");
        f_movies.close();
    }

    for (int x = 0; x < rowOfData.size(); x++)
    {
        rowData = rowOfData.at(x).split(";");
        ui->moviesTable->insertRow(ui->moviesTable->rowCount());
        int currentRow = ui->moviesTable->rowCount()-1;
        for (int y = 0; y < rowData.size(); y++)
        {
            ui->moviesTable->setItem(currentRow,y,new QTableWidgetItem(rowData[y]));
        }
    }
    ui->moviesTable->removeRow(ui->moviesTable->rowCount()-1);

    data.clear();
    rowOfData.clear();
    rowData.clear();

    if (f_borrows.open(QFile::ReadOnly)){
        data = f_borrows.readAll();
        rowOfData = data.split("\n");
        f_borrows.close();
    }

    for (int x = 0; x < rowOfData.size(); x++)
    {
        rowData = rowOfData.at(x).split(";");
        ui->borrowsTable->insertRow(ui->borrowsTable->rowCount());
        int currentRow = ui->borrowsTable->rowCount()-1;
        for (int y = 0; y < rowData.size(); y++)
        {
            ui->borrowsTable->setItem(currentRow,y,new QTableWidgetItem(rowData[y]));
        }
    }
    ui->borrowsTable->removeRow(ui->borrowsTable->rowCount()-1);
}

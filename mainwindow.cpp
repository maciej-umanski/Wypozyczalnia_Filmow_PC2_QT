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
#include <setpenaltydialog.h>

float penalty;
unsigned long long clients_lastID;
unsigned long long movies_lastID;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    this->penalty = 2.0f;
    this->clients_lastID = 0;
    this->movies_lastID = 0;

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    ui->setupUi(this);
    ui->actionWczytaj_bazy_z_pliku->trigger();
    ui->actionShow_IDs->toggle();
    ui->actionPokazuj_Status_Zwr_cenia->toggle();
    ui->borrowsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->clientsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->moviesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->actionPod_wietlaj_zaleg_e->toggle();
    ui->actionPod_wietlaj_zwr_cone->toggle();

    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);


    //POWIADOMIENIE O ZALEGŁYCH//
    QString currentDateStr = QDate::currentDate().toString("dd.MM.yyyy");
    int count = 0;
    for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
        int cmp = ui->borrowsTable->item(i,DATA_ZWROTU)->text().compare(currentDateStr);
        if(cmp < 0){
            count ++;
        }
    }
    if(count > 0){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Zaległe wypożyczenia");
        msgBox.setText(QString("Istnieje %1 zaległych wypożyczeń! Skontaktuj się z klientami").arg(count));
        msgBox.exec();
    }

    for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
        if(ui->borrowsTable->item(i,ZWROCONE)->text() == "Tak"){
            ui->borrowsTable->hideRow(i);
        }
    }
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
        msgBox.setWindowTitle("Błąd");
        msgBox.setText("Klient o danym peselu już istnieje w bazie!");
        msgBox.exec();
        return;
    }

    this->clients_lastID++;

    ui->clientsTable->insertRow(ui->clientsTable->rowCount());
    int currentRow = ui->clientsTable->rowCount()-1;

    QTableWidgetItem *name_item = new QTableWidgetItem(name);
    QTableWidgetItem *surname_item = new QTableWidgetItem(surname);
    QTableWidgetItem *email_item = new QTableWidgetItem(email);
    QTableWidgetItem *pesel_item = new QTableWidgetItem(pesel);
    QTableWidgetItem *phone_item = new QTableWidgetItem(phone);
    QTableWidgetItem *count_item = new QTableWidgetItem("0");
    QTableWidgetItem *ID_item = new QTableWidgetItem(QString::number(clients_lastID));

    ui->clientsTable->setItem(currentRow, IMIE, name_item);
    ui->clientsTable->setItem(currentRow, NAZWISKO, surname_item);
    ui->clientsTable->setItem(currentRow, EMAIL, email_item);
    ui->clientsTable->setItem(currentRow, PESEL, pesel_item);
    ui->clientsTable->setItem(currentRow, TELEFON, phone_item);
    ui->clientsTable->setItem(currentRow, POSIADANE_FILMY, count_item);
    ui->clientsTable->setItem(currentRow, ID_KLIENTA, ID_item);

}

void MainWindow::on_delClientButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Błąd");
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
    msgBox.setWindowTitle("Błąd");
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

    addBorrowDialog addBorrowDialog(this, ui->clientsTable, ui->moviesTable, ui->actionShow_IDs->isChecked());
    int ret = addBorrowDialog.exec();
    if(ret == QDialog::Rejected)
        return;


    QString borrowDate = addBorrowDialog.borrow_date();
    QString returnDate = addBorrowDialog.return_date();
    QString name = addBorrowDialog.name();
    QString surname = addBorrowDialog.surname();
    QString title = addBorrowDialog.title();
    QString charge = addBorrowDialog.charge();
    QString movieID = addBorrowDialog.chosenMovieID();
    QString clientID = addBorrowDialog.chosenClientID();

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
        if(match_item==3 && ui->borrowsTable->item(row,ZWROCONE)->text() == "Nie") {
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
    QTableWidgetItem *movieID_item = new QTableWidgetItem(movieID);
    QTableWidgetItem *clientID_item = new QTableWidgetItem(clientID);
    QTableWidgetItem *isReturned_item = new QTableWidgetItem("Nie");

    ui->borrowsTable->insertRow(ui->borrowsTable->rowCount());
    int currentRow = ui->borrowsTable->rowCount()-1;

    ui->borrowsTable->setItem(currentRow, IMIE_WYP, name_item);
    ui->borrowsTable->setItem(currentRow, NAZWISKO_WYP, surname_item);
    ui->borrowsTable->setItem(currentRow, TITLE, title_item);
    ui->borrowsTable->setItem(currentRow, DATA_WYPOZYCZENIA, borrowdate_item);
    ui->borrowsTable->setItem(currentRow, DATA_ZWROTU, returndate_item);
    ui->borrowsTable->setItem(currentRow, KOSZT, charge_item);
    ui->borrowsTable->setItem(currentRow, ID_FILMU_WYP, movieID_item);
    ui->borrowsTable->setItem(currentRow, ID_KLIENTA_WYP, clientID_item);
    ui->borrowsTable->setItem(currentRow, ZWROCONE, isReturned_item);

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

    for(int i = 0 ; i < 2; i++){
        ui->actionPod_wietlaj_zaleg_e->toggle();
        ui->actionPod_wietlaj_zwr_cone->toggle();
        ui->actionPod_wietlaj_aktualne_niezaleg_e->toggle();
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
                QTableWidgetItem *item = ui->moviesTable->item(row, DOSTEPNE);
                int data = available.toInt();
                data = data + item->text().toInt();
                item->setText(QString::number(data));
            }
            return;
        }

    }

    this->movies_lastID++;

    QTableWidgetItem *title_item = new QTableWidgetItem(title);
    QTableWidgetItem *director_item = new QTableWidgetItem(director);
    QTableWidgetItem *genre_item = new QTableWidgetItem(genre);
    QTableWidgetItem *year_item = new QTableWidgetItem(year);
    QTableWidgetItem *available_item = new QTableWidgetItem(available);
    QTableWidgetItem *borrowed_item = new QTableWidgetItem("0");
    QTableWidgetItem *ID_item = new QTableWidgetItem(QString::number(movies_lastID));

    ui->moviesTable->insertRow(ui->moviesTable->rowCount());
    int currentRow = ui->moviesTable->rowCount()-1;

    ui->moviesTable->setItem(currentRow, TYTUL, title_item);
    ui->moviesTable->setItem(currentRow, REZYSER, director_item);
    ui->moviesTable->setItem(currentRow, GATUNEK, genre_item);
    ui->moviesTable->setItem(currentRow, ROK, year_item);
    ui->moviesTable->setItem(currentRow, DOSTEPNE, available_item);
    ui->moviesTable->setItem(currentRow, WYPOZYCZONE, borrowed_item);
    ui->moviesTable->setItem(currentRow, ID_FILMU, ID_item);
}

void MainWindow::on_editClientButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Błąd");
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
            msgBox.setWindowTitle("Błąd");
            msgBox.setText("Inny Klient o danym peselu już istnieje w bazie!");
            msgBox.exec();
            return;
        }
    }
}

void MainWindow::on_editBorrowButton_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Błąd");
    QList<QTableWidgetItem *> items = ui->borrowsTable->selectedItems();
    if(items.isEmpty()) {
        msgBox.setText("Żaden wiersz nie został wybrany!");
        msgBox.exec();
        return;
    }else if(ui->borrowsTable->item(items[0]->row(),ZWROCONE)->text() == "Tak"){
        msgBox.setText("Nie można edytować zwróconego wypożyczenia!");
        msgBox.exec();
    }else{
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

        for(int i = 0 ; i < 2; i++){
            ui->actionPod_wietlaj_zaleg_e->toggle();
            ui->actionPod_wietlaj_zwr_cone->toggle();
            ui->actionPod_wietlaj_aktualne_niezaleg_e->toggle();
        }
    }
}

void MainWindow::on_editMovieButton_clicked()
{
    QList<QTableWidgetItem *> items = ui->moviesTable->selectedItems();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Błąd");
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
    int currentRow = items[0]->row();
    if(items.isEmpty()){
        msgBox.setWindowTitle("Błąd");
        msgBox.setText("Żadna z kolumn nie jest wybrana!");
        msgBox.exec();
    }else if(ui->borrowsTable->item(currentRow, ZWROCONE)->text() == "Tak"){
         msgBox.setWindowTitle("Błąd");
         msgBox.setText("Film już jest zwrócony!");
         msgBox.exec();
    }else{
        int rowToRemove = ui->borrowsTable->row(items[0]);
        QDate borrowdate, returndate;
        borrowdate = QDate::fromString(ui->borrowsTable->item(rowToRemove, DATA_WYPOZYCZENIA)->text(), "dd.MM.yyyy");
        returndate = QDate::fromString(ui->borrowsTable->item(rowToRemove, DATA_ZWROTU)->text(), "dd.MM.yyyy");
        unsigned long long clientID_toUpdate = ui->borrowsTable->item(rowToRemove, ID_KLIENTA_WYP)->text().toULongLong();
        unsigned long long movieID_toUpdate = ui->borrowsTable->item(rowToRemove, ID_FILMU_WYP)->text().toULongLong();

        int datediff = borrowdate.daysTo(returndate);
        int datetonow = returndate.daysTo(QDate::currentDate());
        int cena = (ui->borrowsTable->item(rowToRemove, 5)->text()).split(" ")[0].toInt();
        int naleznosc_podstawowa = datediff * cena;
        float naleznosc_kara = datetonow * this->penalty;

        if(datetonow > 0) {
            msgBox.setWindowTitle("Zwrot wypożyczenia");
            msgBox.setText("Wypożyczenie oddane po terminie!\nKara zostanie doliczona do rachunku.\nNależność podstawowa: "+QString::number(naleznosc_podstawowa)+"zł.\nKara: " + QString::number(naleznosc_kara)+"zł.\nRazem do zapłaty: " + QString::number(naleznosc_kara+naleznosc_podstawowa)+"zł.");
            msgBox.exec();
        }
        else {
           msgBox.setText("Należność do zapłaty: "+QString::number(naleznosc_podstawowa)+"zł.");
           msgBox.exec();
        }

        ui->borrowsTable->item(rowToRemove,ZWROCONE)->setText("Tak");
        ui->borrowsTable->item(rowToRemove,DATA_ZWROTU)->setText(QDate::currentDate().toString("dd.MM.yyyy"));

        if(ui->comboBox->currentIndex() == 0 || ui->comboBox->currentIndex() == 1){
           ui->borrowsTable->hideRow(rowToRemove);
        }

        for(int i = 0 ; i < 2; i++){
            ui->actionPod_wietlaj_zaleg_e->toggle();
            ui->actionPod_wietlaj_zwr_cone->toggle();
            ui->actionPod_wietlaj_aktualne_niezaleg_e->toggle();
        }


        for(int i = 0; i < ui->clientsTable->rowCount(); i++){
            if(clientID_toUpdate == ui->clientsTable->item(i, ID_KLIENTA)->text().toULongLong()){
                int tempMovieCount = ui->clientsTable->item(i, POSIADANE_FILMY)->text().toInt();
                tempMovieCount--;
                ui->clientsTable->item(i, POSIADANE_FILMY)->setText(QString::number(tempMovieCount));
                break;
            }
        }

        for(int i = 0; i < ui->moviesTable->rowCount(); i++){
            if(movieID_toUpdate == ui->moviesTable->item(i, ID_FILMU)->text().toULongLong()){
                int tempFreeMovieCount = ui->moviesTable->item(i, DOSTEPNE)->text().toInt();
                int tempBorrowedMovieCount = ui->moviesTable->item(i, WYPOZYCZONE)->text().toInt();
                tempFreeMovieCount++;
                tempBorrowedMovieCount--;
                ui->moviesTable->item(i,DOSTEPNE)->setText(QString::number(tempFreeMovieCount));
                ui->moviesTable->item(i,WYPOZYCZONE)->setText(QString::number(tempBorrowedMovieCount));
                break;
            }
        }
   }
}



void MainWindow::on_actionZapisz_do_pliku_triggered()
{
    QString path("databases/");
    QDir dir;
    if(!dir.exists(path))
        dir.mkpath(path);

    QFile f_clients(path + "clientsTable.db");
    QFile f_movies(path + "moviesTable.db");
    QFile f_borrows(path + "borrowsTable.db");
    QFile f_penalty(path + "penalty.db");
    QFile f_clients_lastID(path + "clients_lastID.db");
    QFile f_movies_lastID(path + "movies_lastID.db");

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

    if (f_penalty.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream data(&f_penalty);
        QStringList strList;
        strList << QString::number(this->penalty);
        data << strList.join("");
        f_penalty.close();
    }

    if (f_clients_lastID.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream data(&f_clients_lastID);
        QStringList strList;
        strList << QString::number(this->clients_lastID);
        data << strList.join("");
        f_clients_lastID.close();
    }

    if (f_movies_lastID.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream data(&f_movies_lastID);
        QStringList strList;
        strList << QString::number(this->movies_lastID);
        data << strList.join("");
        f_movies_lastID.close();
    }
}

void MainWindow::on_actionWczytaj_bazy_z_pliku_triggered()
{
    QString path("databases/");
    QDir dir;
    if(!dir.exists(path))
        dir.mkpath(path);

    QFile f_clients(path + "clientsTable.db");
    QFile f_movies(path + "moviesTable.db");
    QFile f_borrows(path + "borrowsTable.db");
    QFile f_penalty(path + "penalty.db");
    QFile f_clients_lastID(path + "clients_lastID.db");
    QFile f_movies_lastID(path + "movies_lastID.db");

    if(QMessageBox::No == QMessageBox::question(this, tr("Odczyt baz danych"), tr("Czy chcesz wczytać bazy danych?"))){
        return;
    }

    if(!(f_clients.exists() || f_movies.exists() || f_borrows.exists() || f_clients_lastID.exists() || f_movies_lastID.exists())){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Błąd");
        msgBox.setText("Pliki baz danych nie istnieją lub są niekompletne!");
        msgBox.exec();
        return;
    }

    if (f_penalty.open(QFile::ReadOnly)){
        QString data = f_penalty.readAll();
        if (f_penalty.size() != 0){
            bool succes = false;
            float penalty_f = data.toFloat(&succes);
            if(succes){
                this->penalty = penalty_f;
            }
        }
    }

    if (f_clients_lastID.open(QFile::ReadOnly)){
        QString data = f_clients_lastID.readAll();
        if (f_clients_lastID.size() != 0){
            bool succes = false;
            unsigned long long clients_lastID_f = data.toULongLong(&succes);
            if(succes){
                this->clients_lastID = clients_lastID_f;
            }
        }
    }

    if (f_movies_lastID.open(QFile::ReadOnly)){
        QString data = f_movies_lastID.readAll();
        if (f_movies_lastID.size() != 0){
            bool succes = false;
            unsigned long long movies_lastID_f = data.toULongLong(&succes);
            if(succes){
                this->movies_lastID = movies_lastID_f;
            }
        }
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

void MainWindow::on_actionPod_wietlaj_zaleg_e_toggled(bool arg1)
{
    QDate currentDate = QDate::currentDate();
    QString currentDateStr = currentDate.toString("dd.MM.yyyy");
    for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
        int cmp = ui->borrowsTable->item(i,DATA_ZWROTU)->text().compare(currentDateStr);
        if(cmp < 0 && ui->borrowsTable->item(i,ZWROCONE)->text() == "Nie"){
           for(int j = 0; j < ui->borrowsTable->columnCount(); j++){\
               if(arg1){
                  ui->borrowsTable->item(i,j)->setBackground(QColor(255,100,100,255));
               }else{
                  ui->borrowsTable->item(i,j)->setBackground(Qt::white);
               }
           }
        }
     }
}

void MainWindow::on_actionUstal_wysoko_kary_triggered()
{
    setPenaltyDialog setPenaltyDialog(nullptr, this->penalty);
    int ret = setPenaltyDialog.exec();
    if(ret == QDialog::Rejected)
        return;
    this->penalty = setPenaltyDialog.penalty();
}

void MainWindow::on_actionShow_Last_IDs_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Ostatnie ID");
    QString string = "Ostatnie ID filmu = " + QString::number(this->movies_lastID) + "\nOstatnie ID klienta = " + QString::number(this->clients_lastID);
    msgBox.setText(string);
    msgBox.exec();
}

void MainWindow::on_actionShow_penalty_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Wysokość kary");
    QString string = "Wysokość kary = " + QString::number(this->penalty) + "zł";
    msgBox.setText(string);
    msgBox.exec();
}

void MainWindow::on_actionShow_IDs_toggled(bool arg1)
{
    ui->borrowsTable->setColumnHidden(ID_FILMU_WYP,!arg1);
    ui->borrowsTable->setColumnHidden(ID_KLIENTA_WYP,!arg1);
    ui->clientsTable->setColumnHidden(ID_KLIENTA,!arg1);
    ui->moviesTable->setColumnHidden(ID_FILMU,!arg1);
}


void MainWindow::on_actionWyjd_triggered()
{
    close();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
        ui->borrowsTable->showRow(i);
    }
    switch(index){
    case 0:{
        for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
            if(ui->borrowsTable->item(i,ZWROCONE)->text()=="Tak"){
                ui->borrowsTable->hideRow(i);
            }
        }
        break;
    }
    case 1:{
        QDate currentDate = QDate::currentDate();
        QString currentDateStr = currentDate.toString("dd.MM.yyyy");
        for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
            int cmp = ui->borrowsTable->item(i,DATA_ZWROTU)->text().compare(currentDateStr);
            if(cmp > 0 || ui->borrowsTable->item(i,ZWROCONE)->text() == "Tak"){
                ui->borrowsTable->hideRow(i);
            }
         }
        break;
    }
    case 2:{
        for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
            ui->borrowsTable->showRow(i);
        }
        break;
    }
    case 3:{
        for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
            if(ui->borrowsTable->item(i,ZWROCONE)->text()=="Nie"){
                ui->borrowsTable->hideRow(i);
            }
        }
    }
    }
}

void MainWindow::on_actionPokazuj_Status_Zwr_cenia_toggled(bool arg1)
{
        ui->borrowsTable->setColumnHidden(ZWROCONE, !arg1);
}

void MainWindow::on_actionPod_wietlaj_zwr_cone_toggled(bool arg1)
{
    for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
        if(ui->borrowsTable->item(i,ZWROCONE)->text() == "Tak"){
            for(int j = 0; j < ui->borrowsTable->columnCount(); j++){
                if(arg1){
                 ui->borrowsTable->item(i,j)->setBackground(Qt::lightGray);
                }else{
                   ui->borrowsTable->item(i,j)->setBackground(Qt::white);
                }

            }
        }
     }
}

void MainWindow::on_actionPod_wietlaj_aktualne_niezaleg_e_toggled(bool arg1)
{
    QDate currentDate = QDate::currentDate();
    QString currentDateStr = currentDate.toString("dd.MM.yyyy");
    for(int i = 0; i < ui->borrowsTable->rowCount(); i++){
        int cmp = ui->borrowsTable->item(i,DATA_ZWROTU)->text().compare(currentDateStr);
        if(cmp >= 0 && ui->borrowsTable->item(i,ZWROCONE)->text() == "Nie"){
           for(int j = 0; j < ui->borrowsTable->columnCount(); j++){\
               if(arg1){
                  ui->borrowsTable->item(i,j)->setBackground(QColor(153,217,234,255));
               }else{
                  ui->borrowsTable->item(i,j)->setBackground(Qt::white);
               }
           }
        }
     }
}

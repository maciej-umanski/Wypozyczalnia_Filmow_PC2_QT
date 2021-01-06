#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void closeEvent(QCloseEvent *event);

    void on_addClientButton_clicked();

    void on_delClientButton_clicked();

    void on_delMovieButton_clicked();

    void on_addMovieButton_clicked();

    void on_editClientButton_clicked();

    void on_editMovieButton_clicked();

    void on_addBorrowButton_clicked();

    void on_searchClientButton_clicked();

    void on_searchBorrowsButton_clicked();

    void on_searchMovieButton_clicked();

    void on_searchBorrowField_returnPressed();

    void on_searchClientField_returnPressed();

    void on_searchMovieField_returnPressed();

    void on_delBorrowButton_clicked();

    void on_editBorrowButton_2_clicked();

    void on_actionZapisz_do_pliku_triggered();

    void on_actionWczytaj_bazy_z_pliku_triggered();

    void on_showOverdueBorrowButton_clicked();

    void on_actionPod_wietlaj_zaleg_e_toggled(bool arg1);

    void on_actionUstal_wysoko_kary_triggered();

    void on_actionShow_Last_IDs_triggered();

    void on_actionShow_penalty_triggered();

    void on_actionShow_IDs_toggled(bool arg1);

    void on_actionWyjd_triggered();

private:

    float penalty;
    int clients_lastID, movies_lastID;

    Ui::MainWindow *ui;

    enum CLIENT_COLLUMNS{
        IMIE, NAZWISKO, PESEL, TELEFON, EMAIL, POSIADANE_FILMY, ID_KLIENTA
    };

    enum MOVIE_COLLUMNS{
        TYTUL, REZYSER, GATUNEK, ROK, DOSTEPNE, WYPOZYCZONE, ID_FILMU
    };

    enum BORROW_COLLUMNS{
        IMIE_WYP, NAZWISKO_WYP, TITLE, DATA_WYPOZYCZENIA, DATA_ZWROTU, KOSZT, ID_FILMU_WYP, ID_KLIENTA_WYP
    };

};
#endif // MAINWINDOW_H

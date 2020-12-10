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

    void on_addClientButton_clicked();

    void on_delClientButton_clicked();

    void on_delMovieButton_clicked();

    void on_addMovieButton_clicked();

    void on_editClientButton_clicked();

    void on_editMovieButton_clicked();

    void on_sortClientButton_clicked();

    void on_sortMovieButton_clicked();

    void on_sortBorrowButton_clicked();

    void on_addDefaultData_triggered();

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

private:
    Ui::MainWindow *ui;

    enum CLIENT_COLLUMNS{
        IMIE, NAZWISKO, PESEL, TELEFON, EMAIL, POSIADANE_FILMY
    };

    enum MOVIE_COLLUMNS{
        TYTUL, REZYSER, GATUNEK, ROK, DOSTEPNE, WYPOZYCZONE
    };

    enum BORROW_COLLUMNS{
        BORROW_COLLUMNS=(IMIE, NAZWISKO), TITLE=2, DATA_WYPOZYCZENIA, DATA_ZWROTU, KOSZT
    };

};
#endif // MAINWINDOW_H

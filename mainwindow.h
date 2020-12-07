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

    void on_actionShowID_toggled(bool arg1);

private:
    Ui::MainWindow *ui;

    enum CLIENT_COLLUMNS{
        IMIE = 1, NAZWISKO, PESEL, TELEFON, EMAIL, POSIADANE_FILMY
    };

    enum MOVIE_COLLUMNS{
        TYTUL = 1, REZYSER, GATUNEK, ROK, DOSTEPNE, WYPOZYCZONE
    };

    enum BORROW_COLLUMNS{
        ID_KLIENT = 1, ID_FILM, IMIEB, NAZWISKOB, TITLE, DATA_WYPOZYCZENIA, DATA_ZWROTU, ZALEGLOSC
    };

};
#endif // MAINWINDOW_H

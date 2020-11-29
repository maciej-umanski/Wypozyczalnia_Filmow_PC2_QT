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

    void on_clientsTable_cellClicked(int row, int column);

    void on_moviesTable_cellClicked(int row, int column);

    void on_delMovieButton_clicked();

    void on_addMovieButton_clicked();

    void on_editClientButton_clicked();

    void on_editMovieButton_clicked();

private:
    Ui::MainWindow *ui;

    enum CLIENT_COLLUMNS{
        IMIE, NAZWISKO, PESEL, TELEFON, EMAIL, POSIADANE_FILMY
    };

    enum MOVIE_COLLUMNS{
        TYTUL, REZYSER, GATUNEK, ROK, DOSTEPNE, WYPOZYCZONE
    };
};
#endif // MAINWINDOW_H

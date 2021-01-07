#ifndef ADDBORROWDIALOG_H
#define ADDBORROWDIALOG_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class addBorrowDialog;
}

class addBorrowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addBorrowDialog(QWidget *parent = nullptr, QTableWidget *clientsTable=nullptr, QTableWidget *moviesTable=nullptr, bool id_setting = false);
    ~addBorrowDialog();

    QString borrow_date() const;
    QString return_date() const;
    QString charge() const;
    QString name() const;
    QString surname() const;
    QString title() const;
    QString chosenClientID() const;
    QString chosenMovieID() const;

    int chosenClientRow() const;
    int chosenMovieRow() const;

    std::pair<int,int> chosenMovie() const;

private slots:

    void on_buttonBox_rejected();

    void on_borrowsMoviesTable_currentCellChanged(int currentRow);

    void on_borrowsClientsTable_currentCellChanged(int currentRow);

    void on_buttonBox_accepted();

    void on_searchClientButton_clicked();

    void on_searchMovieButton_clicked();

    void on_searchClientField_returnPressed();

    void on_searchMovieField_returnPressed();

private:
    Ui::addBorrowDialog *ui;
    int clientRow, movieRow;
    QString clientID, movieID;
    QTableWidget *moviesTableTemp;

    enum CLIENT_COLLUMNS{
        IMIE, NAZWISKO, PESEL, TELEFON, EMAIL, POSIADANE_FILMY, ID_KLIENTA
    };

    enum MOVIE_COLLUMNS{
        TYTUL, REZYSER, GATUNEK, ROK, DOSTEPNE, WYPOZYCZONE, ID_FILMU
    };
};

#endif // ADDBORROWDIALOG_H

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
    explicit addBorrowDialog(QWidget *parent = nullptr, QTableWidget *clientsTable=nullptr, QTableWidget *moviesTable=nullptr);
    ~addBorrowDialog();

    QString borrow_date() const;
    QString return_date() const;
    QString charge() const;
    QString name() const;
    QString surname() const;
    QString title() const;

    int chosenClientRow() const;
    int chosenMovieRow() const;

    std::pair<int,int> chosenMovie() const;

private slots:

    void on_buttonBox_rejected();

    void on_borrowsMoviesTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_borrowsClientsTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_buttonBox_accepted();

    void on_searchClientButton_clicked();

    void on_searchMovieButton_clicked();

    void on_searchClientField_returnPressed();

    void on_searchMovieField_returnPressed();

private:
    Ui::addBorrowDialog *ui;
    int clientRow, movieRow;
    QTableWidget *moviesTableTemp;

    enum CLIENT_COLLUMNS{
        IMIE, NAZWISKO, PESEL, TELEFON, EMAIL, POSIADANE_FILMY
    };

    enum MOVIE_COLLUMNS{
        TYTUL, REZYSER, GATUNEK, ROK, DOSTEPNE, WYPOZYCZONE
    };
};

#endif // ADDBORROWDIALOG_H

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
    explicit addBorrowDialog(QWidget *parent = nullptr, QTableWidget *clientsTable=nullptr, QTableWidget *moviesTable=nullptr, bool showIdState = false);
    ~addBorrowDialog();

    QString borrow_date() const;
    QString return_date() const;
    QString arrear() const;
    QString name() const;
    QString surname() const;
    QString title() const;
    QString clientID() const;
    QString movieID() const;

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

private:
    Ui::addBorrowDialog *ui;
    int clientRow, movieRow;
    QTableWidget *moviesTableTemp, *clientsTableTemp;
    QString clientIDTemp, movieIDTemp;

    enum CLIENT_COLLUMNS{
        IMIE=1, NAZWISKO, PESEL, TELEFON, EMAIL, POSIADANE_FILMY
    };

    enum MOVIE_COLLUMNS{
        TYTUL=1, REZYSER, GATUNEK, ROK, DOSTEPNE, WYPOZYCZONE
    };
};

#endif // ADDBORROWDIALOG_H

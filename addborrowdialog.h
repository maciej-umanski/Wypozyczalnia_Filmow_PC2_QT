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
    QString arrear() const;
    QString name() const;
    QString surname() const;
    QString title() const;

private slots:
    void on_buttonBox_rejected();

    void on_borrowsMoviesTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_borrowsClientsTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_buttonBox_accepted();

private:
    Ui::addBorrowDialog *ui;
};

#endif // ADDBORROWDIALOG_H

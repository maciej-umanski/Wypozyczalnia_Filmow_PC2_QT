#ifndef EDITBORROWDIALOG_H
#define EDITBORROWDIALOG_H

#include <QDialog>

namespace Ui {
class editBorrowDialog;
}

class editBorrowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editBorrowDialog(QWidget *parent = nullptr, QString returndate = nullptr);
    ~editBorrowDialog();

    QString returndate() const;

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::editBorrowDialog *ui;
};

#endif // EDITBORROWDIALOG_H

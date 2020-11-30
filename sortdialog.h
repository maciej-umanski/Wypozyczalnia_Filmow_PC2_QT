#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class sortDialog;
}

class sortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit sortDialog(QWidget *parent = nullptr, QTableWidget *table = nullptr);
    ~sortDialog();

    Qt::SortOrder order() const;
    int collumn() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::sortDialog *ui;
};

#endif // SORTDIALOG_H

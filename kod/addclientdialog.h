#ifndef ADDCLIENTDIALOG_H
#define ADDCLIENTDIALOG_H

#include <QDialog>

namespace Ui {
class AddClientDialog;
}

class AddClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddClientDialog(QWidget *parent = nullptr);
    ~AddClientDialog();

    QString name() const;
    QString surname() const;
    QString pesel() const;
    QString phone() const;
    QString email() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddClientDialog *ui;
};

#endif // ADDCLIENTDIALOG_H

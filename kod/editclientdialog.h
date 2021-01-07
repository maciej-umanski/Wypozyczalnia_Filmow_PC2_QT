#ifndef EDITCLIENTDIALOG_H
#define EDITCLIENTDIALOG_H

#include <QDialog>

namespace Ui {
class editClientDialog;
}

class editClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editClientDialog(QWidget *parent = nullptr,
                              QString name = nullptr,
                              QString surname = nullptr,
                              QString pesel = nullptr,
                              QString phone = nullptr,
                              QString email = nullptr);
    ~editClientDialog();

    QString name() const;
    QString surname() const;
    QString pesel() const;
    QString phone() const;
    QString email() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::editClientDialog *ui;
};

#endif // EDITCLIENTDIALOG_H

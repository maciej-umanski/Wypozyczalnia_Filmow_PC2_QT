#ifndef SETPENALTYDIALOG_H
#define SETPENALTYDIALOG_H

#include <QDialog>

namespace Ui {
class setPenaltyDialog;
}

class setPenaltyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit setPenaltyDialog(QWidget *parent = nullptr, float penalty = 0.00);
    ~setPenaltyDialog();

    float penalty() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::setPenaltyDialog *ui;
};

#endif // SETPENALTYDIALOG_H

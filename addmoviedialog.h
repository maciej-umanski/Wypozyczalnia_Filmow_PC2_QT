#ifndef ADDMOVIEDIALOG_H
#define ADDMOVIEDIALOG_H

#include <QDialog>

namespace Ui {
class addMovieDialog;
}

class addMovieDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addMovieDialog(QWidget *parent = nullptr);
    ~addMovieDialog();

    QString title() const;
    QString director() const;
    QString genre() const;
    QString year() const;
    QString count() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::addMovieDialog *ui;
};

#endif // ADDMOVIEDIALOG_H

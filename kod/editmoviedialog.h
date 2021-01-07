#ifndef EDITMOVIEDIALOG_H
#define EDITMOVIEDIALOG_H

#include <QDialog>

namespace Ui {
class editMovieDialog;
}

class editMovieDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editMovieDialog(QWidget *parent = nullptr,
                             QString title = nullptr,
                             QString director = nullptr,
                             QString genre = nullptr,
                             QString year = nullptr,
                             QString available = nullptr);
    ~editMovieDialog();

    QString title() const;
    QString director() const;
    QString genre() const;
    QString year() const;
    QString available() const;


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::editMovieDialog *ui;
};

#endif // EDITMOVIEDIALOG_H

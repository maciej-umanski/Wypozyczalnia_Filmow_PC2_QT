#include "addmoviedialog.h"
#include "ui_addmoviedialog.h"
#include <QMessageBox>
#include <QDate>

addMovieDialog::addMovieDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addMovieDialog)
{
    ui->setupUi(this);
}

addMovieDialog::~addMovieDialog()
{
    delete ui;
}

void addMovieDialog::on_buttonBox_accepted()
{
    QDate date;
    QMessageBox msgBox;
    msgBox.setWindowTitle("Błąd");
    bool yearConversion, availableConversion;
    ui->yearMovieEdit->text().toUInt(&yearConversion);
    ui->availableMovieEdit->text().toUInt(&availableConversion);

    if(
            ui->titleMovieEdit->text().isEmpty() ||
            ui->genreMovieEdit->text().isEmpty() ||
            ui->directorMovieEdit->text().isEmpty() ||
            ui->yearMovieEdit->text().isEmpty() ||
            ui->availableMovieEdit->text().isEmpty())
    {
        msgBox.setText("Wszystkie pola muszą być wypełnione!");
        msgBox.exec();
    }else{
        if(yearConversion
                && availableConversion
                && ui->yearMovieEdit->text().toInt() <= date.currentDate().year()
                && ui->yearMovieEdit->text().toInt() > 0
                && ui->availableMovieEdit->text().toInt() >= 0)
            accept();

        if(!yearConversion || ui->yearMovieEdit->text().toInt() > date.currentDate().year() || ui->yearMovieEdit->text().toInt() <= 0){
            msgBox.setText("Błąd!  Sprawdź poprawność roku!");
            msgBox.exec();
        }
        if(!availableConversion || ui->availableMovieEdit->text().toInt() < 0){
            msgBox.setText("Błąd!  Sprawdź poprawność ilości!");
            msgBox.exec();
        }
    }
}


void addMovieDialog::on_buttonBox_rejected()
{
    reject();
}


QString addMovieDialog::title() const{
    return ui->titleMovieEdit->text();
}

QString addMovieDialog::director() const{
    return ui->directorMovieEdit->text();
}

QString addMovieDialog::genre() const{
    return ui->genreMovieEdit->text();
}

QString addMovieDialog::year() const{
    return ui->yearMovieEdit->text();
}

QString addMovieDialog::available() const{
    return ui->availableMovieEdit->text();
}

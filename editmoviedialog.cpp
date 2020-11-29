#include "editmoviedialog.h"
#include "ui_editmoviedialog.h"
#include <QDate>
#include <QMessageBox>

editMovieDialog::editMovieDialog(QWidget *parent,
                                 QString title,
                                 QString director,
                                 QString genre,
                                 QString year,
                                 QString available) :
    QDialog(parent),
    ui(new Ui::editMovieDialog)
{
    ui->setupUi(this);
    ui->titleMovieEdit->setText(title);
    ui->directorMovieEdit->setText(director);
    ui->genreMovieEdit->setText(genre);
    ui->yearMovieEdit->setText(year);
    ui->availableMovieEdit->setText(available);
}

editMovieDialog::~editMovieDialog()
{
    delete ui;
}

void editMovieDialog::on_buttonBox_accepted()
{
    QDate date;
    QMessageBox msgBox;
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
                && ui->availableMovieEdit->text().toInt() > 0)
            accept();

        if(!yearConversion || ui->yearMovieEdit->text().toInt() > date.currentDate().year() || ui->yearMovieEdit->text().toInt() <= 0){
            msgBox.setText("Błąd!  Sprawdź poprawność roku!");
            msgBox.exec();
        }
        if(!availableConversion || ui->availableMovieEdit->text().toInt() <= 0){
            msgBox.setText("Błąd!  Sprawdź poprawność ilości!");
            msgBox.exec();
        }
    }
}

void editMovieDialog::on_buttonBox_rejected()
{
    reject();
}

QString editMovieDialog::title() const{
    return ui->titleMovieEdit->text();
}

QString editMovieDialog::director() const{
    return ui->directorMovieEdit->text();
}

QString editMovieDialog::genre() const{
    return ui->genreMovieEdit->text();
}

QString editMovieDialog::year() const{
    return ui->yearMovieEdit->text();
}

QString editMovieDialog::available() const{
    return ui->availableMovieEdit->text();
}

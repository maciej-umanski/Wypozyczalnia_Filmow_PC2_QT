#include "setpenaltydialog.h"
#include "ui_setpenaltydialog.h"
#include "QMessageBox"

setPenaltyDialog::setPenaltyDialog(QWidget *parent, float penalty) :
    QDialog(parent),
    ui(new Ui::setPenaltyDialog)
{
    ui->setupUi(this);
    ui->penaltyEdit->setText(QString::number(penalty));
}

setPenaltyDialog::~setPenaltyDialog()
{
    delete ui;
}

void setPenaltyDialog::on_buttonBox_accepted()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Błąd");
    bool succes = false;
    if(ui->penaltyEdit->text().isEmpty()){
        msgBox.setText("Pole nie może być puste!");
        msgBox.exec();
    }
    float number = ui->penaltyEdit->text().toFloat(&succes);
    if(!succes){
        msgBox.setText("Nie wpisano poprawnej wartości!");
        msgBox.exec();
    }else if(number < 0){
        msgBox.setText("Wartość nie może być mniejsza niż 0");
        msgBox.exec();
    }else{
        ui->penaltyEdit->setText(QString::asprintf("%.2f", ui->penaltyEdit->text().toFloat()));
        accept();
    }
}

void setPenaltyDialog::on_buttonBox_rejected()
{
    reject();
}

float setPenaltyDialog::penalty() const{
    return ui->penaltyEdit->text().toFloat();
}

#include "sortdialog.h"
#include "ui_sortdialog.h"

sortDialog::sortDialog(QWidget *parent, QTableWidget *table) :
    QDialog(parent),
    ui(new Ui::sortDialog)
{
    ui->setupUi(this);

    for(int i = 1 ; i < table->columnCount(); i++){
        ui->comboBox->addItem(table->horizontalHeaderItem(i)->text());
    }

}

sortDialog::~sortDialog()
{
    delete ui;
}

void sortDialog::on_buttonBox_accepted()
{
    accept();

}

void sortDialog::on_buttonBox_rejected()
{
    reject();
}

Qt::SortOrder sortDialog::order() const{
    if(ui->comboBox_2->currentIndex() == 0){
        return Qt::AscendingOrder;
    }else{
        return Qt::DescendingOrder;
    }
}

int sortDialog::collumn() const{
    return ui->comboBox->currentIndex()+1;
}


#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getFnScript()
{
    return ui->fn_textbox->toPlainText();
}

QString Dialog::getDfScript()
{
    return ui->df_textbox->toPlainText();
}

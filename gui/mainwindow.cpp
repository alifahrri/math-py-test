#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dialog(new Dialog(this))
{
    ui->setupUi(this);

    f_plot = ui->widget->addGraph();
    df_plot = ui->widget->addGraph();

    f_plot->setPen(QPen(Qt::red,1.0,Qt::SolidLine));
    df_plot->setPen(QPen(Qt::blue,1.0,Qt::DashDotDotLine));

    connect(ui->actionDialog,&QAction::triggered,[=](bool checked)
    {
        if(checked && !dialog->isVisible())
            dialog->show();
        else if(!checked && dialog->isVisible())
            dialog->close();
    });
    connect(this->dialog,&QDialog::finished,[=]
    {
        ui->actionDialog->setChecked(false);
    });
    connect(this->ui->apply_btn,&QPushButton::clicked,[=]
    {
        auto xi = ui->xi_sbox->value();
        auto xf = ui->xf_sbox->value();
        auto step = ui->step_sbox->value();
        auto fn = dialog->getFnScript();
        auto df = dialog->getDfScript();

        if(fn_script)
            fn_script(fn.toStdString());
        if(df_script)
            df_script(df.toStdString());

        double dx = xf-xi;
        QVector<double> keys;
        QVector<double> f_values;
        QVector<double> df_values;
        int x_step = (int)(dx/step);

        if(fn_eval)
        {
            for(int i=0; i<x_step; i++)
            {
                auto x = xi + (i*step);
                auto y = fn_eval(x);
                keys.push_back(x);
                f_values.push_back(y);
            }
            f_plot->setData(keys, f_values);
        }
        if(df_eval)
        {
            for(const auto& x : keys)
                df_values.push_back(df_eval(x));
            df_plot->setData(keys, df_values);
        }
        ui->widget->xAxis->rescale(true);
        ui->widget->yAxis->rescale(true);
        ui->widget->replot();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::FunctionEvalCallback MainWindow::getFn_eval() const
{
    return fn_eval;
}

void MainWindow::setFn_eval(const FunctionEvalCallback &value)
{
    fn_eval = value;
}

MainWindow::FunctionEvalCallback MainWindow::getDf_eval() const
{
    return df_eval;
}

void MainWindow::setDf_eval(const FunctionEvalCallback &value)
{
    df_eval = value;
}

MainWindow::SetFunctionCallback MainWindow::getFn_script() const
{
    return fn_script;
}

void MainWindow::setFn_script(const SetFunctionCallback &value)
{
    fn_script = value;
}

MainWindow::SetFunctionCallback MainWindow::getDf_script() const
{
    return df_script;
}

void MainWindow::setDf_script(const SetFunctionCallback &value)
{
    df_script = value;
}

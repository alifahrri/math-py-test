#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <functional>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class Dialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef std::function<double(double)> FunctionEvalCallback;
    typedef std::function<void(std::string)> SetFunctionCallback;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    FunctionEvalCallback getFn_eval() const;
    void setFn_eval(const FunctionEvalCallback &value);

    FunctionEvalCallback getDf_eval() const;
    void setDf_eval(const FunctionEvalCallback &value);

    SetFunctionCallback getFn_script() const;
    void setFn_script(const SetFunctionCallback &value);

    SetFunctionCallback getDf_script() const;
    void setDf_script(const SetFunctionCallback &value);

private:
    Ui::MainWindow *ui;
    Dialog *dialog;
    FunctionEvalCallback fn_eval = nullptr;
    FunctionEvalCallback df_eval = nullptr;
    SetFunctionCallback fn_script = nullptr;
    SetFunctionCallback df_script = nullptr;
    QCPGraph *f_plot;
    QCPGraph *df_plot;
};

#endif // MAINWINDOW_H

#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include "mainwidget.h"

namespace Ui {
class ProgressDialog;
}

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget *parent = nullptr);
    ~ProgressDialog();

    void setRange(int start,int end);
    void setValue(int val);

public slots:
    void cancel();
    void loadData();

private:
    Ui::ProgressDialog *ui;
    MainWidget *parent;
};

#endif // PROGRESSDIALOG_H

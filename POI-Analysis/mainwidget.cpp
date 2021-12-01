#include "mainwidget.h"
#include "welcomeDialog.h"

#include <QDebug>
MainWidget::MainWidget()
{

    WelcomeDialog *dialog = new WelcomeDialog();
    int res = dialog->exec();
    if (res == QDialog::Accepted){
        filename = dialog->getFilename();
        delete dialog;
        file = new QFile(filename);
        file->open(QIODevice::ReadOnly|QIODevice::Text);
        qDebug() << filename;
    }else if (res == QDialog::Rejected){
        qDebug() << "Rejected";
    }
}



#include "mainwidget.h"
#include "welcomeDialog.h"

#include <QDebug>
MainWidget::MainWidget()
{

    WelcomeDialog *dialog = new WelcomeDialog();
    dialog->exec();
    filename = dialog->getFilename();

    qDebug() << filename;
}



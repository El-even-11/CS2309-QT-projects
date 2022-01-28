#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class WelcomeDialog;
}

class WelcomeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeDialog(QWidget *parent = nullptr);
    ~WelcomeDialog();

    QString getFilename();

public slots:
    void setFile();

private:
    Ui::WelcomeDialog *ui;

    QString filename;
};

#endif // WELCOMEDIALOG_H

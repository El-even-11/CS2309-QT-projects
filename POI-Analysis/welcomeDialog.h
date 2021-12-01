#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>

class WelcomeDialog : public QDialog
{
    Q_OBJECT

public:
    WelcomeDialog();

    QString getFilename();
public slots:
    void setFile();

private:
    QVBoxLayout *container;
    QLabel *label;
    QPushButton *btn;

    QString filename;
};

#endif // WELCOMEDIALOG_H

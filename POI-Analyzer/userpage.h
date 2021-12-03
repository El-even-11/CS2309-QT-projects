#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QChart>

class UserPage : public QWidget
{
    Q_OBJECT
public:
    explicit UserPage(QWidget *parent = nullptr);

public slots:
    void setTimeCharts(bool checked);
    void setPOICharts(bool checked);

private:
    QChart *createTimeChart();

private:
    QGridLayout *gridLayout;

    QLineEdit* input;

    QGroupBox* groupBox;

    QRadioButton* radio1;
    QRadioButton* radio2;
};

#endif // USERPAGE_H

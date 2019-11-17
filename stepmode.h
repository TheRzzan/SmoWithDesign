#ifndef STEPMODE_H
#define STEPMODE_H

#include <QWidget>
#include <analytics.h>

namespace Ui {
class StepMode;
}

class StepMode : public QWidget
{
    Q_OBJECT

public:
    explicit StepMode(QWidget *parent = nullptr);
    ~StepMode();

    void setAnalytics(Morozov::Analytics *value);

    void showAnalytics();

private:
    Ui::StepMode *ui;

    Morozov::Analytics *analytics;
};

#endif // STEPMODE_H

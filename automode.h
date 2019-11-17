#ifndef AUTOMODE_H
#define AUTOMODE_H

#include <QWidget>
#include <analytics.h>

namespace Ui {
class AutoMode;
}

class AutoMode : public QWidget
{
    Q_OBJECT

public:
    explicit AutoMode(QWidget *parent = nullptr);
    ~AutoMode();

    void setAnalytics(Morozov::Analytics *value);

    void showAnalytics();

private slots:
    void on_buttonRefresh_clicked();

private:
    Ui::AutoMode *ui;

    Morozov::Analytics *analytics;
};

#endif // AUTOMODE_H

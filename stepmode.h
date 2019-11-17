#ifndef STEPMODE_H
#define STEPMODE_H

#include <QWidget>
#include <analytics.h>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

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

private slots:
    void on_buttonRefresh_clicked();

    void on_buttonNext_clicked();

    void on_buttonBack_clicked();

private:
    void refreshScene();
    void prepareScene();

    Ui::StepMode *ui;

    Morozov::Analytics *analytics;

    int currentStep;

    std::vector<QGraphicsTextItem*> vecTextSources;
    std::vector<QGraphicsTextItem*> vecTextBuffers;
    std::vector<QGraphicsTextItem*> vecTextDevices;

    QGraphicsScene *scene;
};

#endif // STEPMODE_H

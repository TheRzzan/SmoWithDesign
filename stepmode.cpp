#include "stepmode.h"
#include "ui_stepmode.h"

StepMode::StepMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepMode)
{
    ui->setupUi(this);
}

StepMode::~StepMode()
{
    delete ui;
}

void StepMode::setAnalytics(Morozov::Analytics *value)
{
    analytics = value;
}

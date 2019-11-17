#include "stepmode.h"
#include "ui_stepmode.h"

StepMode::StepMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepMode)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsStep->setScene(scene);
}

StepMode::~StepMode()
{
    delete ui;
}

void StepMode::setAnalytics(Morozov::Analytics *value)
{
    analytics = value;
}

void StepMode::refreshScene()
{
    scene->clear();
    currentStep = 0;
    vecTextBuffers.clear();
    vecTextDevices.clear();
    vecTextSources.clear();
}

void StepMode::prepareScene()
{
    if (analytics->getSteps().size() <= 0)
        return;
    int numSources = analytics->getSteps().at(0).sources.size();
    int numBuffers = analytics->getSteps().at(0).buffers.size();
    int numDevices = analytics->getSteps().at(0).devices.size();

    int height1 = std::max(numSources, numBuffers);
    int height2 = std::max(numBuffers, numDevices);

    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    for (int i = 0; i < numSources; i++) {
        scene->addRect(0, 75*i, 100, 50, blackPen, whiteBrush);
        QGraphicsTextItem *textTmp = scene->addText(("Source" + std::to_string(i+1)).c_str(), QFont());
        vecTextSources.push_back(textTmp);
        textTmp->setX(0);
        textTmp->setY(75*i);
        scene->addLine(QLineF(100, 75*i, 150, 75*i), blackPen);
    }

    scene->addLine(QLineF(150, 0, 150, 75*(height1-1)), blackPen);

    for (int i = 0; i < numBuffers; i++) {
        scene->addRect(200, 75*i, 100, 50, blackPen, whiteBrush);
        QGraphicsTextItem *textTmp = scene->addText(("Buffer" + std::to_string(i+1)).c_str(), QFont());
        vecTextBuffers.push_back(textTmp);
        textTmp->setX(200);
        textTmp->setY(75*i);
        scene->addLine(QLineF(150, 75*i, 350, 75*i), blackPen);
    }

    scene->addLine(QLineF(350, 0, 350, 75*(height2-1)), blackPen);

    for (int i = 0; i < numDevices; i++) {
        scene->addRect(400, 75*i, 100, 50, blackPen, whiteBrush);
        QGraphicsTextItem *textTmp = scene->addText(("Device" + std::to_string(i+1)).c_str(), QFont());
        vecTextDevices.push_back(textTmp);
        textTmp->setX(400);
        textTmp->setY(75*i);
        scene->addLine(QLineF(350, 75*i, 400, 75*i), blackPen);
    }
}

void StepMode::on_buttonRefresh_clicked()
{
    refreshScene();
    prepareScene();
}

void StepMode::on_buttonNext_clicked()
{
    if (currentStep + 1 >= analytics->getSteps().size())
        return;
    if (currentStep < 0){
        currentStep++;
        return;
    }

    currentStep++;

    Morozov::Analytics::StepModel stepModel = analytics->getSteps().at(currentStep);

    for (int i=0; i < vecTextSources.size() && i < stepModel.sources.size(); i++) {
        vecTextSources.at(i)->setPlainText(("Source" + std::to_string(i+1) + "\n" +
                                           stepModel.sources.at(i)).c_str());
    }

    for (int i=0; i < vecTextBuffers.size() && i < stepModel.buffers.size(); i++) {
        vecTextBuffers.at(i)->setPlainText(("Buffer" + std::to_string(i+1) + "\n" +
                                           stepModel.buffers.at(i)).c_str());
    }

    for (int i=0; i < vecTextDevices.size() && i < stepModel.devices.size(); i++) {
        vecTextDevices.at(i)->setPlainText(("Device" + std::to_string(i+1) + "\n" +
                                           stepModel.devices.at(i)).c_str());
    }
}

void StepMode::on_buttonBack_clicked()
{
    if (currentStep <= 0)
        return;
    if (currentStep > analytics->getSteps().size()){
        currentStep--;
        return;
    }

    currentStep--;

    Morozov::Analytics::StepModel stepModel = analytics->getSteps().at(currentStep);

    for (int i=0; i < vecTextSources.size() && i < stepModel.sources.size(); i++) {
        vecTextSources.at(i)->setPlainText(("Source" + std::to_string(i+1) + "\n" +
                                           stepModel.sources.at(i)).c_str());
    }

    for (int i=0; i < vecTextBuffers.size() && i < stepModel.buffers.size(); i++) {
        vecTextBuffers.at(i)->setPlainText(("Buffer" + std::to_string(i+1) + "\n" +
                                           stepModel.buffers.at(i)).c_str());
    }

    for (int i=0; i < vecTextDevices.size() && i < stepModel.devices.size(); i++) {
        vecTextDevices.at(i)->setPlainText(("Device" + std::to_string(i+1) + "\n" +
                                           stepModel.devices.at(i)).c_str());
    }
}

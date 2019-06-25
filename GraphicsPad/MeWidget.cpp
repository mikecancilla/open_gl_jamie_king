#include "MeWidget.h"
#include <Qt\qdebug.h>
#include <QtGui\QVBoxLayout>
#include <QtGui\QHBoxLayout>
#include <MeGlWindow.h>
#include <GuiComponents/DebugSlider.h>

MeWidget::MeWidget()
{
    QVBoxLayout *mainLayout;
    setLayout(mainLayout = new QVBoxLayout);
    
    QVBoxLayout *controlsLayout;
    mainLayout->addLayout(controlsLayout = new QVBoxLayout);

    mainLayout->addWidget(meGlWindow = new MeGlWindow(&theModel));

    QHBoxLayout *lightPositionLayout;
    controlsLayout->addLayout(lightPositionLayout = new QHBoxLayout);

    lightPositionLayout->addWidget(lightXSlider = new DebugSlider);
    lightPositionLayout->addWidget(lightYSlider = new DebugSlider);
    lightPositionLayout->addWidget(lightZSlider = new DebugSlider);

    connect(lightXSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
    connect(lightYSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
    connect(lightZSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
}

MeWidget::~MeWidget()
{
}

void MeWidget::sliderValueChanged()
{
    theModel.lightPosition.x = lightXSlider->value();
    theModel.lightPosition.y = lightYSlider->value();
    theModel.lightPosition.z = lightZSlider->value();

    meGlWindow->repaint();
}
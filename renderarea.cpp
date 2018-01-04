#include "renderarea.h"

using namespace PSCDP;

PSCDP::RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    pixmap.load(":/images/qt-logo.png");

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize PSCDP::RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

QSize PSCDP::RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

void PSCDP::RenderArea::paintEvent(QPaintEvent * /* event */)
{

}

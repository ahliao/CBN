#include "layoutwindow.h"

#include <QGridLayout>

using namespace PSCDP;

PSCDP::LayoutWindow::LayoutWindow(QWidget *parent) : QWidget(parent)
{
    renderArea = new RenderArea();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea, 0, 0, 1, 4);
    setLayout(mainLayout);

    setWindowTitle(tr("Layout Drawing"));
}

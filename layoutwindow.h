#ifndef LAYOUTWINDOW_H
#define LAYOUTWINDOW_H

#include <QWidget>
#include "renderarea.h"

namespace PSCDP
{
    class LayoutWindow : public QWidget
    {
        Q_OBJECT
    public:
        explicit LayoutWindow(QWidget *parent = nullptr);

    signals:

    public slots:

    private:
        RenderArea *renderArea;
    };
}

#endif // LAYOUTWINDOW_H

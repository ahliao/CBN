#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>

namespace PSCDP
{
    class RenderArea : public QWidget
    {
        Q_OBJECT

    public:
        RenderArea(QWidget *parent = 0);

        QSize minimumSizeHint() const override;
        QSize sizeHint() const override;

    public slots:

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        QPixmap pixmap;
    };
}

#endif // RENDERAREA_H

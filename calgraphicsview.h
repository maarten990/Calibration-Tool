#ifndef CALGRAPHICSVIEW_H
#define CALGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>

class CalGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CalGraphicsView(QObject *parent = 0);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QPoint m_rect_start;

signals:
    
public slots:
    
};

#endif // CALGRAPHICSVIEW_H

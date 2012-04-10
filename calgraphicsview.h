#ifndef CALGRAPHICSVIEW_H
#define CALGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsRectItem>

class CalGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CalGraphicsView(QObject *parent = 0);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QPoint m_rect_start;
    QGraphicsRectItem *m_rect;

signals:
    
public slots:
    
};

#endif // CALGRAPHICSVIEW_H

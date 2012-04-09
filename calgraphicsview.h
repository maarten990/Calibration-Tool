#ifndef CALGRAPHICSVIEW_H
#define CALGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class CalGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CalGraphicsView(QObject *parent = 0);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    
public slots:
    
};

#endif // CALGRAPHICSVIEW_H

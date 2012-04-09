#ifndef CALGRAPHICSVIEW_H
#define CALGRAPHICSVIEW_H

#include <QGraphicsView>

class CalGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CalGraphicsView(QObject *parent = 0);
    void resizeEvent(QResizeEvent *event);

signals:
    
public slots:
    
};

#endif // CALGRAPHICSVIEW_H

#include "calgraphicsview.h"

#include <iostream>

CalGraphicsView::CalGraphicsView(QObject *parent)
{
    // intializing the rectangle we draw
    m_rect = new QGraphicsRectItem();
    m_rect->setPen(QPen(Qt::red));
    m_rect->setRect(0, 0, 0, 0);
}

/*
 * event handlers
 */
void CalGraphicsView::mousePressEvent(QMouseEvent *event)
{
    std::cout << "Clicked: " << event->pos().x() << ", " << event->pos().y() << std::endl;
    m_rect_start = event->pos();
}

void CalGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout << "Released: " << event->pos().x() << ", " << event->pos().y() << std::endl;

    // calculating the rectangle's position and dimensions
    QPoint end = event->pos();
    int width = end.x() - m_rect_start.x();
    int height = end.y() - m_rect_start.y();

    // setting the new rect
    m_rect->setPen(QPen(Qt::red));
    m_rect->setRect(m_rect_start.x(), m_rect_start.y(), width, height);
    this->scene()->update();
}

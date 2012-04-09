#include "calgraphicsview.h"

#include <iostream>

CalGraphicsView::CalGraphicsView(QObject *parent)
{
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

    this->scene()->clear();

    QPoint end = event->pos();
    int width = end.x() - m_rect_start.x();
    int height = end.y() - m_rect_start.y();

    this->scene()->addRect(m_rect_start.x(), m_rect_start.y(), width, height);
    this->scene()->update();
}

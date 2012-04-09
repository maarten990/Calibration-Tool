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
}

void CalGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout << "Released: " << event->pos().x() << ", " << event->pos().y() << std::endl;
}

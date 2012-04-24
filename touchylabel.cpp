#include "touchylabel.h"
#include <iostream>
#include <QPainter>
#include <QBrush>

using namespace std;

TouchyLabel::TouchyLabel(QWidget* &w)
{
}

void TouchyLabel::mousePressEvent(QMouseEvent *ev)
{
    m_start_point = ev->pos();
}

void TouchyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QPoint end_point = ev->pos();
    correctSize(&m_end_point);

    int begin_x = m_start_point.x();
    int begin_y = m_start_point.y();
    int width = end_point.x() - m_start_point.x();
    int height = end_point.y() - m_start_point.y();

    m_pixmap_rect = m_pixmap_orig;
    QPainter p(&m_pixmap_rect);
    p.setPen(Qt::magenta);

    p.drawRect(begin_x, begin_y, width, height);
    this->setPixmap(m_pixmap_rect);
}

void TouchyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    m_end_point = ev->pos();
    correctSize(&m_end_point);

    cout << "End: " << m_end_point.x() << ", " << m_end_point.y() << endl;
}

void TouchyLabel::correctSize(QPoint *point) {
    // correcting for viewport size
    if (point->x() > m_pixmap_orig.width() - 1)
        point->setX( m_pixmap_orig.width() - 1);

    if (point->y() > m_pixmap_orig.height() - 1)
        point->setY( m_pixmap_orig.height() - 1);
}

void TouchyLabel::setImage(IplImage *img, IplImage *hsv)
{
    m_pixmap_orig = *(this->pixmap());
    m_img = img;
    m_hsv = hsv;
}

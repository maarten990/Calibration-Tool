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

HSVMinMax TouchyLabel::getValues()
{
    return m_values;
}

void TouchyLabel::setValues()
{
    CvMat *mat = cvCreateMat(m_hsv->height, m_hsv->width, CV_32FC3);
    cvConvert(m_hsv, mat);
    CvScalar scalar;

    for (int x = m_start_point.x(); x < m_end_point.x(); ++x) {
        for (int y = m_start_point.y(); y < m_end_point.y(); ++y) {
            scalar = cvGet2D(mat, y, x);

            // checking the hue
            if (scalar.val[0] < m_values.hue_min)
                m_values.hue_min = scalar.val[0];
            else if (scalar.val[0] > m_values.hue_max)
                m_values.hue_max = scalar.val[0];

            // checking the value
            if (scalar.val[1] < m_values.val_min)
                m_values.val_min = scalar.val[1];
            else if (scalar.val[1] > m_values.val_max)
                m_values.val_max = scalar.val[1];

            // checking the saturation
            if (scalar.val[2] < m_values.sat_min)
                m_values.sat_min = scalar.val[2];
            else if (scalar.val[2] > m_values.sat_max)
                m_values.sat_max = scalar.val[2];
        }
    }
}

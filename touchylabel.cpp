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

void TouchyLabel::setValues(bool reset)
{
    // resetting the old values if required
    if (reset) {
        m_values.reset();
        m_hues.clear();
        m_sats.clear();
        m_vals.clear();
    }


    CvMat *mat = cvCreateMat(m_hsv->height, m_hsv->width, CV_32FC3);
    cvConvert(m_hsv, mat);
    CvScalar scalar;

    for (int x = m_start_point.x(); x < m_end_point.x(); ++x) {
        for (int y = m_start_point.y(); y < m_end_point.y(); ++y) {
            scalar = cvGet2D(mat, y, x);
            m_hues.push_back(scalar.val[0]);
            m_sats.push_back(scalar.val[1]);
            m_vals.push_back(scalar.val[2]);
        }
    }

    // getting the lowest and highest values
    int hue_min = 300, sat_min = 300, val_min = 300;
    int hue_max = -1, sat_max = -1, val_max = -1;

    for (auto& hue : m_hues) {
        hue_min = min(hue_min, hue);
        hue_max = max(hue_max, hue);
    }

    for (auto& sat : m_sats) {
        sat_min = min(sat_min, sat);
        sat_max = max(sat_max, sat);
    }

    for (auto& val : m_vals) {
        val_min = min(val_min, val);
        val_max = max(val_max, val);
    }

    m_hues.clear(); m_sats.clear(); m_vals.clear();
    m_hues.push_back(hue_max);
    m_hues.push_back(hue_min);
    m_sats.push_back(sat_max);
    m_sats.push_back(sat_min);
    m_vals.push_back(val_max);
    m_vals.push_back(val_min);

    m_values.hue_min = hue_min;
    m_values.hue_max = hue_max;
    m_values.sat_min = sat_min;
    m_values.sat_max = sat_max;
    m_values.val_min = val_min;
    m_values.val_max = val_max;
}

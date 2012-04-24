#ifndef TOUCHYLABEL_H
#define TOUCHYLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QPixmap>

#include <cv.h>

class TouchyLabel : public QLabel
{
    Q_OBJECT
public:
    // methods
    explicit TouchyLabel(QWidget*& w);
    void setImage(IplImage *img, IplImage *hsv);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void correctSize(QPoint *point);

    // fields
    QPixmap m_pixmap_orig;
    QPixmap m_pixmap_rect;
    IplImage *m_img;
    IplImage *m_hsv;
    QPoint m_start_point;
    QPoint m_end_point;

signals:
    
public slots:
    
};

#endif // TOUCHYLABEL_H

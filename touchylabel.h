#ifndef TOUCHYLABEL_H
#define TOUCHYLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QPixmap>
#include <vector>
#include "hsvminmax.h"

#include <cv.h>

using namespace std;

class TouchyLabel : public QLabel
{
    Q_OBJECT
public:
    /* methods */
    explicit TouchyLabel(QWidget*& w);
    void setImage(IplImage *img, IplImage *hsv);
    void setValues(bool reset=true);
    HSVMinMax getValues();
    IplImage* getHSVImage();
    IplImage* getImage();

    // magic wand
    void toggleWandMode(int threshold);
    bool getWandMode();
    void setWandThresh(int threshold);

private:
    // methods
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void correctSize(QPoint *point);

    /* fields */
    QPixmap m_pixmap_orig;
    QPixmap m_pixmap_rect;
    IplImage *m_img;
    IplImage *m_hsv;
    QPoint m_start_point;
    QPoint m_end_point;
    HSVMinMax m_values;
    vector<int> m_hues;
    vector<int> m_sats;
    vector<int> m_vals;
    
    // magic wand
    int m_wand_threshold;
    bool m_wand_mode;
    vector<CvPoint> m_wand_points;

signals:
    void magicWanded(vector<CvPoint> *points);
    
public slots:
    
};

#endif // TOUCHYLABEL_H

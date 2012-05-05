#ifndef CONNECTEDCOMPONENT_H
#define CONNECTEDCOMPONENT_H

#include <cv.h>
#include <highgui.h>
#include <vector>

using namespace std;

class ConnectedComponent
{
public:
    ConnectedComponent(IplImage *img, int x, int y, int threshold);
    CvPoint get_points();

private:
    // fields
    vector<CvPoint> m_points;
    vector<CvPoint> m_visited;
    CvScalar m_average;
    IplImage *m_img;

    // methods
    void start_the_wand(int x, int y, int threshold);
    double squared_error(CvPoint a);
    void update_average(CvPoint p);
    void add_neighbours(vector<CvPoint> &stack, CvPoint p);
};

#endif // CONNECTEDCOMPONENT_H

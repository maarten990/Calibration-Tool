#include "connectedcomponent.h"
#include <math.h>
#include <algorithm>

using namespace std;

ConnectedComponent::ConnectedComponent(IplImage *img, int x, int y, int threshold)
{
    m_img = img;
    m_average = cvGet2D(m_img, y, x);
    start_the_wand(x, y, threshold);
}

vector<CvPoint> ConnectedComponent::start_the_wand(int x, int y, int threshold)
{
    vector<CvPoint> stack;
    stack.push_back(cvPoint(x, y));

    CvPoint current;

    // main loop
    while (!stack.empty()) {
        // pop a point from the stack and add it to the list of visited points
        current = stack.pop_back();
        m_visited.push_back(current);

        if (squared_error(current, m_average) < threshold) {
            // adjusting the average and adding the point to the list of points
            update_average(current);
            m_points.push_back(current);

            // adding the surrounding points to the stack
        }
    }
}

// returns the squared error of an image point compared to the current average
// color value
double ConnectedComponent::squared_error(CvPoint p)
{
    // the CvScalars hold a field valled "val" which is an array with a size of
    // 3 (assuming a triple-channel image)
    CvScalar val_p = cvGet2D(m_img, p.y, p.x);

    double error = 0;
    for (int i = 0; i < 3; ++i) {
        error += pow(val_p.val[i] - m_average.val[i], 2);
    }

    return error;
}

// updates the average color values with a given point
void ConnectedComponent::update_average(CvPoint p)
{
    CvScalar new_average = cvScalar(0, 0, 0);
    CvScalar val_p = cvGet2D(m_img, p.y, p.x);
    for (int i = 0; i < 3; ++i) {
        new_average.val[i] = (val_p.val[i] + m_average.val[i]) / 2.0;
    }

    m_average = new_average;
}

// adds the neighbours of point p to the given vector
void ConnectedComponent::add_neighbours(vector<CvPoint> &stack, CvPoint p)
{
    int new_x, new_y;
    CvPoint new_point;
    for (int &i : {-1, 0, 1}) {
        for (int &j : {-1, 0, 1}) {
            new_x = p.x + i;
            new_y = p.y + j;
            new_point = cvPoint(new_x, new_y);
            if (new_x >= 0 && new_x < m_img->width &&
                new_y >= 0 && new_y < m_img->height &&
                (find(m_visited.begin(), m_visited.end(), new_point) == m_visited.end()) &&
                (find(stack.begin(), stack.end(), new_point) == stack.end()))
            {
                stack.push_back(new_point);
            }
        }
    }
}

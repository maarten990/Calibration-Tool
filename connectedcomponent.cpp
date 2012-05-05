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

vector<CvPoint> ConnectedComponent::get_points()
{
    return m_points;
}

void ConnectedComponent::start_the_wand(int x, int y, int threshold)
{
    vector<CvPoint> stack;
    stack.push_back(cvPoint(x, y));

    CvPoint current;

    // main loop
    while (!stack.empty()) {
        // pop a point from the stack and add it to the list of visited points
        current = stack.back();
        stack.pop_back();
        m_visited.push_back(current);

        if (squared_error(current) < threshold) {
            // adjusting the average and adding the point to the list of points
            update_average(current);
            m_points.push_back(current);

            // adding the surrounding points to the stack
            add_neighbours(stack, current);
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

    for (auto &i : {-1, 0, 1}) {
        for (auto &j : {-1, 0, 1}) {
            new_x = p.x + i;
            new_y = p.y + j;
            new_point = cvPoint(new_x, new_y);

            // lambda function for comparison
            auto comparator = [&new_point] (CvPoint p)
            {
                return (p.x == new_point.x) && (p.y == new_point.y);
            };

            if (new_x >= 0 && new_x < m_img->width &&
                new_y >= 0 && new_y < m_img->height &&
                (find_if(m_visited.begin(), m_visited.end(), comparator) == m_visited.end()) &&
                (find_if(stack.begin(), stack.end(), comparator) == stack.end()))
            {
                stack.push_back(new_point);
            }
        }
    }
}

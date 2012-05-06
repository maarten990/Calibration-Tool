#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QPoint>
#include <QtAlgorithms>
#include <QEvent>
#include <QMouseEvent>
#include <vector>

// OpenCV
#include <cv.h>
#include <highgui.h>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    // fields
    Ui::MainWindow *ui;
    QPixmap m_pixmap;

    IplImage *m_image;
    IplImage *m_image_hsv;

    // the vector holding the selected images
    vector<QString> m_paths;
    vector<QString>::iterator m_cur_path;

    // variable to hold whether the current image is a thresholded one
    bool m_cur_is_threshed;

    // methods
    void updateOutput();
    void updateStatus();

public slots:
    void onLoad();
    void onPathChange(QString p);
    void onGetHSV();
    void onAdd();
    void onPrevious();
    void onNext();
    void onThresh();
    void onToggleWand();

signals:
    void pathChanged(QString p);
};

#endif // MAINWINDOW_H

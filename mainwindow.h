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

// OpenCV
#include <cv.h>
#include <highgui.h>

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

    QPoint point_begin;

public slots:
    void onLoad();
    void onPathChange(QString p);
    void onGetHSV();

signals:
    void pathChanged(QString p);
};

#endif // MAINWINDOW_H

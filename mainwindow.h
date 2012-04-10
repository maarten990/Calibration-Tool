#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt
#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPoint>
#include <QResizeEvent>
#include <QtAlgorithms>

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
    QGraphicsScene *m_scene;
    QPixmap m_pixmap;
    QPixmap m_pixmap_backup;

    IplImage *m_image;
    IplImage *m_image_hsv;

    // methods
    void resizeEvent(QResizeEvent *);

public slots:
    void onLoad();
    void onPathChange(QString p);

signals:
    void pathChanged(QString p);
};

#endif // MAINWINDOW_H

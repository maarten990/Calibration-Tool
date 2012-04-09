#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPoint>
#include <QResizeEvent>
#include <QtAlgorithms>

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

    // methods
    void resizeEvent(QResizeEvent *);

public slots:
    void onLoad();
    void onPathChange(QString p);

signals:
    void pathChanged(QString p);
};

#endif // MAINWINDOW_H

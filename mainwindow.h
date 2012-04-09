#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPoint>

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
    Ui::MainWindow *ui;
    QGraphicsScene scene;

public slots:
    void onLoad();
    void onPathChange(QString p);
    void onClicked(QPoint p);

signals:
    void pathChanged(QString p);
};

#endif // MAINWINDOW_H

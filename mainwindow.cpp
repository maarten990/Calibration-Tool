#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene;

    /*
     * connections
     */
    connect(ui->button_load, SIGNAL(clicked()), this, SLOT(onLoad()));
    connect(this, SIGNAL(pathChanged(QString)), this, SLOT(onPathChange(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_scene;
}

/*
 * slots
 */
void MainWindow::onLoad()
{
    QString path = QFileDialog::getOpenFileName(this, "Choose an image", ".");
    emit pathChanged(path);
}

void MainWindow::onPathChange(QString p)
{
    // updating the pixmap/graphicsscene
    m_pixmap = QPixmap(p);
    m_pixmap_backup = m_pixmap;

    delete m_scene;
    m_scene = new QGraphicsScene;

    m_scene->addPixmap(m_pixmap);
    ui->graphics->setScene(m_scene);

    // updating the underlying IplImage
    if (m_image)
        cvReleaseImage(&m_image);
    if (m_image_hsv)
        cvReleaseImage(&m_image_hsv);

    m_image = cvLoadImage(p.toStdString().c_str());
    m_image_hsv = cvCreateImage(cvGetSize(m_image), 8, 3);
    cvCvtColor(m_image, m_image_hsv, CV_BGR2HSV);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    std::cout << "resized" << std::endl;
    m_pixmap = m_pixmap_backup.scaled(ui->graphics->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    delete m_scene;
    m_scene = new QGraphicsScene;

    m_scene->addPixmap(m_pixmap);
    ui->graphics->setScene(m_scene);
}

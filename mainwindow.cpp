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
    m_pixmap = QPixmap(p);
    m_pixmap_backup = m_pixmap;

    delete m_scene;
    m_scene = new QGraphicsScene;

    m_scene->addPixmap(m_pixmap);
    ui->graphics->setScene(m_scene);
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

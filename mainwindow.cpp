#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
     * connections
     */
    connect(ui->button_load, SIGNAL(clicked()), this, SLOT(onLoad()));
    connect(this, SIGNAL(pathChanged(QString)), this, SLOT(onPathChange(QString)));
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onClicked(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
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
    scene.addPixmap( QPixmap(p) );
    ui->graphics->setScene(&scene);
}

void MainWindow::onClicked(QPoint p)
{
    std::cout << "Clicked: " << p.x() << ", " << p.y() << std::endl;
}

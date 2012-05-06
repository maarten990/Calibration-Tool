#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hsvminmax.h"

#include <iostream>
#include <sstream>
#include <QString>
#include <QStringList>
#include <cstdlib>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
     * variable initializations
     */
    m_image = 0;
    m_image_hsv = 0;

    // setting up the imageLabel
    ui->imageLabel->setBackgroundRole(QPalette::Base);
    ui->imageLabel->setAlignment(Qt::AlignTop & Qt::AlignLeft);

    // hiding some elements at first
    ui->imageLabel->setVisible(false);
    ui->output_text->setVisible(false);

    // resizing to the smallest necessary size
    this->resize(0, 0);

    m_cur_is_threshed = false;

    // update the statusbar
    updateStatus();

    /*
     * connections
     */
    connect(ui->button_load, SIGNAL(clicked()), this, SLOT(onLoad()));
    connect(ui->button_values, SIGNAL(clicked()), this, SLOT(onGetHSV()));
    connect(ui->button_add, SIGNAL(clicked()), this, SLOT(onAdd()));
    connect(ui->button_previous, SIGNAL(clicked()), this, SLOT(onPrevious()));
    connect(ui->button_next, SIGNAL(clicked()), this, SLOT(onNext()));
    connect(ui->button_thresh, SIGNAL(clicked()), this, SLOT(onThresh()));
    connect(ui->button_wand, SIGNAL(clicked()), this, SLOT(onToggleWand()));

    connect(ui->imageLabel, SIGNAL(magicWanded(vector<CvPoint>*)), this, SLOT(onWanded(vector<CvPoint>*)));
    connect(ui->input_mwand, SIGNAL(textChanged(QString)), this, SLOT(onThreshChange(QString)));
    connect(this, SIGNAL(pathChanged(QString)), this, SLOT(onPathChange(QString)));
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
    QStringList paths = QFileDialog::getOpenFileNames(this, "Choose your images", ".");

    // setting the member variables
    m_paths = paths.toVector().toStdVector();
    m_cur_path = m_paths.begin();

    // make the "next" button available if more than 1 image is loaded
    if (m_paths.size() > 1)
        ui->button_next->setEnabled(true);
    ui->button_thresh->setEnabled(true);

    emit pathChanged(*m_cur_path);
}

void MainWindow::onPathChange(QString p)
{
    // updating the pixmap/graphicsscene
    m_pixmap = QPixmap(p);

    // updating the underlying IplImage
    if (m_image != 0)
        cvReleaseImage(&m_image);
    if (m_image_hsv != 0)
        cvReleaseImage(&m_image_hsv);

    ui->imageLabel->setPixmap(m_pixmap);
    this->resize(0, 0);

    m_image = cvLoadImage(p.toStdString().c_str());
    m_image_hsv = cvCreateImage(cvGetSize(m_image), 8, 3);
    cvCvtColor(m_image, m_image_hsv, CV_BGR2HSV);

    // passing the iplImage to the QLabel and making it visible
    // if it isn't already
    ui->imageLabel->setImage(m_image, m_image_hsv);

    if (!ui->imageLabel->isVisible())
        ui->imageLabel->setVisible(true);
}

void MainWindow::onGetHSV()
{
    ui->imageLabel->setValues();
    updateOutput();
}

void MainWindow::onAdd()
{
    ui->imageLabel->setValues(false);
    updateOutput();
}

// scrolls to the previous image
void MainWindow::onPrevious()
{
    // decrement the iterator
    m_cur_path--;
    ui->button_next->setEnabled(true);

    if (m_cur_path == m_paths.begin()) {
        ui->button_previous->setEnabled(false);
    }

    // remove the threshold-flag
    m_cur_is_threshed = false;

    emit pathChanged(*m_cur_path);
}

// scrolls to the next image
void MainWindow::onNext()
{
    // increment the iterator
    m_cur_path++;
    ui->button_previous->setEnabled(true);

    if ((m_cur_path + 1) == m_paths.end()) {
        ui->button_next->setEnabled(false);
    }

    // remove the threshold-flag
    m_cur_is_threshed = false;

    emit pathChanged(*m_cur_path);
}

void MainWindow::onThresh()
{
    if (!m_cur_is_threshed) {
        // disabling the value butotns
        ui->button_add->setEnabled(false);
        ui->button_values->setEnabled(false);

        IplImage *hsv = ui->imageLabel->getHSVImage();
        IplImage *threshed = cvCreateImage(cvGetSize(hsv), 8, 1);

        HSVMinMax v = ui->imageLabel->getValues();
        CvScalar lower = cvScalar(v.hue_min, v.sat_min, v.val_min);
        CvScalar upper = cvScalar(v.hue_max, v.sat_max, v.val_max);

        cvInRangeS(hsv, lower, upper, threshed);

        cvSaveImage("temp.png", threshed);

        m_cur_is_threshed = true;
        emit pathChanged(QString("./temp.png"));
    }

    else {
        // enabling the value butotns
        ui->button_add->setEnabled(true);
        ui->button_values->setEnabled(true);

        m_cur_is_threshed = false;
        emit pathChanged(*m_cur_path);
    }
}

void MainWindow::updateOutput()
{
    // set it to be visible if it wasn't already
    if (!ui->output_text->isVisible())
        ui->output_text->setVisible(true);

    HSVMinMax minmax = ui->imageLabel->getValues();

    stringstream sstr;

    // hue
    sstr << "hue_min = " << (int) minmax.hue_min << endl;
    sstr << "hue_max = " << (int) minmax.hue_max << endl;

    // saturation
    sstr << "sat_min = " << (int) minmax.sat_min << endl;
    sstr << "sat_max = " << (int) minmax.sat_max << endl;

    // value
    sstr << "val_min = " << (int) minmax.val_min << endl;
    sstr << "val_max = " << (int) minmax.val_max << endl;

    ui->output_text->setPlainText(QString(sstr.str().c_str()));
    ui->output_text->update();
}

void MainWindow::onToggleWand()
{
    int threshold = atoi(ui->input_mwand->text().toStdString().c_str());
    ui->imageLabel->toggleWandMode(threshold);
    updateStatus();
}

void MainWindow::updateStatus()
{
    if (ui->imageLabel->getWandMode() == true)
        ui->statusBar->showMessage("Wand mode: Enabled");
    else
        ui->statusBar->showMessage("Wand mode: Disabled");
}

void MainWindow::onWanded(vector<CvPoint> *points)
{
    cout << "Wanded!" << endl;
    cout << points->size() << endl;
    IplImage *hsv = ui->imageLabel->getHSVImage();

    for (auto &p : *points) {
        cvSet2D(m_image, p.y, p.x, cvScalar(255, 0, 0));
    }

    cvSaveImage("blobbed.png", m_image);
    emit pathChanged(QString("./blobbed.png"));
}

void MainWindow::onThreshChange(QString p)
{
    int threshold = atoi(p.toStdString().c_str());
    ui->imageLabel->setWandThresh(threshold);
}

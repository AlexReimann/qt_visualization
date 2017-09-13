#include "../../include/qt_visualization/qgl_visualization_viewer.hpp"

#include <GL/glew.h>
#include <GL/glu.h>
#include <Eigen/Dense>
#include <unsupported/Eigen/OpenGLSupport>

namespace qt_visualization
{

QGLVisualizationViewer::QGLVisualizationViewer(QWidget* parent) :
    qglv::QGLViewer(parent)
{
  hough_image_ = NULL;
  camera()->setType(qglviewer::Camera::ORTHOGRAPHIC);
}

void QGLVisualizationViewer::setLineDrawer(GLListDrawerPtr line_drawer)
{
  line_drawer_ = line_drawer;
}

void QGLVisualizationViewer::setHoughPlanes(HoughPlanesPtr hough_planes)
{
  hough_planes_ = hough_planes;
}

void QGLVisualizationViewer::setHoughImage(QLabel* hough_image)
{
  hough_image_ = hough_image;
}

void QGLVisualizationViewer::updatePx(const int& slider_value)
{
  hough_planes_->updatePx(slider_value);
  draw();
  QGLWidget::updateGL();
}

void QGLVisualizationViewer::updatePy(const int& slider_value)
{
  hough_planes_->updatePy(slider_value);
  draw();
  QGLWidget::updateGL();
}

void QGLVisualizationViewer::draw()
{
  if (line_drawer_)
  {
    line_drawer_->draw();
  }

  Eigen::MatrixXd votes = hough_planes_->getVotes();

  double max = votes.maxCoeff();

  QImage hough_image(votes.cols(), votes.rows(), QImage::Format_RGB32);

  for (int y = 0; y < votes.rows(); ++y)
  {
    for (int x = 0; x < votes.cols(); ++x)
    {
      int value = (votes(y, x) * 255);
      hough_image.setPixel(x, y, qRgb(value, value, value));

      if (votes(y, x) == max)
      {
        hough_image.setPixel(x, y, qRgb(255, 0, 0));
      }
    }
  }

  QImage scaled_image = hough_image.scaled(300, 100);
  hough_image_->setPixmap(QPixmap::fromImage(scaled_image));

  drawAxis();
  qglv::QGLViewer::draw();
}

} // namespace

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
  Eigen::MatrixXd votes = hough_planes_->getVotes();

//  std::cout << "votes: " << std::endl << votes.transpose() << std::endl << std::endl;

  double max = votes.maxCoeff();

  QImage hough_image(votes.cols(), votes.rows(), QImage::Format_RGB32);

  std::vector<std::pair<int, int>> best;

  for (int y = 0; y < votes.rows(); ++y)
  {
    for (int x = 0; x < votes.cols(); ++x)
    {
      int value = (votes(y, x) * 255);
      hough_image.setPixel(x, y, qRgb(value, value, value));

      if (votes(y, x) == max)
      {
        best.push_back(std::make_pair(x, y));
      }
    }
  }

  for (int i = 0; i < best.size(); ++i)
  {
    hough_image.setPixel(best[i].first, best[i].second, qRgb(255, 0, 0));
//    drawNeighbours(best[i].first, best[i].second, hough_image);

    hough_planes_->test(best[i].second, best[i].first);
  }

  QImage scaled_image = hough_image.scaled(1200, 300);
  QPixmap pixmap = QPixmap::fromImage(scaled_image);
  hough_image_->setPixmap(pixmap);

  if (line_drawer_)
  {
    line_drawer_->draw();
  }

  drawAxis();
  qglv::QGLViewer::draw();
}

void QGLVisualizationViewer::drawNeighbours(const int& x, const int& y, QImage& image)
{
  int temp_x = x;
  int temp_y = y;

  enforceBounds(temp_x, temp_y, image);
  image.setPixel(temp_x, temp_y, qRgb(255, 0, 0));

  temp_x = x + 1;
  temp_y = y + 1;
  enforceBounds(temp_x, temp_y, image);
  image.setPixel(temp_x, temp_y, qRgb(255, 0, 0));

  temp_x = x + 1;
  temp_y = y - 1;
  enforceBounds(temp_x, temp_y, image);
  image.setPixel(temp_x, temp_y, qRgb(255, 0, 0));

  temp_x = x - 1;
  temp_y = y - 1;
  enforceBounds(temp_x, temp_y, image);
  image.setPixel(temp_x, temp_y, qRgb(255, 0, 0));

  temp_x = x - 1;
  temp_y = y + 1;
  enforceBounds(temp_x, temp_y, image);
  image.setPixel(temp_x, temp_y, qRgb(255, 0, 0));
}

void QGLVisualizationViewer::enforceBounds(int& x, int& y, const QImage& image)
{
  x = std::min(std::max(x, 0), image.size().width());
  y = std::min(std::max(y, 0), image.size().height());
}

} // namespace

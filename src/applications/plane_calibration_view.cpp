#include "qt_visualization/plane_calibration_ui.hpp"
#include "qt_visualization/gl_list_drawer.hpp"
#include "qt_visualization/hough_planes.hpp"

#include <Eigen/Dense>

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPushButton>
#include <QPixmap>

#include <memory>
#include <string>

using namespace qt_visualization;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  GLListDrawerPtr line_drawer = std::make_shared<GLListDrawer>();

  std::shared_ptr<QPixmap> pixmap;

  HoughPlanes planes(line_drawer);
  planes.setup();
  planes.run();

  Eigen::MatrixXd votes = planes.getVotes();

  std::cout << votes << std::endl;

  PlaneCalibrationUI main_window;
  main_window.qgl_viewer->setLineDrawer(line_drawer);

  QImage hough_image(votes.cols(), votes.rows(), QImage::Format_RGB32);

  for (int y = 0; y < votes.rows(); ++y)
  {
    for (int x = 0; x < votes.cols(); ++x)
    {
      int value = (votes(y, x) * 255);
      hough_image.setPixel(x, y, qRgb(value, value, value));
    }
  }

  QImage scaled_image = hough_image.scaled(300, 100);
  main_window.imageLabel->setPixmap(QPixmap::fromImage(scaled_image));

  main_window.show();

  return app.exec();
}

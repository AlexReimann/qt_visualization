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

  HoughPlanesPtr planes = std::make_shared<HoughPlanes>(line_drawer);
  planes->setup();
  planes->run();

  PlaneCalibrationUI main_window;
  main_window.qgl_viewer->setLineDrawer(line_drawer);
  main_window.qgl_viewer->setHoughPlanes(planes);
  main_window.qgl_viewer->setHoughImage(main_window.imageLabel);

  QObject::connect(main_window.pxSlider, SIGNAL(valueChanged(int)),
                   main_window.qgl_viewer, SLOT(updatePx(const int&)));
  QObject::connect(main_window.pySlider, SIGNAL(valueChanged(int)),
                   main_window.qgl_viewer, SLOT(updatePy(const int&)));

  main_window.show();

  return app.exec();
}

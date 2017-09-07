#include "qt_visualization/plane_calibration_ui.hpp"
#include "qt_visualization/gl_list_drawer.hpp"
#include "qt_visualization/hough_planes.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPushButton>

#include <memory>
#include <string>

using namespace qt_visualization;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  GLListDrawerPtr line_drawer = std::make_shared<GLListDrawer>();

  HoughPlanes planes(line_drawer);
  planes.setup();
  planes.run();

  PlaneCalibrationUI main_window;
  main_window.qgl_viewer->setLineDrawer(line_drawer);

  main_window.show();

  return app.exec();
}

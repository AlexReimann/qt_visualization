#include "qt_visualization/plane_calibration_ui.hpp"

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

  PlaneCalibrationUI main_window;
  main_window.widget->setLineDrawer(line_drawer);

  Eigen::Vector3f test1(1, 2, 3);
  Eigen::Vector3f test2(4, 5, 6);

  line_drawer->addLine(test1, test2);

  main_window.show();

  return app.exec();
}

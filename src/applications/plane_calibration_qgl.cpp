#include "qt_visualization/plane_calibration_qgl.hpp"

#include <GL/glew.h>
#include <GL/glu.h>

#include <Eigen/Dense>
#include <unsupported/Eigen/OpenGLSupport>

namespace qt_visualization
{

PlaneCalibrationQGL::PlaneCalibrationQGL(QWidget* parent) :
    qglv::QGLViewer(parent)
{
}

void PlaneCalibrationQGL::setLineDrawer(GLListDrawerPtr line_drawer)
{
  line_drawer_ = line_drawer;
}

void PlaneCalibrationQGL::draw()
{
  if (line_drawer_)
  {
    line_drawer_->draw();
  }

  qglv::QGLViewer::draw();
}

} // namespace

#include "qt_visualization/plane_calibration_qgl.hpp"

namespace qt_visualization
{

PlaneCalibrationQGL::PlaneCalibrationQGL(QWidget *parent) :
    qglv::QGLViewer(parent)
{
}

void PlaneCalibrationQGL::draw()
{
  qglv::QGLViewer::draw();
}

} // namespace

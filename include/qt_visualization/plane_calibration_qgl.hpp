#ifndef qt_visualization_PLANE_CALIBRATION_QGL_HPP_
#define qt_visualization_PLANE_CALIBRATION_QGL_HPP_

#include <QWidget>

// rendering headers
#include <qglv/opengl.hpp> // must be 1st for correct seq. of gl headers
#include <qglv/extras.hpp>

namespace qt_visualization
{

class PlaneCalibrationQGL : public qglv::QGLViewer
{
  Q_OBJECT
public :
  PlaneCalibrationQGL(QWidget *parent);
  virtual ~PlaneCalibrationQGL() {};

  virtual void draw();

  qglv::TeleportArrow origin_teleport_arrow;
  qglv::TeleportArrow destination_teleport_arrow;
};

}  // namespace

#endif

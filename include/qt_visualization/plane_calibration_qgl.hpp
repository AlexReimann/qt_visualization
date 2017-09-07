#ifndef qt_visualization_PLANE_CALIBRATION_QGL_HPP_
#define qt_visualization_PLANE_CALIBRATION_QGL_HPP_

#include "gl_list_drawer.hpp"

#include <QWidget>

// rendering headers
#include <qglv/opengl.hpp> // must be 1st for correct seq. of gl headers
#include <qglv/extras.hpp>

namespace qt_visualization
{

class PlaneCalibrationQGL : public qglv::QGLViewer
{
  Q_OBJECT
public:
  PlaneCalibrationQGL(QWidget* parent);
  virtual ~PlaneCalibrationQGL()
  {
  }

  void setLineDrawer(GLListDrawerPtr line_drawer);
  virtual void draw();

protected:
  GLListDrawerPtr line_drawer_;
};

} // namespace

#endif

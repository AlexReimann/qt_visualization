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
}

void QGLVisualizationViewer::setLineDrawer(GLListDrawerPtr line_drawer)
{
  line_drawer_ = line_drawer;
}

void QGLVisualizationViewer::draw()
{
  if (line_drawer_)
  {
    line_drawer_->draw();
  }

  qglv::QGLViewer::draw();
}

} // namespace

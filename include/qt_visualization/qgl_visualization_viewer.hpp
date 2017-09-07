#ifndef qt_visualization_QGL_VISUALIZATION_VIEWER_HPP_
#define qt_visualization_QGL_VISUALIZATION_VIEWER_HPP_

#include "gl_list_drawer.hpp"

#include <QWidget>

// rendering headers
#include <qglv/opengl.hpp> // must be 1st for correct seq. of gl headers
#include <qglv/extras.hpp>

namespace qt_visualization
{

class QGLVisualizationViewer : public qglv::QGLViewer
{
  Q_OBJECT
public:
  QGLVisualizationViewer(QWidget* parent);
  virtual ~QGLVisualizationViewer()
  {
  }

  void setLineDrawer(GLListDrawerPtr line_drawer);
  virtual void draw();

protected:
  GLListDrawerPtr line_drawer_;
};

} // namespace

#endif

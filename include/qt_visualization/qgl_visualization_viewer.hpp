#ifndef qt_visualization_QGL_VISUALIZATION_VIEWER_HPP_
#define qt_visualization_QGL_VISUALIZATION_VIEWER_HPP_

#include "gl_list_drawer.hpp"
#include "qt_visualization/hough_planes.hpp"

#include <QWidget>
#include <QLabel>

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
  void setHoughPlanes(HoughPlanesPtr hough_planes);
  void setHoughImage(QLabel* hough_image_);
  virtual void draw();

public slots:
  void updatePx(const int& slider_value);
  void updatePy(const int& slider_value);

protected:
  GLListDrawerPtr line_drawer_;
  HoughPlanesPtr hough_planes_;
  QLabel* hough_image_;
};

} // namespace

#endif

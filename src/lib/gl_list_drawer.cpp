#include "qt_visualization/gl_list_drawer.hpp"

namespace qt_visualization
{
GLListDrawer::GLListDrawer()
{
}

void GLListDrawer::addLine(const Eigen::Vector3f& point1, const Eigen::Vector3f& point2, const std::string& id)
{
  addLine_(point1.x(), point1.y(), point1.z(), point2.x(), point2.y(), point2.z(), id);
}

void GLListDrawer::addLine(const float& point1_x, const float& point1_y, const float& point1_z, const float& point2_x,
                           const float& point2_y, const float& point2_z, const std::string& id)
{
  addLine_(point1_x, point1_y, point1_z, point2_x, point2_y, point2_z, id);
}

void GLListDrawer::addLine_(const float& point1_x, const float& point1_y, const float& point1_z, const float& point2_x,
                            const float& point2_y, const float& point2_z, const std::string& id)
{
  std::lock_guard<std::mutex> lock(mutex_);
  lines_[id].add(point1_x, point1_y, point1_z, point2_x, point2_y, point2_z);
}

void GLListDrawer::clearLines(const std::string& id)
{
  std::lock_guard<std::mutex> lock(mutex_);
  lines_.erase(id);
}

void GLListDrawer::clearAllLines()
{
  std::lock_guard<std::mutex> lock(mutex_);
  lines_.clear();
}

void GLListDrawer::draw()
{
  std::lock_guard<std::mutex> lock(mutex_);
  for (auto lines : lines_)
  {
    lines.second.draw();
  }
}

} //  namespace
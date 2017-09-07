#ifndef qt_visualization_GL_LIST_DRAWER_HPP_
#define qt_visualization_GL_LIST_DRAWER_HPP_

#include <GL/glew.h>
#include <GL/glu.h>

#include <Eigen/Dense>

#include <map>
#include <vector>
#include <memory>
#include <mutex>

namespace qt_visualization
{

class GLListDrawer
{
public:
  class GLGenList
  {
  public:
    GLGenList(const Eigen::Vector3f& color = Eigen::Vector3f(0.0f, 0.0f, 0.0f))
    {
      updated_ = false;
      gl_list_id_ = -1;
      color_ = color;
    }

    virtual ~GLGenList()
    {
      deleteOldList();
    }

    void draw()
    {
      if (updated_)
      {
        deleteOldList();

        gl_list_id_ = ::glGenLists(1);
        glNewList(gl_list_id_, GL_COMPILE);
        {
          update();
        }
        glEndList();
        updated_ = false;
      }
      ::glCallList(gl_list_id_);
    }

  protected:
    virtual void update() = 0;
    void deleteOldList()
    {
      if (gl_list_id_ > 0)
      {
        glDeleteLists(gl_list_id_, 1);
      }
    }

    bool updated_;
    int gl_list_id_;
    Eigen::Vector3f color_;
  };

  class Lines : public GLGenList
  {
  public:
    Lines(const Eigen::Vector3f& color = Eigen::Vector3f(0.0f, 0.0f, 0.0f), const float& line_width = 1.0f) :
        GLGenList(color)
    {
      line_width_ = line_width;
    }

    Lines(const float& line_width)
    {
      line_width_ = line_width;
    }

    void add(const float& point1_x, const float& point1_y, const float& point1_z, const float& point2_x,
             const float& point2_y, const float& point2_z)
    {
      line_coordinates_.push_back(point1_x);
      line_coordinates_.push_back(point1_y);
      line_coordinates_.push_back(point1_z);

      line_coordinates_.push_back(point2_x);
      line_coordinates_.push_back(point2_y);
      line_coordinates_.push_back(point2_z);
      updated_ = true;
    }

  protected:
    virtual void update() override
    {
      glColor3f(0.1f, 0.2f, 0.1f);
      glLineWidth(1.0f);
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_FLOAT, 0, line_coordinates_.data());
      glDrawArrays(GL_LINES, 0, line_coordinates_.size() / 3);
      glDisableClientState(GL_VERTEX_ARRAY);
    }

    float line_width_;
    std::vector<float> line_coordinates_;
  };

  GLListDrawer();
  virtual ~GLListDrawer()
  {
  }

  virtual void addLine(const Eigen::Vector3f& point1, const Eigen::Vector3f& point2, const std::string& id = "");
  virtual void addLine(const float& point1_x, const float& point1_y, const float& point1_z, const float& point2_x,
                       const float& point2_y, const float& point2_z, const std::string& id = "");

  virtual void clearLines(const std::string& id = "");
  virtual void clearAllLines();

  virtual void draw();

protected:
  virtual void addLine_(const float& point1_x, const float& point1_y, const float& point1_z, const float& point2_x,
                        const float& point2_y, const float& point2_z, const std::string& id = "");

  std::mutex mutex_;
  std::map<std::string, Lines> lines_;
};
typedef std::shared_ptr<GLListDrawer> GLListDrawerPtr;

} //  namespace

#endif

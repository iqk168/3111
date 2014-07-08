#ifndef __DRAWADAPTER_H_
#define __DRAWADAPTER_H_


//class EGenericROI;

namespace Euresys
{
  inline double RadianToDegrees(double angle)
  { 
    return (angle * 360.0f) / 6.28318530718f;
  }

  typedef Euresys::eVision::Point Euresys_Point;

  // Draw Adapter Interface
  struct DrawAdapter
  {
  public:
    // Draw Methods
    virtual void Point(const int x1, const int y1, const ::Euresys::RGBColor& traceColor= ::Euresys::RGBColor::NoColor, double opacity= 1)= 0;

    virtual void Line(const int x1, const int y1, const int x2, const int y2, const ::Euresys::RGBColor& traceColor= ::Euresys::RGBColor::NoColor)= 0;
    virtual void Arc(const int orgX, const int orgY, const int width, const int height, const double startAngle, const double amplitude, const ::Euresys::RGBColor& traceColor= ::Euresys::RGBColor::NoColor)= 0;

    virtual void Rectangle(const int orgX, const int orgY, const int width, const int height, const ::Euresys::RGBColor& traceColor= ::Euresys::RGBColor::NoColor)= 0;
    virtual void Polygon(const Euresys::eVision::Utils::Vector<Euresys_Point> & points, const ::Euresys::RGBColor& traceColor= ::Euresys::RGBColor::NoColor)= 0;
    virtual void Ellipse(const int orgX, const int orgY, const int width, const int height, const ::Euresys::RGBColor& traceColor= ::Euresys::RGBColor::NoColor)= 0;

    virtual void FilledRectangle(const int orgX, const int orgY, const int width, const int height, const ::Euresys::RGBColor& traceColor= ::Euresys::RGBColor::NoColor , const ::Euresys::RGBColor& fillColor= ::Euresys::RGBColor::NoColor)= 0;
    virtual void FilledEllipse(const int orgX, const int orgY, const int width, const int height, const ::Euresys::RGBColor& traceColor= ::Euresys::RGBColor::NoColor , const ::Euresys::RGBColor& fillColor= ::Euresys::RGBColor::NoColor)= 0;
    virtual void FilledPolygon(const Euresys::eVision::Utils::Vector< Euresys::eVision::Point >& points, const ::Euresys::RGBColor& traceColor= ::Euresys::RGBColor::NoColor , const ::Euresys::RGBColor& fillColor= ::Euresys::RGBColor::NoColor)= 0;

    virtual void Text(const std::string& text, const int x, const int y, const ::Euresys::RGBColor& textColor= ::Euresys::RGBColor::NoColor)= 0;
    virtual void BackedText(const std::string& text, const int x, const int y, const ::Euresys::RGBColor& textColor= ::Euresys::RGBColor::NoColor, const ::Euresys::RGBColor& backColor= ::Euresys::RGBColor::NoColor)= 0;

    virtual void Image(const EGenericROI& image, const float zoomX= 1, const float zoomY= 0, const int panX= 0, const int panY= 0, double opacity = 1, const ::Euresys::RGBColor& overlayColor = ::Euresys::RGBColor::NoColor)= 0;

    // Helpers
    virtual Euresys::eVision::Point GetTextSize(const std::string& text)= 0;

    virtual int GetPenThickness()= 0;
  };
}

#endif

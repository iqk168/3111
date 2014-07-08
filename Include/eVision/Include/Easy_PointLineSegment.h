// Easy_PointLineSegment.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_POINTLINESEGMENT_H__
#define __EASY_POINTLINESEGMENT_H__

namespace Euresys
{
  namespace eVision
  {

    template<typename Type> struct TemplatePoint {
      Type  x;
      Type  y;
      TemplatePoint( Type x_, Type y_ ) { 
        x = x_; y = y_; } 
      TemplatePoint( ) { } 

      bool operator== (const TemplatePoint& pt) const {
        if (pt.x != x)
          return false;
        if (pt.y != y)
          return false;
        return true;
      }

      bool operator!= (const TemplatePoint& pt) const {
        if (pt.x != x)
          return true;
        if (pt.y != y)
          return true;
        return false;
      }

      TemplatePoint operator=(const TemplatePoint& pt)
      {
        if (this!=&pt)
        {
          x=pt.x;
          y=pt.y;
        }
        return *this;
      }
    };

    typedef TemplatePoint<double> Point;
    typedef TemplatePoint<INT32>  Pointn32;

    struct Line
    {
      double x;
      double y;
      double angle;
    };

    struct Segment: public Line
    {
      double length;
    };

  }
}

#endif //__EASY_POINTLINESEGMENT_H__

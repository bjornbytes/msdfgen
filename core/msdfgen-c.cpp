#include "../msdfgen-c.h"
#include "../msdfgen.h"
#include "Shape.h"
#include "Bitmap.h"
#include <math.h>

using namespace msdfgen;

#ifdef __cplusplus
extern "C" {
#endif

msShape* msShapeCreate() {
  Shape* shape = new Shape;
  return reinterpret_cast<msShape*>(shape);
}

void msShapeDestroy(msShape* cShape) {
  delete reinterpret_cast<Shape*>(cShape);
}

msContour* msShapeAddContour(msShape* cShape) {
  Shape* shape = reinterpret_cast<Shape*>(cShape);
  return reinterpret_cast<msContour*>(&shape->addContour());
}

void msShapeNormalize(msShape* cShape) {
  reinterpret_cast<Shape*>(cShape)->normalize();
}

void msEdgeColoringSimple(msShape* cShape, double angleThreshold, unsigned long long seed) {
  Shape* shape = reinterpret_cast<Shape*>(cShape);
  edgeColoringSimple(*shape, angleThreshold, seed);
}

void msContourAddLinearEdge(msContour* cContour, float x1, float y1, float x2, float y2) {
  Contour* contour = reinterpret_cast<Contour*>(cContour);
  Point2 p0(x1, y1);
  Point2 p1(x2, y2);
  contour->addEdge(new LinearSegment(p0, p1));
}

void msContourAddQuadraticEdge(msContour* cContour, float x1, float y1, float x2, float y2, float x3, float y3) {
  Contour* contour = reinterpret_cast<Contour*>(cContour);
  Point2 p0(x1, y1);
  Point2 p1(x2, y2);
  Point2 p2(x3, y3);
  contour->addEdge(new QuadraticSegment(p0, p1, p2));
}

void msContourAddCubicEdge(msContour* cContour, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
  Contour* contour = reinterpret_cast<Contour*>(cContour);
  Point2 p0(x1, y1);
  Point2 p1(x2, y2);
  Point2 p2(x3, y3);
  Point2 p3(x4, y4);
  contour->addEdge(new CubicSegment(p0, p1, p2, p3));
}

void msGenerateMSDF(uint8_t* data, int w, int h, msShape* cShape, float range, float sx, float sy, float dx, float dy) {
  Shape* shape = reinterpret_cast<Shape*>(cShape);
  Bitmap<FloatRGB> bitmap(w, h);

  generateMSDF(bitmap, *shape, range, Vector2(sx, sy), Vector2(dx, dy));

  int i = 0;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      float r = bitmap(x, y).r;
      float g = bitmap(x, y).g;
      float b = bitmap(x, y).b;
      data[i++] = isfinite(r) ? clamp(int(r * 0x100), 0xff) : 0xff;
      data[i++] = isfinite(g) ? clamp(int(g * 0x100), 0xff) : 0xff;
      data[i++] = isfinite(b) ? clamp(int(b * 0x100), 0xff) : 0xff;
    }
  }
}

#ifdef __cplusplus
}
#endif

#include "../msdfgen-c.h"
#include "../msdfgen.h"
#include "Shape.h"
#include "Bitmap.h"

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

void msGenerateSDF(float* data, int w, int h, msShape* cShape, double range, float sx, float sy, float dx, float dy) {
  Shape* shape = reinterpret_cast<Shape*>(cShape);
  const BitmapRef<float, 1> bitmap(data, w, h);
  generateSDF(bitmap, *shape, range, Vector2(sx, sy), Vector2(dx, dy));
}

void msGeneratePseudoSDF(float* data, int w, int h, msShape* cShape, double range, float sx, float sy, float dx, float dy) {
  Shape* shape = reinterpret_cast<Shape*>(cShape);
  const BitmapRef<float, 1> bitmap(data, w, h);
  generatePseudoSDF(bitmap, *shape, range, Vector2(sx, sy), Vector2(dx, dy));
}

void msGenerateMSDF(float* data, int w, int h, msShape* cShape, double range, float sx, float sy, float dx, float dy) {
  Shape* shape = reinterpret_cast<Shape*>(cShape);
  const BitmapRef<float, 3> bitmap(data, w, h);
  generateMSDF(bitmap, *shape, range, Vector2(sx, sy), Vector2(dx, dy));
}

void msGenerateMTSDF(float* data, int w, int h, msShape* cShape, double range, float sx, float sy, float dx, float dy) {
  Shape* shape = reinterpret_cast<Shape*>(cShape);
  const BitmapRef<float, 4> bitmap(data, w, h);
  generateMTSDF(bitmap, *shape, range, Vector2(sx, sy), Vector2(dx, dy));
}

#ifdef __cplusplus
}
#endif

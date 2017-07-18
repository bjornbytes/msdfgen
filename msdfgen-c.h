#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct msEdge;
struct msContour;
struct msShape;
typedef struct msEdge msEdge;
typedef struct msContour msContour;
typedef struct msShape msShape;

msShape* msShapeCreate();
void msShapeDestroy(msShape* shape);
msContour* msShapeAddContour(msShape* shape);
void msShapeNormalize(msShape* cShape);
void msEdgeColoringSimple(msShape* cShape, double angleThreshold, unsigned long long seed);
void msContourAddLinearEdge(msContour* cContour, float x1, float y1, float x2, float y2);
void msContourAddQuadraticEdge(msContour* cContour, float x1, float y1, float x2, float y2, float x3, float y3);
void msContourAddCubicEdge(msContour* cContour, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void msGenerateMSDF(uint8_t* data, int w, int h, msShape* shape, float range, float sx, float sy, float dx, float dy);

#ifdef __cplusplus
}
#endif

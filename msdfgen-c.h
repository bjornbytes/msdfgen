#pragma once

#if defined(_WIN32) && defined(_MSDFGEN_BUILD_DLL)
/* We are building MSDFgen as a Win32 DLL */
#define MSDFGEN_API __declspec(dllexport)
#elif defined(_WIN32)
/* We are calling MSDFgen as a Win32 DLL */
#define MSDFGEN_API  __declspec(dllimport)
#elif defined(__GNUC__)
/* We are building MSDFgen as a shared / dynamic library */
#define MSDFGEN_API  __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct msEdge;
struct msContour;
struct msShape;
typedef struct msEdge msEdge;
typedef struct msContour msContour;
typedef struct msShape msShape;

MSDFGEN_API msShape* msShapeCreate(void);
MSDFGEN_API void msShapeDestroy(msShape* shape);
MSDFGEN_API msContour* msShapeAddContour(msShape* shape);
MSDFGEN_API void msShapeNormalize(msShape* cShape);
MSDFGEN_API void msEdgeColoringSimple(msShape* cShape, double angleThreshold, unsigned long long seed);
MSDFGEN_API void msContourAddLinearEdge(msContour* cContour, float x1, float y1, float x2, float y2);
MSDFGEN_API void msContourAddQuadraticEdge(msContour* cContour, float x1, float y1, float x2, float y2, float x3, float y3);
MSDFGEN_API void msContourAddCubicEdge(msContour* cContour, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
MSDFGEN_API void msGenerateSDF(float* data, int w, int h, msShape* shape, double range, float sx, float sy, float dx, float dy);
MSDFGEN_API void msGeneratePseudoSDF(float* data, int w, int h, msShape* shape, double range, float sx, float sy, float dx, float dy);
MSDFGEN_API void msGenerateMSDF(float* data, int w, int h, msShape* shape, double range, float sx, float sy, float dx, float dy);
MSDFGEN_API void msGenerateMTSDF(float* data, int w, int h, msShape* shape, double range, float sx, float sy, float dx, float dy);

#ifdef __cplusplus
}
#endif

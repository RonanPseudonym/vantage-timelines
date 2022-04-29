/*
   TYPES USED FOR PARSING SHAPEFILES
   PRIMARY SOURCE: http://dl.maptools.org/dl/shapelib/shapefile.pdf
*/

#ifndef SHP_TYPES
#define SHP_TYPES

typedef struct _Point Point;
typedef struct _MultiPoint MultiPoint;
typedef struct _PolyLine PolyLine;
typedef struct _Polygon Polygon;
typedef struct _PointM PointM;
typedef struct _MultiPointM MultiPointM;
typedef struct _PolyLineM PolyLineM;
typedef struct _PolygonM PolygonM;
typedef struct _PointZ PointZ;
typedef struct _MultiPointZ MultiPointZ;
typedef struct _PolyLineZ PolyLineZ;
typedef struct _PolygonZ PolygonZ;
typedef struct _MultiPatch MultiPatch;

typedef struct _ShpHeader ShpHeader;

struct _Point {
    double x;
    double y;
};

struct _MultiPoint {
    double box[4];
    int    num_points;
    void*  points; // num_points VLA : Point[]
};

struct _PolyLine {
    double box[4];
    int    num_parts;
    int    num_points;
    void*  parts;  // num_parts VLA : int[]
    void*  points; // num_points VLA : Point[]
};

struct _Polygon {
    double box[4];
    int    num_parts;
    int    num_points;
    void*  parts;  // num_parts VLA : int[]
    void*  points; // num_points VLA : Point[]
};

struct _PointM {
    double x;
    double y;
    double m;
};

struct _MultiPointM {
    double box[4];
    int    num_points;
    void*  points;  // num_points VLA : Point[]
    double m_range[2];
    void*  m_array; // num_points VLA : double[]
};

struct _PolyLineM {
    double box[4];
    int    num_parts;
    int    num_points;
    void*  parts;  // num_parts VLA : int[]
    void*  points; // num_points VLA : Point[]
    double m_range[2];
    void*  m_array; // num_points VLA : double[]
};

struct _PolygonM {
    double box[4];
    int    num_parts;
    int    num_points;
    void*  parts;  // num_parts VLA : int[]
    void*  points; // num_points VLA : Point[]
    double m_range[2];
    void*  m_array; // num_points VLA : double[]
};

struct _PointZ {
    double x;
    double y;
    double z;
    double m;
};

struct _MultiPointZ {
    double box[4];
    int    num_points;
    void*  points;  // num_points VLA : Point[]
    double z_range[2];
    void*  z_array; // num_points VLA : double[]
    double m_range[2];
    void*  m_array; // num_points VLA : double[]
};

struct _PolyLineZ {
    double box[4];
    int    num_parts;
    int    num_points;
    void*  parts;   // num_parts VLA : int[]
    void*  points;  // num_points VLA : Point[]
    double z_range[2];
    void*  z_array; // num_points VLA : double[]
    double m_range[2];
    void*  m_array; // num_points VLA : double[]
};

struct _PolygonZ {
    double box[4];
    int    num_parts;
    int    num_points;
    void*  parts;   // num_parts VLA : int[]
    void*  points;  // num_points VLA : Point[]
    double z_range[2];
    void*  z_array; // num_points VLA : double[]
    double m_range[2];
    void*  m_array; // num_points VLA : double[]
};

struct _MultiPatch {
    double box[4];
    int    num_parts;
    int    num_points;
    void*  parts;      // num_parts VLA : int[]
    void*  part_types; // num_parts VLA : int[]
    void*  points;     // num_points VLA : Point[]
    double z_range[2];
    void*  z_array;    // num_points VLA : double[]
    double m_range[2];
    void*  m_array;    // num_points VLA : double[]
};

struct _ShpHeader {
    int file_length;
    int version;
    int shape_type;
    double x_min;
    double y_min;
    double x_max;
    double y_max;
    double z_min;
    double z_max;
    double m_min;
    double m_max;
};

Point       NEW_POINT       ();
MultiPoint  NEW_MULTIPOINT  (int num_points);
PolyLine    NEW_POLYLINE    (int num_parts, int num_points);
Polygon     NEW_POLYGON     (int num_parts, int num_points);
PointM      NEW_POINTM      ();
MultiPointM NEW_MULTIPOINTM (int num_points);
PolyLineM   NEW_POLYLINEM   (int num_parts, int num_points);
PolygonM    NEW_POLYGONM    (int num_parts, int num_points);
PointZ      NEW_POINTZ      ();
MultiPointZ NEW_MULTIPOINTZ (int num_points);
PolyLineZ   NEW_POLYLINEZ   (int num_parts, int num_points);
PolygonZ    NEW_POLYGONZ    (int num_parts, int num_points);
MultiPatch  NEW_MULTIPATCH  (int num_parts, int num_points);

ShpHeader   NEW_SHPHEADER   ();

#endif

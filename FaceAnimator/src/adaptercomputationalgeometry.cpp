#include "adaptercomputationalgeometry.h"

AdapterComputationalGeometry::AdapterComputationalGeometry(){

    }

char AdapterComputationalGeometry::SegTriInt(Vect* T,Vect q,Vect r){
    SegmentTriangleIntersection segmenttriangleintersection;
    tPointi Tpoints;
    tPointd qpoints;
    tPointd rpoints;
    tPointd ppoints;

	segmenttriangleintersection.Vertices[0][0]=T[0].getPunto().getX();
	segmenttriangleintersection.Vertices[0][1]=T[0].getPunto().getY();
	segmenttriangleintersection.Vertices[0][2]=T[0].getPunto().getZ();
	segmenttriangleintersection.Vertices[1][0]=T[1].getPunto().getX();
	segmenttriangleintersection.Vertices[1][1]=T[1].getPunto().getY();
	segmenttriangleintersection.Vertices[1][2]=T[1].getPunto().getZ();
	segmenttriangleintersection.Vertices[2][0]=T[2].getPunto().getX();
	segmenttriangleintersection.Vertices[2][1]=T[2].getPunto().getY();
	segmenttriangleintersection.Vertices[2][2]=T[2].getPunto().getZ();

	Tpoints[0]=0;
	Tpoints[1]=1;
	Tpoints[2]=2;

	qpoints[0]=q.getPunto().getX();
	qpoints[1]=q.getPunto().getY();
	qpoints[2]=q.getPunto().getZ();

	rpoints[0]=r.getPunto().getX();
	rpoints[1]=r.getPunto().getY();
	rpoints[2]=r.getPunto().getZ();

	return segmenttriangleintersection.SegTriInt(Tpoints,qpoints,rpoints,ppoints);
	}

char AdapterComputationalGeometry::SegPlaneInt(Vect* T, Vect q, Vect r){
    SegmentTriangleIntersection segmenttriangleintersection;
    tPointi Tpoints;
    tPointd qpoints;
    tPointd rpoints;
    tPointd ppoints;
    int m;

	segmenttriangleintersection.Vertices[0][0]=T[0].getPunto().getX();
	segmenttriangleintersection.Vertices[0][1]=T[0].getPunto().getY();
	segmenttriangleintersection.Vertices[0][2]=T[0].getPunto().getZ();
	segmenttriangleintersection.Vertices[1][0]=T[1].getPunto().getX();
	segmenttriangleintersection.Vertices[1][1]=T[1].getPunto().getY();
	segmenttriangleintersection.Vertices[1][2]=T[1].getPunto().getZ();
	segmenttriangleintersection.Vertices[2][0]=T[2].getPunto().getX();
	segmenttriangleintersection.Vertices[2][1]=T[2].getPunto().getY();
	segmenttriangleintersection.Vertices[2][2]=T[2].getPunto().getZ();

	Tpoints[0]=0;
	Tpoints[1]=1;
	Tpoints[2]=2;

	qpoints[0]=q.getPunto().getX();
	qpoints[1]=q.getPunto().getY();
	qpoints[2]=q.getPunto().getZ();

	rpoints[0]=r.getPunto().getX();
	rpoints[1]=r.getPunto().getY();
	rpoints[2]=r.getPunto().getZ();

	char resultado=segmenttriangleintersection.SegPlaneInt(Tpoints,qpoints,rpoints,ppoints,&m);

	return resultado;
    }

AdapterComputationalGeometry::~AdapterComputationalGeometry(){

	}

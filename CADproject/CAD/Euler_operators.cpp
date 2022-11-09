#include "Half_Edge_DS.h"
#include <map>
#include <iterator>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <vector>
std::tuple<Vertex*, Face*, Solid*> mvfs(const Coord& coord)
{
	auto solid = new Solid;
	auto face = new Face;
	auto loop = new Loop;
	auto vertex = new Vertex;

	solid->faces.push_back(face);
	face->fsolid = solid;

	face->Loopout = loop;
	loop->lface = face;

	vertex->coord = coord;
	solid->vertices.push_back(vertex);

	return std::make_tuple(vertex, face, solid);
}

std::tuple<Edge*, Vertex*> mev(Vertex* v0, Loop* loop, Coord coord)
{
	auto v1 = new Vertex;
	auto edge = new Edge;
	auto he0 = new HalfEdge;
	auto he1 = new HalfEdge;

	v1->coord = coord;
	he0->vertex = v0;
	he1->vertex = v1;

	he0->next = he1;
	he1->prev = he0;

	he0->eg = edge;
	he1->eg = edge;
	he0->wloop = loop;
	he1->wloop = loop;

	edge->he0 = he0;
	edge->he1 = he1;

	if (loop->ledge == nullptr) {
		loop->ledge = he0;
		he0->prev = he1;
		he1->next = he0;
	}
	else {
		auto tmp = loop->find(v0);
		he0->prev = tmp->prev;
		he1->next = tmp;

		he0->prev->next = he0;
		he1->next->prev = he1;
	}

	auto solid = loop->lface->fsolid;
	solid->edges.push_back(edge);
	solid->vertices.push_back(v1);

	return std::make_tuple(edge, v1);
}

std::tuple<Edge*, Face*> mef(Loop* loop0, Vertex* v0, Vertex* v1)
{
	auto solid = loop0->lface->fsolid;
	auto face = new Face;
	auto loop1 = new Loop;
	auto edge = new Edge;
	auto he0 = new HalfEdge;
	auto he1 = new HalfEdge;

	solid->faces.push_back(face);
	face->fsolid = loop0->lface->fsolid;
	face->Loopout = loop1;
	solid->edges.push_back(edge);
	edge->he0 = he0;
	edge->he1 = he1;
	loop1->lface = face;

	auto tmphe0 = loop0->find(v0);
	auto tmphe1 = loop0->find(v1);

	he0->next = tmphe1;
	he0->prev = tmphe0->prev;
	he1->next = tmphe0;
	he1->prev = tmphe1->prev;

	tmphe0->prev->next = he0;
	tmphe1->prev->next = he1;
	tmphe0->prev = he1;
	tmphe1->prev = he0;

	he0->wloop = loop0;
	he0->eg = edge;
	he1->wloop = loop1;
	he1->eg = edge;
	he0->vertex = v0;
	he1->vertex = v1;
	loop1->ledge = he1;
	loop0->ledge = he0;
	return std::make_tuple(edge, face);
}

std::tuple<Loop*> kemr(Vertex* v0, Vertex* v1, Loop* loop0)
{
	auto solid = loop0->lface->fsolid;
	auto loop1 = new Loop;

	HalfEdge* he0 = loop0->ledge;
	HalfEdge* he1 = he0->next;
	while (he0->vertex != v0 || he1->vertex != v1) {
		he0 = he1;
		he1 = he0->next;
	}

	loop0->ledge = he1->next;
	he0->prev->next = he1->next;
	he1->next->prev = he0->prev;
	loop1->lface = loop0->lface;
	loop1->lface->Loopins.push_back(loop1);
	auto edge = he0->eg;
	solid->edges.remove(edge);
	delete edge;
	delete he0;
	delete he1;
	return std::make_tuple(loop1);
}

void kfmrh(Loop* Loopout, Loop* Loopin)
{
	auto solid = Loopout->lface->fsolid;
	Loopout->lface->Loopins.push_back(Loopin);
	delete Loopin->lface;
	solid->faces.remove(Loopin->lface);
	Loopin->lface = Loopout->lface;
}

Coord operator + (Coord c0, Coord c1)
{
	c0.x += c1.x;
	c0.y += c1.y;
	c0.z += c1.z;
	return c0;
}

void Sweep(Face* face, Coord dir)
{
	auto extrude = [](Loop* loop, Coord dir)
	{
		auto endVertex = loop->ledge->vertex;
		auto he = loop->ledge;

		auto oriRet = mev(he->vertex, loop, he->vertex->coord + dir);
		he = he->next;
		auto lastRet = oriRet;
		while (he->vertex != endVertex) {
			auto ret = mev(he->vertex, loop, he->vertex->coord + dir);
			mef(loop, std::get<1>(lastRet), std::get<1>(ret));
			lastRet = ret;
			he = he->next;
		}
		mef(loop, std::get<1>(lastRet), std::get<1>(oriRet));
	};

	extrude(face->Loopout, dir);
	for (auto loop : face->Loopins)
		extrude(loop, dir);
}

void Print(Solid* solid, const std::string& path)
{
	//创建流对象
	std::ofstream ofs{ path };

	std::vector<Vertex*> vertVec;
	for (auto vertex : solid->vertices) {
		vertVec.push_back(vertex);
	}
	std::vector<Loop*> loopVec;
	for (auto face : solid->faces) {
		loopVec.push_back(face->Loopout);
		for (auto loop : face->Loopins)
			loopVec.push_back(loop);
	}
	//写入数据
	ofs << "BRP" << std::endl;
	ofs << vertVec.size() << ' '
		<< loopVec.size() << ' '
		<< solid->faces.size() << ' '
		<< 1 << std::endl;

	for (auto itr = vertVec.begin(); itr != vertVec.end(); itr++) {
		auto vert = *itr;
		ofs << vert->coord.x << ' '
			<< vert->coord.y << ' '
			<< vert->coord.z
			<< std::endl;
	}

	for (auto itr = loopVec.begin(); itr != loopVec.end(); itr++) {
		auto loop = *itr;
		int a = vertVec.size();
		ofs << 4 << ' ';
		auto he = loop->ledge;
		ofs << std::distance(vertVec.begin(), std::find(vertVec.begin(), vertVec.end(), he->vertex)) << ' ';
		he = he->next;
		while (he != loop->ledge) {
			ofs << std::distance(vertVec.begin(), std::find(vertVec.begin(), vertVec.end(), he->vertex)) << ' ';
			he = he->next;
		}
		ofs << std::endl;
	}

	for (auto face : solid->faces) {
		ofs << std::distance(loopVec.begin(), std::find(loopVec.begin(), loopVec.end(), face->Loopout)) << ' '
			<< face->Loopins.size() << ' ';
		for (auto loop : face->Loopins) {
			ofs << std::distance(loopVec.begin(), std::find(loopVec.begin(), loopVec.end(), loop)) << ' ';
		}
		ofs << 0 << std::endl;
	}

}

HalfEdge* Loop::find(Vertex* vertex)
{
	auto he = ledge;
	while (he) {
		if (he->vertex == vertex) return he;
		he = he->next;
		if (he == ledge) break;
	}
	return nullptr;
}

HalfEdge* HalfEdge::mate()
{
	return eg->he0 == this ? eg->he1 : eg->he0;
}

#include <list>
#include <array>
#include <tuple>
#include <string>

struct Solid;
struct Face;
struct Loop;
struct HalfEdge;
struct Edge;
struct Vertex;


struct Coord
{
	float x, y, z;
};

struct Function
{
	float x, y, z, s;
};

struct Vertex
{
	Coord coord;
};

struct Edge
{
	HalfEdge* he0 = nullptr;
	HalfEdge* he1 = nullptr;
};

struct HalfEdge
{

	Loop* wloop = nullptr;
	Edge* eg = nullptr;
	Vertex* vertex = nullptr;

	HalfEdge* next = nullptr;
	HalfEdge* prev = nullptr;

	HalfEdge* mate();
};

struct Loop
{
	Face* lface = nullptr;
	HalfEdge* ledge = nullptr;

	HalfEdge* find(Vertex* vertex);
};

struct Face
{
	Solid* fsolid = nullptr;
	Loop* Loopout = nullptr;
	std::list<Loop*>	Loopins;
};

struct Solid
{
	std::list<Face*>	faces;
	std::list<Edge*>	edges;
	std::list<Vertex*>	vertices;
};

std::tuple<Vertex*, Face*, Solid*> mvfs(const Coord& coord);
std::tuple<Edge*, Vertex*> mev(Vertex* v0, Loop* loop, Coord coord);
std::tuple<Edge*, Face*> mef(Loop* loop, Vertex* v0, Vertex* v1);
std::tuple<Loop*> kemr(Vertex* v0, Vertex* v1, Loop* loop0);
void kfmrh(Loop* Loopout, Loop* Loopin);
void Sweep(Face* face, Coord dir);
void Print(Solid* solid, const std::string& path);
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMeshT.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

#include <iostream>
#include <vector>
#include <set>
#include <queue>

typedef OpenMesh::TriMeshT<OpenMesh::TriMesh_ArrayKernelT<>> Mesh;

// Global variables
Mesh mesh;
OpenMesh::VPropHandleT<double> property_distance;

// Compares which vertex has the shorter distance
class DistanceComparator {
public:
	bool operator() (const Mesh::VertexHandle vh1, const Mesh::VertexHandle vh2) {
		return mesh.property(property_distance, vh1) > mesh.property(property_distance, vh2);
	}
};

bool was_visited(Mesh::VertexHandle vh) {
	// unvisted vertices are initialized with an infinite distance
	return std::isfinite(mesh.property(property_distance, vh));
}

//// Exercise 1: Find mesh properties ////

int num_vertices(const Mesh &mesh) {
	int vertices = 0;
	// TODO: Implement this
	return vertices;
}

int num_faces(const Mesh &mesh) {
	int faces = 0;
	// TODO: Implement this
	return faces;
}

int maximum_degree(const Mesh &mesh) {
	int max_degree = -std::numeric_limits<int>::infinity();
	// TODO: Implement this
	return max_degree;
}


//// Exercise 2: Calculcate the distance between two points on a mesh using Dijkstra's algorithm //
double distance_on_mesh(Mesh &mesh, const Mesh::VertexHandle vh_start, const Mesh::VertexHandle vh_target) {
	double distance = std::numeric_limits<double>::infinity();

	// Initialize the property with infinity to mark unvisited vertices
	for(auto vh: mesh.vertices()) {
		mesh.property(property_distance, vh) = std::numeric_limits<double>::infinity();
	}

	// The distance from the start vertex to itself is 0
	mesh.property(property_distance, vh_start) = 0.0;

	// A priority queue, which sorts the vertices by the distance to the source vertex
	std::priority_queue<Mesh::VertexHandle, std::vector<Mesh::VertexHandle>, DistanceComparator> queue;
	queue.push(vh_start);

	// Process vertices as long as the queue is not empty and the target is not found
	while(!queue.empty()) {
		// TODO: Implement the loop body
		break;

		// Hints:
		// - Loop invariant: all vertices in the queue have a valid distance, which is sum of the lengths
		//   of the edges on the shortest path between source_vh and the vertex.
		// - The top vertex in the priority queue always has the shortest path from the source vertex of all
		//   visited vertices.
		// - All vertices that need to be inserted into the queue at the end of the loop were not visisted before.
		// - Break the loop when the target vertex is found and assign its distance value to the "distance" variable.
		// - The only case when the loop is terminated because of an empty queue is when the target vertex cannot be reached.
		// - You can either use the Mesh::Point::norm method for distance calculations or the Mesh::calc_edge_length method,
		//   depending on which type of iterators you use for finding neighboring vertices.
	}

	return distance;
}

//// Excercise 3: Use the distance values to trace a path from the target vertex back to the source vertex ////
std::vector<Mesh::VertexHandle> trace_back(const Mesh &mesh, const Mesh::VertexHandle target_vh) {
	// Attention: This function only works after distance_on_mesh was executed with the same target_vh.

	std::vector<Mesh::VertexHandle> result_path;
	Mesh::VertexHandle current_vh = target_vh;
	result_path.push_back(target_vh);

	// Hints:
	// - Each vertex on the path has a property with its distance to the source.
	// - Each vertex in an optimal path from the target to the source has a smaller distance than the vertex before.
	// - The source vertex has distance 0.

	// TODO: Implement this

	assert(mesh.property(property_distance, result_path.back()) == 0);

	std::reverse(result_path.begin(), result_path.end());
	return result_path;
}

int main(int argc, char **argv) {
	OpenMesh::IO::read_mesh(mesh, "example.obj");
	// Add a property handle to vertices, which stores a double value.
	mesh.add_property(property_distance);

	std::cout << "Vertices:                           " << num_vertices(mesh) << std::endl;
	std::cout << "Faces:                              " << num_faces(mesh) << std::endl;
	std::cout << "Maximum degree:                     " << maximum_degree(mesh) << std::endl;

	Mesh::VertexHandle source_vh = mesh.vertex_handle(0);
	Mesh::VertexHandle target_vh = mesh.vertex_handle(4200);

	double distance = distance_on_mesh(mesh, source_vh, target_vh);
	std::cout << "Distance between Vertex " << source_vh.idx() << " and " << target_vh.idx() << ": " << distance << std::endl;

	if(0.092 > distance || distance > 0.094) {
		std::cout << "Wrong distance" << std::endl;
		return 1;
	}

	std::vector<Mesh::VertexHandle> path = trace_back(mesh, target_vh);
	std::cout << "Num path vertices:                  " << path.size() << std::endl;
	if(path.size() != 76) {
		std::cout << "Wrong path length." << std::endl;
		return 1;
	}
	if(path.front() != source_vh || path.back() != target_vh) {
		std::cout << "Wrong source or target" << std::endl;
		return 1;
	}

	std::cout << std::endl;
	std::cout << "Path:";
	for(auto vh: path) {
		std::cout << " " << vh.idx();
	}
	std::cout << std::endl;

	return 0;
}

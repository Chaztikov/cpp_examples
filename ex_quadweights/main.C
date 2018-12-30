#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <stdint.h>
#include <sys/time.h>
#include <typeinfo>
#include <utility>

#include <libmesh/dirichlet_boundaries.h>
#include <boost/math/special_functions/binomial.hpp>

#include <libmesh/elem.h>
#include <libmesh/equation_systems.h>
#include <libmesh/exact_solution.h>
#include <libmesh/exodusII_io.h>
#include <libmesh/getpot.h>

#include <libmesh/libmesh.h>

#include <libmesh/mesh.h>
#include <libmesh/mesh_generation.h>
#include <libmesh/mesh_modification.h>
#include <libmesh/mesh_refinement.h>
#include <libmesh/replicated_mesh.h>
#include <libmesh/serial_mesh.h>

#include <libmesh/node.h>

using namespace libMesh;

typedef std::map<const Elem *, std::vector<const Elem *>> ElemPatchMap;
typedef std::map<const Elem *, std::vector<const Node *>> ElemNodeMap;
typedef std::map<Node, std::vector<const Node *>> NodePatchMap;
typedef std::map<Node, std::vector<const Elem *>> NodeElemMap;

template <typename T>
class Range
{
public:
  class iterator
  {
  public:
    explicit iterator(T val, T stop, T step)
        : m_val(val), m_stop(stop), m_step(step) {}
    iterator &operator++()
    {
      m_val += m_step;
      if ((m_step > 0 && m_val >= m_stop) || (m_step < 0 && m_val <= m_stop))
      {
        m_val = m_stop;
      }
      return *this;
    }
    iterator operator++(int)
    {
      iterator retval = *this;
      ++(*this);
      return retval;
    }
    bool operator==(iterator other) const { return m_val == other.m_val; }
    bool operator!=(iterator other) const { return !(*this == other); }
    T operator*() const { return m_val; }

  private:
    T m_val, m_stop, m_step;
  };

  explicit Range(T stop) : m_start(0), m_stop(stop), m_step(1) {}

  explicit Range(T start, T stop, T step = 1)
      : m_start(start), m_stop(stop), m_step(step) {}

  iterator begin() const { return iterator(m_start, m_stop, m_step); }
  iterator end() const { return iterator(m_stop, m_stop, m_step); }

private:
  T m_start, m_stop, m_step;
};

template <typename T>
Range<T> range(T stop) { return Range<T>(stop); }

template <typename T>
Range<T> range(T start, T stop, T step = 1)
{
  return Range<T>(start, stop, step);
}

void mesh_build_neighborhood(const Mesh &mesh, Real horizon);

void mesh_build_neighborhood(const Mesh &mesh, Real horizon)
{
  ElemNodeMap map_elem_node;
  NodePatchMap map_node_patch;
  NodeElemMap map_node_elem;
  std::set<Number> xinorm_unique_values;

  //   std::unique_ptr<PointLocatorBase> locator = mesh.sub_point_locator();
  for (const auto &elem : mesh.active_element_ptr_range())
  {

    std::vector<const Point *> xi_node_values;
    std::set<const Node *> elemnodes_patch;

    for (const auto &node : elem->node_ref_range())
    {

      std::set<const Elem *> point_patch;
      std::set<const Node *> node_patch;

      elem->find_point_neighbors(node, point_patch);

      for (const auto &neighbor : point_patch)
        for (const auto ii : neighbor->node_index_range())
        {
          const Point xi(node - *(neighbor->node_ptr(ii)));

          if (xi.norm() <= horizon &&
              node_patch.count(neighbor->node_ptr(ii)) < 1)
          {
            xinorm_unique_values.insert(xi.norm());

            elemnodes_patch.insert(neighbor->node_ptr(ii));
            node_patch.insert(neighbor->node_ptr(ii));

            xi_node_values.push_back(&xi);
          }
        }

      std::vector<const Elem *> elemvec(point_patch.begin(), point_patch.end());
      map_node_elem.insert(std::make_pair(node, elemvec));

      std::vector<const Node *> nodevec(node_patch.begin(), node_patch.end());
      map_node_patch.insert(std::make_pair(node, nodevec));
    }

    std::vector<const Node *> elemnodevec(elemnodes_patch.begin(),
                                          elemnodes_patch.end());
    map_elem_node.insert(std::make_pair(elem, elemnodevec));
  }
}

template <typename T>
std::vector<double> get_trap_quadweights(T qorder) {

  switch (qorder) {

    case 1: {
      std::vector<double> dx{1, -2, 1};
      return dx;
    }

    case 2: {
      std::vector<double> dx{1, -4, 6, -4, 1};
      return dx;
    }

    case 3: {
      std::vector<double> dx{1, -6, 15, -20, 15, -6, 1};
      return dx;
    }

    case 4: {
      std::vector<double> dx{1, -8, 28, -56, 70, -56, 28, -8, 1};
      return dx;
    }

    case 5: {
      std::vector<double> dx{1, -10, 45, -120, 210, -252, 210, -120, 45, -10, 1};
      return dx;
    }
  }
}

template <typename T>
T get_trap_quadweights(const unsigned int qorder)
{
  
}



// template <typename T>
// template <typename T2>
// inline
// TypeVector<T>::TypeVector (const TypeVector<T2> & p)
// {
//   // copy the nodes from vector p to me
//   for (unsigned int i=0; i<LIBMESH_DIM; i++)
//     _coords[i] = p._coords[i];
// }

void print_binomial_coefficients(int nn)
{
  for (auto i : range(-nn / 2, (nn) / 2 + 1, 1))
  {
    std::cout << "\n " << i
              << " " << i + nn / 2
              << " " << i
              << " " << boost::math::binomial_coefficient<double>(nn, i + nn / 2);
  }
  // std::endl;
}

template <typename T>
inline T pt2vec(const Point &p)
{
  T pout{p(0), p(1), p(2)};
  return pout;
}
// auto pt2vec = [](const Point &p){ Eigen::Vector3d pout{p(0),p(1),p(2)}; return pout;};

template <typename T>
inline T binomial_coefficients(int nn)
{
  T pout;
  for (auto i : range(-nn / 2, (nn) / 2 + 1, 1))
    pout.push_back(
        boost::math::binomial_coefficient<double>(nn, i + nn / 2));
  return pout;
}

template <typename T>
inline void print(const T &vec)
{
  std::cout << "\n ";
  for (auto coord : vec) // range(vec.size()))
    std::cout << "  " << coord;
  // std::endl;
}



// template <typename T>
// inline T qtrap(int nn)
Eigen::MatrixXd compute_qtrap(int nn, double horizon=1)
{
  int sgn = nn%2==0 ? -1 : 0;

  Eigen::MatrixXd quad(2,2*nn+1);
  Eigen::MatrixXd qpoints(2,2*nn+1);

  for (auto i : range(2*nn+1))
  {
    // qpoints(i) = (i - (nn))*horizon ;
    quad(0,i) = boost::math::binomial_coefficient<double>(2*nn, i) * std::pow(-1, i+sgn);
    quad(1,i) = (i - (nn))*horizon ;
  }

  return quad;
}



  // ReplicatedMesh* _mesh;

  // ReplicatedMesh* build_mesh()
  // {
  //   ReplicatedMesh  mesh = new ReplicatedMesh(*TestCommWorld);

  //   // (0,1)           (1,1)
  //   // x---------------x
  //   // |               |
  //   // |               |
  //   // |               |
  //   // |               |
  //   // |               |
  //   // x---------------x
  //   // (0,0)           (1,0)
  //   // |               |
  //   // |               |
  //   // |               |
  //   // |               |
  //   // x---------------x
  //   // (0,-1)          (1,-1)

  //   _mesh->set_mesh_dimension(2);

  //   _mesh->add_point( Point(0.0,-1.0), 4 );
  //   _mesh->add_point( Point(1.0,-1.0), 5 );
  //   _mesh->add_point( Point(1.0, 0.0), 1 );
  //   _mesh->add_point( Point(1.0, 1.0), 2 );
  //   _mesh->add_point( Point(0.0, 1.0), 3 );
  //   _mesh->add_point( Point(0.0, 0.0), 0 );

  //   {
  //     Elem* elem_top = _mesh->add_elem( new Quad4 );
  //     elem_top->set_node(0) = _mesh->node_ptr(0);
  //     elem_top->set_node(1) = _mesh->node_ptr(1);
  //     elem_top->set_node(2) = _mesh->node_ptr(2);
  //     elem_top->set_node(3) = _mesh->node_ptr(3);

  //     // Elem* elem_bottom = _mesh->add_elem( new Quad4 );
  //     // elem_bottom->set_node(0) = _mesh->node_ptr(4);
  //     // elem_bottom->set_node(1) = _mesh->node_ptr(5);
  //     // elem_bottom->set_node(2) = _mesh->node_ptr(1);
  //     // elem_bottom->set_node(3) = _mesh->node_ptr(0);

  //     Elem* edge = _mesh->add_elem( new Edge2 );
  //     edge->set_node(0) = _mesh->node_ptr(0);
  //     edge->set_node(1) = _mesh->node_ptr(1);

  //     // 2D elements will have subdomain id 0, this one will have 1
  //     edge->subdomain_id() = 1;
  //   }

  //   // libMesh will renumber, but we numbered according to its scheme
  //   // anyway. We do this because when we call uniformly_refine subsequently,
  //   // it's going use skip_renumber=false.
  //   _mesh->prepare_for_use(false /*skip_renumber*/);

  //   return _mesh;
  // }


// std::unique_ptr<MeshRefinement> build_mesh_refinement(MeshBase & mesh,
//                                                       FEMParameters & param)
// {
//   MeshRefinement * mesh_refinement = new MeshRefinement(mesh);
//   mesh_refinement->coarsen_by_parents() = true;
//   mesh_refinement->absolute_global_tolerance() = param.global_tolerance;
//   mesh_refinement->nelem_target()      = param.nelem_target;
//   mesh_refinement->refine_fraction()   = param.refine_fraction;
//   mesh_refinement->coarsen_fraction()  = param.coarsen_fraction;
//   mesh_refinement->coarsen_threshold() = param.coarsen_threshold;

//   return std::unique_ptr<MeshRefinement>(mesh_refinement);
// }


int main(int argc, char **argv)
{

  LibMeshInit init(argc, argv);

  SerialMesh mesh(init.comm());
  const unsigned int nelem = 16;
  MeshTools::Generation::build_square(mesh, nelem, nelem, 0, 1, 0, 1,
                                      QUAD4);

  mesh.prepare_for_use();

  Real horizon = 1. / double(nelem);
      std::cout << "\n horizon " << horizon << " \n " << std::endl;

  // for(auto qorder : range(3))
  // {
  //   std::cout << "\n qorder " << qorder << " \n " << std::endl;
  //   Eigen::MatrixXd qpw = qtrap(qorder, horizon);
  //   std::cout << qpw << std::endl;
  // }
  const unsigned int qorder = 1;
  const unsigned int qordernp1 = qorder * 2 + 1;
Eigen::MatrixXd qtrap = compute_qtrap(qorder, horizon);

    std::unique_ptr<PointLocatorBase> locator = mesh.sub_point_locator();

// Eigen::Map<Eigen::RowVectorXf> v1(qpw.data(), qpw.size()/2 ) ;
Eigen::RowVectorXd qpoints(  qordernp1 );
Eigen::MatrixXd qx(  qordernp1, qordernp1 );
qx << qtrap.row(1);
qx.square();

  QTrap

// Eigen::ColVectorXd qpoints(  qtrap.row(0).size() );
// qpoints << qtrap.row(1);

// Eigen::RowVectorXf::LinSpaced(-1,1,  qordernp1 );
// std::cout << "qpoints: \n ";
// std::cout  << qpoints << std::endl;
// std::cout  << qpoints.square().replicate<qordernp1,1>() << std::endl;
// std::cout  << Eigen::square(qpoints) << std::endl;

// std::cout  << qpoints.replicate<qordernp1,1>().pow(2) + qpoints.transpose().replicate<1,qordernp1>().pow(2)

    // const Elem* top_elem = (*locator)(top_point);

  for (unsigned int nid=1; nid<mesh.n_nodes(); ++nid)
    {
      
    // Point top_point(0.5, 0.5);
    const Elem* elem = (*locator)(mesh.point(nid));
    if(elem != 0 )
    1;

      // const Real dist_sq = (mesh.point(nid) - ).norm_sq();
      // if (dist_sq < nearest_dist_sq)
      //   {
      //     nearest_dist_sq = dist_sq;
      //     center_node = mesh.node_ptr(nid);
      //   }
    }


    // for(const auto &elem : mesh)
    // {
    //   for(const auto &node: elem.node_ref_range())
    //     node_ptr
    // }
}
/*   {
    auto print = [](const Point &p1, const Point &p2) {
      libMesh::out << "\n ";
      p1.print();
      libMesh::out << "\n ";
      p2.print();
    };

    // std::vector<Real> p0{0,1,2};
    Eigen::Vector3d p0{0, 1, 2};
    const Point &p1 = Point(0, 0, 1);
    // const Point &p1 = Point(p0);
    const Point &p2 = Point(1, 0, 1);
    auto pt2vec(p1);
    print(p1, p2);
  }

  {
    auto print = [](const unsigned int n) {
      std::vector<double> qw = get_trap_quadweights(n);
      // libMesh::out << "\n ";
      // (2*p1+p2).print();
      // libMesh::out << "\n ";
    };
  }
  auto comp = [](int x, int y) { return x < y; };
  const Point &pt = Point(0, 0, 1);
  Eigen::Vector3d p0 = pt2vec<Eigen::Vector3d>(pt);
  p0 + p0;
  std::vector<Real> p1 = pt2vec<std::vector<Real>>(pt);
  // std::find_if
  // std::fill(p1.begin, p1.end, boost::math::binomial_coefficient<double>(10, 2););

  // std::for_each(qpoint.begin(), qpoint.end(), print);
  // print_binomial_coefficients(8);
  std::vector<double> vec(binomial_coefficients<std::vector<double>>(8));
  print<std::vector<double>>(vec); */
/* 
OutputFunction

// Boundary conditions for the 3D test case
class OutputFunction : public FunctionBase<Number>
{
public:
  OutputFunction (unsigned int u_var, ValueFunctionPointer)
    : _u_var(u_var)
  { this->_initialized = true; }
//   { libmesh_not_implemented(); }

  virtual Number operator() (const Point & p, const Real = 0)
  {
      return exact_solution(p);
  }


  virtual void operator() (const Point & p,
                           const Real,
                           DenseVector<Number> & output)
  {
    libmesh_not_implemented();
  }

  virtual std::unique_ptr<FunctionBase<Number>> clone() const
  { return libmesh_make_unique<OutputFunction>(_u_var); }

private:
  const unsigned int _u_var;

};
 */


void write_libmesh_info(EquationSystems &equation_systems)
{

    const MeshBase &mesh = equation_systems.get_mesh();
    const unsigned int ndimensions = mesh.mesh_dimension();
    ExplicitSystem &system =
        equation_systems.get_system<ExplicitSystem>("system");
    const DofMap &dof_map = system.get_dof_map();
    auto n_dofs_total = dof_map.n_dofs();
    auto nelem = mesh.n_active_elem();
    // AnalyticFunction<Number> exact_solution_object(exact_solution);

    FEType fe_type = system.variable_type(0);

    // auto& exact = system.get_vector("exact");
    // auto& approx = system.get_vector("approx");
    // auto& error = system.get_vector("error");

    std::unique_ptr<NumericVector<Number>> centroid_values =
        system.solution->zero_clone();

    std::unique_ptr<FEBase> fe(FEBase::build(ndimensions, FEType(p_order, fe_family)));
    std::unique_ptr<QBase> qrule(QBase::build(QGAUSS, ndimensions, quad_order));
    fe->attach_quadrature_rule(qrule.get());

    const std::vector<Real> &JxW = fe->get_JxW();
    const std::vector<Point> &qpoint = fe->get_xyz();
    const std::vector<std::vector<Real>> &phi = fe->get_phi();
    std::cout << "\n qrule->quad_order() " << qrule->get_order();

    std::unique_ptr<FEBase> fe_face(FEBase::build(ndimensions, FEType(p_order, fe_family)));
    std::unique_ptr<QBase> qface(QBase::build(QTRAP, ndimensions - 1, quad_order));
    fe_face->attach_quadrature_rule(qface.get());

    const std::vector<Real> &JxW_face = fe_face->get_JxW();
    const std::vector<Point> &qpoint_face = fe_face->get_xyz();
    const std::vector<std::vector<Real>> &phi_face = fe_face->get_phi();
    std::cout << "\n qrule->quad_order() " << qface->get_order();

    std::unique_ptr<NumericVector<Number>> scalarfield_elem =
        NumericVector<Number>::build(mesh.comm());
    scalarfield_elem->init(nelem, false, SERIAL);

    std::unique_ptr<NumericVector<Number>> exact_scalarfield_elem = scalarfield_elem->zero_clone();

    std::unique_ptr<NumericVector<Number>> scalarfield_node = system.solution->zero_clone();

    // std::vector<Number> scalarfield_elem(mesh->n_elem());
    // std::vector<Number> exact_scalarfield_elem(mesh->n_elem());

    // auto elemval = scalarfield_elem.begin();
    // auto elemval_exact = exact_scalarfield_elem.begin();

    std::stringstream sstm;
    // sstm << "_" << nelem << horizon;
    std::string savename = sstm.str();

    std::ofstream outfile_elem;
    outfile_elem.open(savename + "elem_values.e", std::ios_base::app);

    std::ofstream outfile_qtrapside;
    outfile_qtrapside.open(savename + "qtrap_side.e", std::ios_base::app);

    std::ofstream outfile_qgausselem;
    outfile_qgausselem.open(savename + "qgauss_elem.e", std::ios_base::app);

    DenseMatrix<Number> Ke;
    DenseVector<Number> Fe;
    // DenseVector<Number> Fexact;
    std::vector<dof_id_type> dof_indices;
    std::vector<dof_id_type> one_dof_index(1);

    // for (auto elem : mesh.element_ptr_range())
    for (auto elem : mesh.element_ptr_range())
    {
        Real elemval_exact = 0;
        Real elemval = 0;

        dof_map.dof_indices(elem, dof_indices);
        const unsigned int n_dofs = dof_indices.size();

        Fe.zero();
        Fe.resize(n_dofs);

        libMesh::Patch patch(mesh.processor_id());
        patch.build_around_element(elem,
                                   std::pow(1 + 2 * nelem_div_horizon, ndimensions),
                                   &Patch::add_point_neighbors);

        const Point &point_elem = elem->centroid();

        std::ofstream outfile;
        outfile.open(savename + "patch.e", std::ios_base::app);

        for (const auto &neighbor : patch)
        {

            fe->reinit(neighbor);

            //qpoints
            for (auto qp : range(qrule->n_points()))
                for (auto i : range(3))
                    outfile << qpoint[qp](i) << " ";

            //JxW
            for (auto val : JxW)
                outfile << val << " ";

            //xi
            for (auto xprime : qpoint)
                outfile << (point_elem - xprime) << " ";

            //kernel
            for (auto xprime : qpoint)
                outfile << kernel(point_elem - xprime) << " ";
        }

        outfile << " \n ";
    }
}

MyUniqueOutput
integrate_exact(EquationSystems &equation_systems)
{
    const MeshBase &mesh = equation_systems.get_mesh();
    auto nelem = mesh.n_active_elem();
    const unsigned int ndimensions = mesh.mesh_dimension();

    ExplicitSystem &system = equation_systems.get_system<ExplicitSystem>("system");

    const DofMap &dof_map = system.get_dof_map();
    auto n_dofs_total = dof_map.n_dofs();

    FEType fe_type = system.variable_type(0);
    std::unique_ptr<NumericVector<Number>> centroid_values =
        system.solution->zero_clone();

    std::unique_ptr<NumericVector<Number>> scalarfield_elem =
        NumericVector<Number>::build(mesh.comm());
    scalarfield_elem->init(nelem, false, SERIAL);

    std::unique_ptr<NumericVector<Number>> exact_scalarfield_elem = scalarfield_elem->zero_clone();

    std::unique_ptr<NumericVector<Number>> scalarfield_node = system.solution->zero_clone();

    std::stringstream sstm;
    // sstm << "_" << nelem << horizon;
    std::string savename = sstm.str();

    std::ofstream outfile_elem;
    outfile_elem.open(savename + "elem_values.e", std::ios_base::app);

    // auto& exact = system.get_vector("exact");
    // auto& approx = system.get_vector("approx");
    // auto& error = system.get_vector("error");

    std::unique_ptr<FEBase> fe(FEBase::build(ndimensions, FEType(p_order, fe_family)));
    std::unique_ptr<QBase> qrule(QBase::build(quad_type, ndimensions, quad_order));
    fe->attach_quadrature_rule(qrule.get());

    const std::vector<Real> &JxW = fe->get_JxW();
    const std::vector<Point> &qpoint = fe->get_xyz();
    const std::vector<std::vector<Real>> &phi = fe->get_phi();
    std::cout << "\n qrule->quad_order() " << qrule->get_order();

    // std::unique_ptr<FEBase> fe_face(FEBase::build(ndimensions, FEType(p_order, fe_family)));
    // std::unique_ptr<QBase> qface(QBase::build(QTRAP, ndimensions - 1, quad_order));
    // fe_face->attach_quadrature_rule(qface.get());

    // const std::vector<Real> &JxW_face = fe_face->get_JxW();
    // const std::vector<Point> &qpoint_face = fe_face->get_xyz();
    // const std::vector<std::vector<Real>> &phi_face = fe_face->get_phi();
    // std::cout << "\n qrule->quad_order() " << qface->get_order();

    DenseMatrix<Number> Ke;
    DenseVector<Number> Fe;
    // DenseVector<Number> Fexact;
    std::vector<dof_id_type> dof_indices;
    std::vector<dof_id_type> dof_indices_neighbor;
    std::vector<dof_id_type> one_dof_index(1);

    // for (auto elem : mesh.element_ptr_range())
    for (auto elem : mesh.element_ptr_range())
    {
        Real elemval_exact = 0;
        Real elemval = 0;

        dof_map.dof_indices(elem, dof_indices);
        const unsigned int n_dofs = dof_indices.size();

        Fe.zero();
        Fe.resize(n_dofs);

        libMesh::Patch patch(mesh.processor_id());
        patch.build_around_element(elem,
                                   std::pow(1 + 2 * nelem_div_horizon, ndimensions),
                                   &Patch::add_point_neighbors);

        const Point &point_elem = elem->centroid();
        Real JxWkernelsum = 0;
        for (const auto &neighbor : patch)
        {
            
            // dof_map.dof_indices(elem, dof_indices_neighbor);

            fe->reinit(neighbor);

            for (auto qp : range(qrule->n_points()))
            {
                const Point &xi((point_elem - qpoint[qp]));

                Real kernelval = ( kernel(xi * horizon ) )  / (horizon * horizon );
                // kernelval += 1;
                JxWkernelsum += JxW[qp] * kernelval;

                elemval += JxW[qp] * kernelval * exact_solution(qpoint[qp], equation_systems.parameters, std::string(), std::string());

            }
        }

        fe->reinit(elem);
        for (auto qp : range(qrule->n_points()))
            for (auto i : range(n_dofs))
                Fe(i) += JxW[qp] * phi[i][qp] * elemval;

        // elemval /= JxWkernelsum;
        // Fe.scale( 1.0 / JxWkernelsum);

        elemval_exact += exact_solution(point_elem, equation_systems.parameters, std::string(), std::string());

        for (auto i : range(3))
            outfile_elem << point_elem(i) << " ";
        outfile_elem << elemval << " " << elemval_exact;
        outfile_elem << " \n ";

        dof_map.constrain_element_vector(Fe, dof_indices);

        scalarfield_node->add_vector(Fe, dof_indices);
    }

    {
        std::ofstream outfile;
        outfile.open("scalarfield_node.e", std::ios_base::app);
        scalarfield_node->print(outfile);
    }

    return scalarfield_node;
}




libMesh::Patch
build_neighborhood(const MeshBase &mesh,
                   const Elem &base_elem,
                   const Point &X,
                   const unsigned int target_patch_size,
                   const Real eps
                   //  std::unique_ptr<PointLocatorTree> point_locator
)
{
  // PointLocatorBase*& point_locator
  // std::unique_ptr<PointLocatorBase> point_locator = mesh.sub_point_locator();
  // PointLocatorTree &point_locator = mesh.sub_point_locator(); //sub_point_locator();
  /*   if (!point_locator->initialized())
  {
    libMesh::out << " initialize point locator...";
    libMesh::out.flush();
    point_locator->init();
  }

  if (point_locator == nullptr)
    try
    {
      mesh.sub_point_locator();
    }
    catch (const std::exception &)
    {
      point_locator = new PointLocatorTree(mesh);
    }

  if (!mesh.is_serial()) 
    point_locator->enable_out_of_mesh_mode();
*/
  libMesh::Patch patch_elems(mesh.processor_id());
  // unsigned int target_patch_size = 9;
  int nlocalelem = mesh.n_local_elem();
  patch_elems.build_around_element(&base_elem, target_patch_size,
                                   &Patch::add_point_neighbors);
  int patchsize = patch_elems.size();

  // if(elem==nullptr)
  //   *base_elem = (*point_locator)(X);
  // else if(X==std::nullptr_t)
  //   &X = base_elem->centroid();

  // std::set<const Elem *> patch_elems;
  // patch_elems->insert(base_elem);
  // std::set<const Elem *> visited_elems = patch_elems;

  /*   
  std::set<const Elem *> frontier_elems = patch_elems;
  while (!frontier_elems.empty())
  {
    std::set<const Elem *> new_frontier;
    for (auto e : frontier_elems)
    {
      for (auto neighbor : e->neighbor_ptr_range())
      {
        if (neighbor != nullptr && !patch_elems.count(neighbor))
        {
          for (int k : neighbor->node_index_range())
          {

            if (signed_distance_fcn(X - neighbor->point(k), eps) > 0.0)
            {
              patch_elems.insert(neighbor);
              new_frontier.insert(neighbor);
              break;
            }
          }
          // visited_elems.insert(neighbor);
        }
      }
    }
    frontier_elems = new_frontier;
  } */

  return patch_elems;
}
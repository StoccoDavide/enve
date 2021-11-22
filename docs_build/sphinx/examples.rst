How to use ENVE
===============

Load the mesh
-------------

With ENVE the ground mesh can be loaded from a Road Data Format (``*.rdf``) file or from a Wavefront OBJ (``*.obj``)
file. An example could be one of the following:

C++

  .. code-block:: cpp
  
      enve::ground::mesh meshRDF(
        std::string "./sample.rdf" // Path to the *.rdf file
      );

  .. code-block:: cpp
  
      enve::ground::mesh meshOBJ(
        std::string "./sample.obj",  // Path to the *.obj file
        real        lambda           // Friction coefficient scaling factor
      );

MATLAB

  .. code-block:: matlab
  
      meshRDF = enve_mesh( ...
        './sample.rdf' ... % Path to the *.rdf file
      );

  .. code-block:: matlab
  
      meshOBJ = enve_mesh( ...
        './sample.obj', ... % Path to the *.obj file
        lambda          ... % Friction coefficient scaling factor
      );

Build a flat ground
-------------------

If no mesh can be provided one could also build a flat terrain where to move the wheel.

C++

  .. code-block:: cpp
  
      enve::ground::flat planeGround(
      flat(
        acme::real origin_x, // X-axis value of ground plane origin point
        acme::real origin_y, // Y-axis value of ground plane origin point
        acme::real origin_z, // Z-axis value of ground plane origin point
        acme::real normal_x, // X-axis value of ground plane normal vector
        acme::real normal_y, // Y-axis value of ground plane normal vector
        acme::real normal_z, // Z-axis value of ground plane normal vector
        acme::real friction  // Friction coefficient scaling factor
      );

  .. code-block:: cpp

      enve::ground::flat planeGround(
        acme::point origin,  // Plane origin point
        acme::vec3  normal,  // Plane normal vector
        acme::real  friction // Friction coefficient scaling factor
      );

  .. code-block:: cpp

      enve::ground::flat planeGround(
        acme::plane plane_in, // ACME plane object
        acme::real  friction  // Friction coefficient scaling factor
      );


MATLAB

  .. code-block:: matlab
  
      planeGround = enve_flat( ...
        acme::real origin_x, ... % X-axis value of ground plane origin point
        acme::real origin_y, ... % Y-axis value of ground plane origin point
        acme::real origin_z, ... % Z-axis value of ground plane origin point
        acme::real normal_x, ... % X-axis value of ground plane normal vector
        acme::real normal_y, ... % Y-axis value of ground plane normal vector
        acme::real normal_z, ... % Z-axis value of ground plane normal vector
        acme::real friction  ... % Friction coefficient scaling factor
      );

  .. code-block:: matlab

      planeGround = enve_flat( ...
        origin,  ... % Plane origin point
        normal,  ... % Plane normal vector
        friction ... % Friction coefficient scaling factor
      );
    

Build the wheel shell
---------------------

The wheel undeformable shell can be initialized in three different ways.

1. Hyperelliptical section surface of revolution:

  C++

  .. code-block:: cpp

    enve::shell(
      size_t     size, // Ribs number
      acme::real r_x,  // Shell radius on x axis (m)
      acme::real m_x,  // Shell curve degree for x axis
      acme::real r_y,  // Shell radius on y axis (m)
      acme::real m_y,  // Shell curve degree for y axis
      acme::real l_y   // Shell half width on y axis (m)
    );

    MATLAB

  .. code-block:: matlab

    shell = enve_shell( ...
      size, ... % Ribs number
      r_x,  ... % Shell radius on x axis (m)
      m_x,  ... % Shell curve degree for x axis
      r_y,  ... % Shell radius on y axis (m)
      m_y,  ... % Shell curve degree for y axis
      l_y   ... % Shell half width on y axis (m)
    );
    

2. Polynomial interpolation of section raw data:

  C++

  .. code-block:: cpp

    enve::shell(
      size_t     size,  // Ribs number
      acme::vecN dataR, // Vector of radius data (m)
      acme::vecN dataY, // Vector of y data (m)
      size_t     order  // Polynom order
    );

  MATLAB

  .. code-block:: matlab
    
    shell = enve_shell( ...
      size,  ... % Ribs number
      dataR, ... % Vector of radius data (m)
      dataY, ... % Vector of y data (m)
      order  ... % Polynom order
    );


3. Precise (dense) section description:

  C++

  .. code-block:: cpp

    enve::shell(
      size_t     size,  // Ribs number
      acme::vecN dataR, // Vector of radius data (m)
      acme::vecN dataY  // Vector of y data (m)
    );


  MATLAB
  
  .. code-block:: matlab

    shell = enve_shell( ...
      size,  ... % Ribs number
      dataR, ... % Vector of radius data (m)
      dataY  ... % Vector of y data (m)
    );


Evaluate the contact
--------------------

Once both the ground and the wheel rigid shell are build we can move to the contact evaluation:

C++

    .. code-block:: cpp

        bool out = shell.setup(
          enve::ground::mesh ground,    // ENVE mesh object (ground)
          acme::affine       matrix,    // 4x4 affine transformation matrix
          size_t             threshold, // Evaluations threshold number
          std::string const  method     // Method name (choose from: "triangle" or "line")
        );

MATLAB

    .. code-block:: matlab

        out = shell.setup( ...
          ground,    ... % ENVE mesh object (ground)
          matrix,    ... % 4x4 affine transformation matrix
          threshold, ... % Evaluations threshold number
          method     ... % Method name (choose from: "triangle" or "line")
        );

Otherwise one can alse perform the contact evaluation with a flat ground:

C++

    .. code-block:: cpp

        bool out = shell.setup(
          enve::ground::flat ground, // ENVE flat object (ground)
          acme::affine       affine  // Shell 4x4 total transformation matrix
        );

MATLAB

    .. code-block:: matlab

        out = shell.setup( ...
          ground, ... % ENVE flat object (ground)
          affine  ... % Shell 4x4 total transformation matrix
        );

Extract Data
------------

Once the contact has been evaluated one can retrive the average contact parameters as: 

C++

    .. code-block:: cpp

        // Variables initialization (real numbers):
        acme::point contact_point_rib;      // (m)
        acme::point contact_point_mesh;     // (m)
        acme::real  contact_depth_rib;      // (m)
        acme::real  contact_depth_rib_dot;  // (m/s)
        acme::real  contact_depth_rib_old;  // (m)
        acme::real  contact_depth_mesh;     // (m)
        acme::real  contact_depth_mesh_dot; // (m/s)
        acme::real  contact_depth_mesh_old; // (m)
        acme::vec3  contact_normal;         // (-)
        acme::real  contact_friction;       // (-)
        acme::real  relative_camber;        // (rad)
        acme::real  time_step;              // (s)

        // Data extraction (real numbers):
        shell.contactPointRib(contact_point_rib);
        shell.contactNormal(contact_normal);
        shell.contactFriction(contact_friction);
        shell.contactDepthRib(contact_depth_rib,
                              contact_depth_rib_dot,
                              contact_depth_rib_old,
                              time_step);
        shell.contactDepthMesh(contact_depth_mesh,
                               contact_depth_mesh_dot,
                               contact_depth_mesh_old,
                               time_step);
        shell.relativeCamber(relative_camber);

MATLAB

    .. code-block:: matlab

        % Data extraction (real numbers):
        shell.contactPointRibAvg(contact_point_rib);
        shell.contactNormalAvg(contact_normal);
        shell.contactFrictionAvg(contact_friction);
        shell.contactDepthRibAvg(contact_depth_rib,     ...
                                 contact_depth_rib_dot, ...
                                 contact_depth_rib_old, ...
                                 time_step);
        shell.contactDepthMeshAvg(contact_depth_mesh,     ...
                                  contact_depth_mesh_dot, ...
                                  contact_depth_mesh_old, ...
                                  time_step);
        shell.relativeCamber(relative_camber);


Or one can retrive the contact parameters rib by rib as: 

C++

    .. code-block:: cpp

        // Variables initialization (vectors):
        acme::size_t              size = tire_shell.size();     // (-)
        acme::std::vector<point>  contact_point_rib(size);      // (m)
        acme::std::vector<point>  contact_point_mesh(size);     // (m)
        acme::vecN                contact_depth_rib(size);      // (m)
        acme::vecN                contact_depth_rib_dot(size);  // (m/s)
        acme::vecN                contact_depth_rib_old(size);  // (m)
        acme::vecN                contact_depth_mesh(size);     // (m)
        acme::vecN                contact_depth_mesh_dot(size); // (m/s)
        acme::vecN                contact_depth_mesh_old(size); // (m)
        acme::std::vector<vec3>   contact_normal(size);         // (-)
        acme::vecN                contact_friction(size);       // (-)
        acme::vecN                relative_camber(size);        // (rad)
        acme::real                time_step;                    // (s)

        // Data extraction (vectors):
        shell.contactPointRib(contact_point_rib);
        shell.contactNormal(contact_normal);
        shell.contactFriction(contact_friction);
        shell.contactDepthRib(contact_depth_rib,
                              contact_depth_rib_dot,
                              contact_depth_rib_old,
                              time_step);
        shell.contactDepthMesh(contact_depth_mesh,
                               contact_depth_mesh_dot,
                               contact_depth_mesh_old,
                               time_step);
        shell.relativeCamber(relative_camber);

MATLAB

    .. code-block:: matlab

        % Data extraction (real numbers):
        contact_point_rib = shell.contactPointRib(i);
        contact_normal    = shell.contactNormal(i);
        contact_friction  = shell.contactFriction(i);
        contact_depth_rib = shell.contactDepthRib( ...
                              contact_depth_rib_dot, ...
                              contact_depth_rib_old, ...
                              time_step,             ...
                              i);
        contact_depth_mesh = shell.contactDepthMesh( ...
                               contact_depth_mesh_dot, ...
                               contact_depth_mesh_old, ...
                               time_step,              ...
                               i);
        relative_camber = shell.relativeCamber();

where ``ì`` is the i-th rib index.

For more advanced functions read the C++/MATLAB API documentation.


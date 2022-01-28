How to use ENVE
===============

Load the mesh
-------------

With ENVE the ground mesh can be loaded from a Road Data Format (``*.rdf``) file or from a Wavefront OBJ (``*.obj``)
file. An example could be one of the following:

C++

  .. code-block:: cpp
  
      enve::ground::mesh mesh_rdf(
        std::string "./sample.rdf" // Path to the *.rdf file
      );

  .. code-block:: cpp
  
      enve::ground::mesh mesh_obj(
        std::string "./sample.obj", // Path to the *.obj file
        acme::real  lambda          // Friction coefficient scaling factor
      );

MATLAB

  .. code-block:: matlab
  
      mesh_rdf = enve_mesh( ...
        './sample.rdf' ... % Path to the *.rdf file
      );

  .. code-block:: matlab
  
      mesh_obj = enve_mesh( ...
        './sample.obj', ... % Path to the *.obj file
        lambda          ... % Friction coefficient scaling factor
      );

Build a flat ground
-------------------

If no mesh can be provided one could also build a flat terrain where to move the tire.

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
    

Build the tire shell
--------------------

The undeformable shell is decribed as a hyperelliptical section surface of revolution. It can be initialized in these way.

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
    

Evaluate the contact
--------------------

Once both the ground and the shell are build we can move to the contact evaluation:

C++

    .. code-block:: cpp

        bool out = shell.setup(
          enve::ground::mesh ground, // ENVE mesh object (ground)
          acme::affine       matrix, // 4x4 affine transformation matrix
          std::string const  method  // Method name (choose from: "geometric" or "sampling")
        );

MATLAB

    .. code-block:: matlab

        out = shell.setup( ...
          ground,    ... % ENVE mesh object (ground)
          matrix,    ... % 4x4 affine transformation matrix
          method     ... % Method name (choose from: "geometric" or "sampling")
        );

Otherwise one can alse perform the contact evaluation with a flat ground:

C++

    .. code-block:: cpp

        bool out = shell.setup(
          enve::ground::flat ground, // ENVE flat object (ground)
          acme::affine       affine, // Shell 4x4 total transformation matrix
          std::string const  method  // Method name (choose from: "geometric" or "sampling")
        );

MATLAB

    .. code-block:: matlab

        out = shell.setup( ...
          ground, ... % ENVE flat object (ground)
          affine, ... % Shell 4x4 total transformation matrix
          method  ... % Method name (choose from: "geometric" or "sampling")
        );

Extract Data
------------

Once the contact has been evaluated one can retrive the (average) contact parameters as: 

C++

    .. code-block:: cpp

        // Variables initialization
        acme::point contact_point_avg;    // (m)
        acme::real  contact_depth_avg;    // (m)
        acme::vec3  contact_normal_avg;   // (-)
        acme::real  contact_friction_avg; // (-)
        acme::real  contact_area_avg;     // (m^2)
        acme::real  contact_volume_avg;   // (m^3)
        acme::vec3  relative_angles_avg;  // (rad)

        // Data extraction
        shell.contactPoint(contact_point_avg);
        shell.contactDepth(contact_depth_avg);
        shell.contactNormal(contact_normal_avg);
        shell.contactFriction(contact_friction_avg);
        shell.contactArea(contact_area_avg);
        shell.contactVolume(contact_volume_avg);
        shell.relativeAngles(relative_angles_avg);

MATLAB

    .. code-block:: matlab

        % Data extraction
        contact_point_avg    = shell.contactPointAvg();
        contact_depth_avg    = shell.contactDepthAvg();
        contact_normal_avg   = shell.contactNormalAvg();
        contact_friction_avg = shell.contactFrictionAvg();
        contact_area_avg     = shell.contactAreaAvg();
        contact_volume_avg   = shell.contactVolumeAvg();
        relative_angles_avg  = shell.relativeAnglesAvg();


Or one can retrive the contact parameters for a specific rib as: 

C++

    .. code-block:: cpp

        // Variables initialization
        acme::point contact_point_rib(i);    // (m)
        acme::real  contact_depth_rib(i);    // (m)
        acme::vec3  contact_normal_rib(i);   // (-)
        acme::real  contact_friction_rib(i); // (-)
        acme::real  contact_area_rib(i);     // (m^2)
        acme::real  contact_volume_rib(i);   // (m^3)
        acme::vec3  relative_angles_rib(i);  // (rad)

        // Data extraction
        shell.contactPointRib(contact_point_rib);
        shell.contactDepth(contact_depth_rib);
        shell.contactNormal(contact_normal_rib);
        shell.contactFriction(contact_friction_rib);
        shell.contactArea(contact_area_rib);
        shell.contactVolume(contact_volume_rib);
        shell.relativeAngles(relative_angles_rib);

MATLAB

    .. code-block:: matlab

        % Data extraction
        contact_point_rib    = shell.contactPointRib(i);
        contact_normal_rib   = shell.contactNormalRib(i);
        contact_friction_rib = shell.contactFrictionRib(i);
        contact_depth_rib    = shell.contactDepthRib(i);
        contact_area_rib     = shell.contactAreaRib(i);
        contact_volume_rib   = shell.contactVolumeRib(i);
        relative_angles_rib  = shell.relativeAnglesRib(i);

where ``i`` is the i-th rib index.


Or one can retrive the contact parameters rib by rib as: 

C++

    .. code-block:: cpp

        // Variables initialization
        acme::size_t                    size = tire_shell.size(); // (-)
        acme::std::vector<acme::point>  contact_point_vec(size);      // (m)
        acme::std::vector<acme::real>   contact_depth_vec(size);      // (m)
        acme::std::vector<acme::vec3>   contact_normal_vec(size);     // (-)
        acme::std::vector<acme::real>   contact_friction_vec(size);   // (-)
        acme::std::vector<acme::real>   contact_area_vec(size);       // (m^2)
        acme::std::vector<acme::real>   contact_volume_vec(size);     // (m^3)
        acme::std::vector<acme::vec3>   relative_angles_vec(size);    // (rad)

        // Data extraction
        shell.contactPointRib(contact_point_vec);
        shell.contactDepth(contact_depth_vec);
        shell.contactNormal(contact_normal_vec);
        shell.contactFriction(contact_friction_vec);
        shell.contactArea(contact_area_vec);
        shell.contactVolume(contact_volume_vec);
        shell.relativeAngles(relative_angles_vec);

MATLAB

    .. code-block:: matlab

        % Data extraction
        contact_point_vec    = shell.contactPointVec();
        contact_normal_vec   = shell.contactNormalVec();
        contact_friction_vec = shell.contactFrictionVec();
        contact_depth_vec    = shell.contactDepthVec();
        contact_area_vec     = shell.contactAreaVec();
        contact_volume_vec   = shell.contactVolumeVec();
        relative_angles_vec  = shell.relativeAnglesVec();



For more advanced functions please read the C++/MATLAB API documentation.


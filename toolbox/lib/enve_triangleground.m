% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
%                                                                     %
% This file is part of the ENVE project.                              %
%                                                                     %
% Copyright (c) 2020, Davide Stocco, Matteo Larcher and Enrico        %
% Bertolazzi.                                                         %
%                                                                     %
% The ENVE project and its components are supplied under the terms of %
% the open source BSD 3-Clause License. The contents of the ENVE      %
% project and its components may not be copied or disclosed except in %
% accordance with the terms of the BSD 3-Clause License.              %
%                                                                     %
%    Davide Stocco                                                    %
%    Department of Industrial Engineering                             %
%    University of Trento                                             %
%    e-mail: davide.stocco@unitn.it                                   %
%                                                                     %
%    Enrico Bertolazzi                                                %
%    Department of Industrial Engineering                             %
%    University of Trento                                             %
%    e-mail: enrico.bertolazzi@unitn.it                               %
%                                                                     %
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %

classdef enve_triangleground < acme_entity
  %>
  %> Class container for ENVE triangleground object
  %>
  methods
    function this = enve_triangleground( varargin )
      %> Create a new C++ pointer to ENVE triangleground object instance
      this.objectHandle = mex_triangleground( 'new', varargin{:} );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Create C++ pointer to ENVE triangleground object instance
    function delete( this )
      mex_triangleground( 'delete', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get ID
    function out = getID( this )
      out = mex_triangleground( 'getID', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get friction coefficent scaling factor
    function out = getFriction( this )
      out = mex_triangleground( 'getFriction', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get triangle vertex 1 as ACME point object
    function out = getVertex1( this )
      out = acme_point();
      out.copyByHandle( mex_triangleground( 'getVertex1', this.objectHandle ) );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get triangle vertex 2 as ACME point object
    function out = getVertex2( this )
      out = acme_point();
      out.copyByHandle( mex_triangleground( 'getVertex2', this.objectHandle ) );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get triangle vertex 3 as ACME point object
    function out = getVertex3( this )
      out = acme_point();
      out.copyByHandle( mex_triangleground( 'getVertex3', this.objectHandle ) );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Set triangle vertex 1 with an ACME point object
    function setVertex1( this, other_obj )
      mex_triangleground( 'setVertex1', this.objectHandle, other_obj.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Set triangle vertex 2 with an ACME point object
    function setVertex2( this, other_obj )
      mex_triangleground( 'setVertex2', this.objectHandle, other_obj.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Set triangle vertex 3 with an ACME point object
    function setVertex3( this, other_obj )
      mex_triangleground( 'setVertex3', this.objectHandle, other_obj.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Copy triangleground object from another triangleground
    function copy( this, other_obj )
      if (other_obj.type() == "triangleground")
        mex_triangleground( 'copy', this.objectHandle, other_obj.objectHandle );
      else
        error('mex_triangleground::copy(): other_obj must be an ENVE triangleground object type.');
      end
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Copy triangleground object from another triangleground shape
    function copyByHandle( this, handle )
      mex_triangleground( 'copy', this.objectHandle, handle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get normal
    function out = normal( this )
      out = mex_triangleground( 'normal', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Display object data
    function disp( this )
      disp([[this.getID(); this.getFriction(); NaN], ...
             this.getVertex1().get(), this.getVertex2().get(),  ...
             this.getVertex3().get() ...
           ]);
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Set friction coefficent scaling factor
    function out = toTriangle( this )
      out = acme_triangle( ...
          this.getVertex1().get(), ...
          this.getVertex2().get(), ...
          this.getVertex3().get() ...
        );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot triangle object
    function plot( this, figure_name, color )
      figure_name; %#ok<VUNUS>
      hold on;
      Vertex1 = this.getVertex1().get();
      Vertex2 = this.getVertex2().get();
      Vertex3 = this.getVertex3().get();
      X = [Vertex1(1), Vertex2(1), Vertex3(1)];
      Y = [Vertex1(2), Vertex2(2), Vertex3(2)];
      Z = [Vertex1(3), Vertex2(3), Vertex3(3)];
      patch(X, Y, Z, color, 'FaceAlpha', 1.0);
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get object type as string
    function out = type( ~ )
      out = 'triangleground';
    end
  end
end

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

classdef enve_mesh < handle
  %>
  %> Class container for ENVE mesh object
  %>
  properties (Hidden = true) %(SetAccess = {?enve_shell}, Hidden = true)
    objectHandle; %> Handle to the underlying C++ class instance
  end
  %
  % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  %
  methods
    %
    %> Create a new C++ pointer to ENVE mesh object instance
    function this = enve_mesh( varargin )
      extension   = varargin{1}(end-3:end);
      file_bool   = isfile(varargin{1});

      % Check for file
      if(~file_bool)
        error("enve_mesh: no *.rdf or *.obj file found!")
      end

      % Sanity check for *.rdf and *.obj files
      if (strcmp(extension, '.rdf'))
        if( ~(nargin == 1) && ...
            ~(nargin == 2 && ismatrix(varargin{2})))
          error("enve_mesh: invalid inputs for *.rdf file!")
        end
      elseif (strcmp(extension, '.obj'))
        if( ~(nargin == 1) && ...
            ~(nargin == 2 && isscalar(varargin{2})) && ...
            ~(nargin == 3 && isscalar(varargin{2}) && length(varargin{3}) == 4))
          error("enve_mesh: invalid inputs for *.obj file!")
        end
      else
        error("enve_mesh: not a *.rdf or *.obj file!")
      end
        
      this.objectHandle = mex_mesh( 'new', varargin{:} );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Create C++ pointer to ENVE meh object instance
    function delete( this )
      mex_mesh( 'delete', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get mesh i-th triangle as ENVE triangle object
    function out = getTriangleground( this, i )
      out = enve_triangleground();
      out.copyByHandle( mex_mesh( 'getTriangleground', this.objectHandle, i ) );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get mesh i-th triangle vertices as a matrix
    function out = getTrianglegroundVertices( this, i )
      out = mex_mesh( 'getTrianglegroundVertices', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get mesh i-th triangle as ACME triangle object
    function out = getTriangle( this, i )
      out = this.getTriangleground(i).toTriangle();
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get mesh i-th triangle vertices as a matrix
    function out = getTriangleVertices( this, i )
      out = mex_mesh( 'getTrianglegroundVertices', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get mesh size
    function out = size( this )
      out = mex_mesh( 'size', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Copy mesh object from another mesh
    function copy( this, other_obj )
      if (other_obj.type() == "mesh")
        mex_mesh( 'copy', this.objectHandle, other_obj.objectHandle );
      else
        error('mex_mesh::copy(): other_obj must be an ENVE mesh object type.');
      end
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Copy mesh object from another mesh shape
    function copyByHandle( this, handle )
      mex_mesh( 'copy', this.objectHandle, handle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Print the number of triangles in the mesh
    function disp( this )
      disp( strcat(num2str(this.size()), ' triangles'))
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot ENVE shape object
    function plot( this, figure_name, color )
      X = zeros(3, this.size());
      Y = zeros(3, this.size());
      Z = zeros(3, this.size());
      for i = 1:this.size()
         V = this.getTrianglegroundVertices(i);
         X(:,i) = V(1,:)';
         Y(:,i) = V(2,:)';
         Z(:,i) = V(3,:)';
      end
      figure_name; %#ok<VUNUS>
      hold on;
      patch(X, Y, Z, color, 'FaceAlpha', 1.0);
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get object type as string
    function out = type( ~ )
      out = 'mesh';
    end
  end
end

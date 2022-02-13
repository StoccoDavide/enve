% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
%                                                                     %
% The ENVE project                                                    %
%                                                                     %
% Copyright (c) 2020-2021, Davide Stocco and Enrico Bertolazzi.       %
%                                                                     %
% The ENVE project and its components are supplied under the terms of %
% the open source BSD 2-Clause License. The contents of the ENVE      %
% project and its components may not be copied or disclosed except in %
% accordance with the terms of the BSD 2-Clause License.              %
%                                                                     %
% URL: https://opensource.org/licenses/BSD-2-Clause                   %
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
  % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  %
  methods
    %> Create a new C++ pointer to ENVE mesh object instance
    function this = enve_mesh( varargin )
      extension = varargin{1}(end-3:end);
      file_bool = isfile(varargin{1});
      if( (file_bool && strcmp(extension, '.rdf') && nargin == 1) || ...
          (file_bool && strcmp(extension, '.obj') && nargin == 2) )
        this.objectHandle = mex_mesh( 'new', varargin{:} );
      else
        error("enve_mesh: invalid input!")
      end 
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Create C++ pointer to ENVE meh object instance
    function delete( this, ~ )
      mex_mesh( 'delete', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get mesh i-th triangle as ACME triangle object
    function out = getTriangleground( this, i, ~ )
      out = enve_triangleground();
      out.copyByHandle( mex_mesh( 'getTriangleground', this.objectHandle, i ) );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get mesh i-th triangle as ACME triangle object
    function out = getTriangle( this, i, ~ )
      out = this.getTriangleground(i).toTriangle();
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get mesh size
    function out = size( this, ~ )
      out = mex_mesh( 'size', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Copy mesh object from another mesh
    function copy( this, other_obj, ~ )
      if (other_obj.type() == "mesh")
        mex_mesh( 'copy', this.objectHandle, other_obj.objectHandle );
      else
        error('mex_mesh::copy(): other_obj must be an ENVE mesh object type.');
      end
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Copy mesh object from another mesh shape
    function copyByHandle( this, handle, ~ )
      mex_mesh( 'copy', this.objectHandle, handle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    function disp( this, ~ )
      disp( strcat(num2str(this.size()), ' triangles'))
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot ENVE shape object
    function plot( this, figure_name, color, ~ )
      figure_name;
      hold on;
      for i = 1:this.size()
         this.getTriangleground(i).plot( figure_name, color )
      end
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get object type as string
    function out = type( this, ~ )
      out = 'mesh';
    end
  end
end

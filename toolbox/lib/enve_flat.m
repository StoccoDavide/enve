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

classdef enve_flat < handle
  %>
  %> Class container for ENVE flat object
  %>
  properties (SetAccess = {?enve_shell}, Hidden = true)
    objectHandle; %> Handle to the underlying C++ class instance
  end
  %
  % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  %
  %> Create a new C++ pointer to ENVE flat object instance
  methods
    function this = enve_flat( varargin )
      this.objectHandle = mex_flat( 'new', varargin{:} );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Create C++ pointer to ENVE meh object instance
    function delete( this )
      mex_flat( 'delete', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get plane origin as ACME point object
    function out = getOrigin( this )
      out = acme_point();
      out.copyByHandle( mex_flat( 'getOrigin', this.objectHandle ) );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Set plane origin
    function setOrigin( this, other_obj )
      mex_flat( 'setOrigin', this.objectHandle, other_obj );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get plane normal
    function out = getNormal( this )
      out = mex_flat( 'getNormal', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Set plane normal
    function setNormal( this, other_obj )
      mex_flat( 'setNormal', this.objectHandle, other_obj );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get plane
    function out = getPlane( this )
      out = acme_plane();
      out.copyByHandle( mex_flat( 'getPlane', this.objectHandle ) );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Set plane
    function setPlane( this, other_obj )
      this.setOrigin( other_obj.getOrigin().get() )
      this.setNormal( other_obj.getNormal() )
      % NOT WORKING ON MEX:
      % mex_flat( 'setPlane', this.objectHandle, other_obj.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get plane friction
    function out = getFriction( this )
      out = mex_flat( 'getFriction', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Set plane friction
    function setFriction( this, friction )
      mex_flat( 'setFriction', this.objectHandle, friction );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Check if plane is degenerated
    function out = isDegenerated( this )
      out = mex_flat( 'isDegenerated', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Check if planes are approximatively equal
    function out = isApprox( this, other_obj )
      if (other_obj.type() == "flat") 
        out = mex_flat( 'isApprox', this.objectHandle, other_obj.objectHandle );
      else
         error('mex_flat::isApprox(): other_obj must be an ENVE flat object type.');
      end
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Copy mesh object from another mesh
    function copy( this, other_obj )
      if (other_obj.type() == "mesh")
        mex_flat( 'copy', this.objectHandle, other_obj.objectHandle );
      else
        error('mex_flat::copy(): other_obj must be an ENVE mesh object type.');
      end
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Copy mesh object from another mesh shape
    function copyByHandle( this, handle )
      mex_flat( 'copy', this.objectHandle, handle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Diplay object data
    function disp( this )
      disp( [[this.getFriction(), NaN, NaN]', ...
             this.getOrigin().get(), ...
             this.getNormal()] )
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot ENVE shape object
    function plot( this, figure_name, color )
      figure_name;
      hold on;
      this.getPlane().plot( figure_name, color );
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get object type as string
    function out = type( this )
      out = 'flat';
    end
  end
end

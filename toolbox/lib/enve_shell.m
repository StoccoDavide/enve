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

classdef enve_shell < handle
  %>
  %> Class container for ENVE shell object
  %>
   properties (SetAccess = protected, Hidden = true)
     objectHandle; %> Handle to the underlying C++ class instance
   end
  %
  % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  %
  methods
    %> Create a new C++ pointer to ENVE shell object instance
    function this = enve_shell( varargin )
      this.objectHandle = mex_shell( 'new', varargin{:} );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Create C++ pointer to ENVE shell object instance
    function delete( this )
      mex_shell( 'delete', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Reset shell shape with N ribs
    function reset( this, n )
      mex_shell( 'reset', this.objectHandle, n );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell ribs number
    function out = size( this )
      out = mex_shell( 'size', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell surface maximum radius (m)
    function out = surfaceMaxRadius( this )
      out = mex_shell( 'surfaceMaxRadius', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell surface maximum width on y axis (m)
    function out = surfaceMaxWidth( this )
      out = mex_shell( 'surfaceMaxWidth', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell surface minimum width (m)
    function out = surfaceWidthLowerBound( this )
      out = mex_shell( 'surfaceWidthLowerBound', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell surface maximum width (m)
    function out = surfaceWidthUpperBound( this )
      out = mex_shell( 'surfaceWidthUpperBound', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell surface width (m)
    function out = surfaceWidth( this )
      out = mex_shell( 'surfaceWidth', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell surface maximum width on reference (m)
    function out = surfaceWidthBound( this, y )
      out = mex_shell( 'surfaceWidthBound', this.objectHandle, y );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell surface of revolution rib radius at y axis coordinate (m)
    function out = surfaceRadius( this, y )
      out = mex_shell( 'surfaceRadius', this.objectHandle, y );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell surface of revolution rib first derivative with respect to y coordinate
    function out = surfaceDerivative( this, y )
      out = mex_shell( 'surfaceDerivative', this.objectHandle, y );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell surface of revolution rib angle with respect to y axis (rad)
    function out = surfaceAngle( this, y )
      out = mex_shell( 'surfaceAngle', this.objectHandle, y );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get i-th rib radius (m)
    function out = ribRadius( this, i )
      out = mex_shell( 'ribRadius', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get i-th rib center as an ACME point
    function out = ribCenter( this, i )
      out = acme_point();
      out.copyByHandle( mex_shell( 'ribCenter', this.objectHandle, i ) );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get i-th rib width
    function out = ribWidth( this, i )
      out = mex_shell( 'ribWidth', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell translation
    function out = translation( this )
      out = mex_shell( 'translation', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Translate shell
    function translate( this, vector )
      mex_shell( 'translate', this.objectHandle, vector );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell rotation
    function out = rotation( this )
      out = mex_shell( 'rotation', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Rotate shell by angle and axis
    function rotate( this, angle, axis )
      mex_shell( 'rotate', this.objectHandle, angle, axis );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell transformation
    function out = transformation( this )
      out = mex_shell( 'transformation', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Transform shell by axis and vector
    function transform( this, matrix )
      mex_shell( 'transform', this.objectHandle, matrix );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell X axis and vector
    function out = x( this )
      out = mex_shell( 'x', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell Y axis and vector
    function out = y( this )
      out = mex_shell( 'y', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell Z axis and vector
    function out = z( this )
      out = mex_shell( 'z', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell euler angles (rad) (rotation sequence ZXY)
    function out = eulerAngles( this )
      out = mex_shell( 'eulerAngles', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell relative angles (rad) (rotation sequence ZXY)
    function out = relativeAnglesAvg( this )
      out = mex_shell( 'relativeAnglesAvg', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell relative angles for the i-th rib (rad) (rotation sequence ZXY)
    function out = relativeAngles( this, i )
      out = mex_shell( 'relativeAngles', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact depth (m) 
    function [out1, out2] = contactDepthRibAvg( this, depth_old, time_step )
      [out1, out2] = mex_shell( 'contactDepthRibAvg', this.objectHandle, depth_old, time_step );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact depth for the i-th rib (m) 
    function [out1, out2] = contactDepthRib( this, i, depth_old, time_step )
      [out1, out2] = mex_shell( 'contactDepthRib', this.objectHandle, i, depth_old, time_step );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact depth (m) 
    function [out1, out2] = contactDepthMeshAvg( this, depth_old, time_step )
      [out1, out2] = mex_shell( 'contactDepthRibMesh', this.objectHandle, depth_old, time_step );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact depth for the i-th rib (m) 
    function [out1, out2] = contactDepthMesh( this, i, depth_old, time_step )
      [out1, out2] = mex_shell( 'contactDepthMesh', this.objectHandle, i, depth_old, time_step );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact normal 
    function out = contactNormalAvg( this )
      out = mex_shell( 'contactNormalAvg', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact normal for the i-th rib
    function out = contactNormal( this, i )
      out = mex_shell( 'contactNormal', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact point as an ACME point
    function out = contactPointRibAvg( this )
      out = acme_point();
      out.copyByHandle( mex_shell( 'contactPointRibAvg', this.objectHandle ) );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact point for the i-th rib as an ACME point
    function out = contactPointRib( this, i )
      out = acme_point();
      out.copyByHandle( mex_shell( 'contactPointRib', this.objectHandle, i ) );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact point as an ACME point
    function out = contactPointMeshAvg( this )
      out = acme_point();
      out.copyByHandle( mex_shell( 'contactPointMeshAvg', this.objectHandle ) );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact point for the i-th rib as an ACME point
    function out = contactPointMesh( this, i )
      out = acme_point();
      out.copyByHandle( mex_shell( 'contactPointMesh', this.objectHandle, i ) );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact friction [-]
    function out = contactFrictionAvg( this )
      out = mex_shell( 'contactFrictionAvg', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact friction for the i-th rib [-]
    function out = contactFriction( this, i )
      out = mex_shell( 'contactFriction', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact point affine
    function out = contactPointRibAffineAvg( this )
      out = mex_shell( 'contactPointRibAffineAvg', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact point affine for the i-th rib
    function out = contactPointRibAffine( this, i )
      out = mex_shell( 'contactPointRibAffine', this.objectHandle, i);
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact point affine
    function out = contactPointMeshAffineAvg( this )
      out = mex_shell( 'contactPointMeshAffineAvg', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact point affine for the i-th rib
    function out = contactPointMeshAffine( this, i )
      out = mex_shell( 'contactPointMeshAffine', this.objectHandle, i);
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Intersect shell with mesh
    function out = setupMesh( this, mesh, transform, threshold, method )
      out = mex_shell( 'setup', this.objectHandle, mesh.objectHandle, transform, threshold, method );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Intersect shell with flat terrain
    function out = setupFlat( this, flat, transform )
      out = mex_shell( 'setup', this.objectHandle, flat.objectHandle, transform );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Display object data
    function disp( this )
      disp( this.size() );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot ENVE shape object profile
    function profile( this, figure_name, color )
      figure_name;
      hold on;
      L = this.surfaceWidthLowerBound();
      U = this.surfaceWidthUpperBound();
      W = this.surfaceWidth();
      y = L:W/50:U;
      r = y;
      for i = 1:length(y)
        r(i) = this.surfaceRadius(y(i));
      end
      plot(y, r, 'Color', color)
      xlim([L U]);
      ylim([0.0 1.1*this.surfaceMaxRadius()]);
      axis equal;
      grid on;
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot non-discretized shell shape with 4x4 affine transformation T
    function shapeTplot( this, T, figure_name, color )
      figure_name;
      hold on;
      L = this.surfaceWidthLowerBound();
      U = this.surfaceWidthUpperBound();
      W = this.surfaceWidth();
      y = L:W/50:U;
      r = zeros(1, length(y));
      for i = 1:length(y)
        r(i) = this.surfaceRadius(y(i));
      end
      [X,Y,Z] = cylinder(r, 100);
      X_new = zeros(height(X), length(X));
      Y_new = zeros(height(X), length(X));
      Z_new = zeros(height(X), length(X));
      for i = 1:height(X)
        for j = 1:length(X)
          new = T*[Y(i,j) Z(i,j)*W-W/2 X(i,j) 1]';
          X_new(i,j) = new(1);
          Y_new(i,j) = new(2);
          Z_new(i,j) = new(3);
        end
      end
      s = surf(X_new, Y_new, Z_new);
      s.FaceColor = color;
      grid on;
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot "statically" non-discretized shell shape
    function shellShape( this, figure_name, color );
      figure_name;
      hold on;
      this.shapeTplot( eye(4), figure_name, color )
      r = 1.1*this.surfaceMaxRadius();
      xlim([-r r]);
      ylim([-r r]);
      zlim([-r r]);
      axis equal;
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot "dinamically" non-discretized shell shape
    function plotShape( this, figure_name, color )
      figure_name;
      hold on;
      T = this.transformation();
      this.shapeTplot( T, figure_name, color );
      r = 2.0*this.surfaceMaxRadius();
      c = T(1:3,4);
      axis equal;
      xlim([c(1)-r c(1)+r]);
      ylim([c(2)-r c(2)+r]);
      zlim([c(3)-r c(3)+r]);
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot discretized shell shape with 4x4 affine transformation T
    function TireXTplot( this, T, figure_name, color )
      figure_name;
      hold on;
      n = this.size();
      w = this.ribWidth(1);
      for k = 1:n
        c = this.ribCenter(k).get();
        d = this.surfaceDerivative(c(2));
        r = ones(1,2)*this.ribRadius(k) + [w/2*d -w/2*d];
        [X,Y,Z] = cylinder(r, 100);
        X_new = zeros(height(X), length(X));
        Y_new = zeros(height(X), length(X));
        Z_new = zeros(height(X), length(X));
        for i = 1:height(X)
          for j = 1:length(X)
            new = T*[Y(i,j) Z(i,j)*w-w/2-c(2) X(i,j) 1]';
            X_new(i,j) = new(1);
            Y_new(i,j) = new(2);
            Z_new(i,j) = new(3);
          end
        end
      s = surf(X_new, Y_new, Z_new);
      s.FaceColor = color;
      end
      grid on;
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot "statically" non-discretized shell TireX shape
    function shellTireX( this, figure_name, color )
      figure_name;
      hold on;
      this.TireXTplot( eye(4), figure_name, color )
      r = 1.1*this.surfaceMaxRadius();
      xlim([-r r]);
      ylim([-r r]);
      zlim([-r r]);
      axis equal;
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot "dinamically" non-discretized shell TireX shape
    function plotTireX( this, figure_name, color )
      figure_name;
      hold on;
      T = this.transformation();
      this.TireXTplot( T, figure_name, color );
      r = 2.0*this.surfaceMaxRadius();
      c = T(1:3,4);
      axis equal;
      xlim([c(1)-r c(1)+r]);
      ylim([c(2)-r c(2)+r]);
      zlim([c(3)-r c(3)+r]);
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot discretized shell shape as ribs with 4x4 affine transformation T
    function ribsTplot( this, T, figure_name, color )
      figure_name;
      hold on;
      n = this.size();
      for i = 1:n
        disk = acme_disk( this.ribRadius(i), ...
                              this.ribCenter(i).get(), ...
                              [0 1 0]' );
        disk.transform(T);
        disk.plot( figure_name, color );
      end
      grid on;
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot "statically" non-discretized shell ribs shape
    function shellRibs( this, figure_name, color );
      figure_name;
      hold on;
      this.ribsTplot( eye(4), figure_name, color )
      r = 1.1*this.surfaceMaxRadius();
      xlim([-r r]);
      ylim([-r r]);
      zlim([-r r]);
     axis equal;
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot "dinamically" non-discretized shell ribs shape
    function plotRibs( this, figure_name, color )
      figure_name;
      hold on;
      T = this.transformation();
      this.ribsTplot( T, figure_name, color );
      r = 2.0*this.surfaceMaxRadius();
      c = T(1:3,4);
      xlim([c(1)-r c(1)+r]);
      ylim([c(2)-r c(2)+r]);
      zlim([c(3)-r c(3)+r]);
      axis equal;
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot results of setup function
    function plotSetup( this, figure_name, map_name )
      figure_name;
      hold on;
      n = this.size();
      color_map = eval( strcat( 'colormap(', map_name, '(double(n)))' ) );
      for i = 1:n
        T = this.contactPointRibAffine(i);
        plane = acme_plane( [0 0 0]', [0 0 1]' );
        plane.transform(T);
        plane.plot( figure_name, color_map(i,:) );
      end
      r = 2.0*this.surfaceMaxRadius();
      c = T(1:3,4);
      axis equal;
      xlim([c(1)-r c(1)+r]);
      ylim([c(2)-r c(2)+r]);
      zlim([c(3)-r c(3)+r]);
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get object type as string
    function out = type( this )
      out = 'shell';
    end
  end
end

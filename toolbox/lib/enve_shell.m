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
    %> Resize shell shape with N ribs
    function resize( this, n )
      mex_shell( 'resize', this.objectHandle, n );
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
    %> Get shell surface maximum width on reference (m)
    function out = surfaceWidthBound( this, y )
      out = mex_shell( 'surfaceWidthBound', this.objectHandle, y );
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
    %> Translate shell
    function translate( this, vector )
      mex_shell( 'translate', this.objectHandle, vector );
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
    %> Rotate shell by angle and axis
    function rotate( this, angle, axis )
      mex_shell( 'rotate', this.objectHandle, angle, axis );
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
    %> Transform shell by axis and vector
    function transform( this, matrix )
      mex_shell( 'transform', this.objectHandle, matrix );
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
    %> Intersect shell with flat terrain
    function out = setupFlat( this, flat, transform, method )
      out = mex_shell( 'setupFlat', this.objectHandle, flat.objectHandle, transform, method );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Intersect shell with mesh terrain
    function out = setupMesh( this, mesh, transform, method )
      out = mex_shell( 'setupMesh', this.objectHandle, mesh.objectHandle, transform, method );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact point as an ACME point
    function out = contactPointAvg( this )
      out = acme_point();
      out.copyByHandle( mex_shell( 'contactPointAvg', this.objectHandle ) );
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
    %> Get shell contact point an ACME point vector
    function out = contactPointVec( this )
      out = cell(1,this.size());
      for i = 1:this.size()
        out{i} = this.contactPointRib(i);
      end
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
    function out = contactNormalRib( this, i )
      out = mex_shell( 'contactNormalRib', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact normal vector
    function out = contactNormalVec( this )
      out = cell(1,this.size());
      for i = 1:this.size()
        out{i} = this.contactNormalRib(i);
      end
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact depth (m) 
    function out = contactDepthAvg( this )
      out = mex_shell( 'contactDepthAvg', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact depth for the i-th rib (m) 
    function out = contactDepthRib( this, i )
      out = mex_shell( 'contactDepthRib', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact depth vector (m) 
    function out = contactDepthVec( this )
      out = zeros(1, this.size());
      for i = 1:this.size()
        out(i) = this.contactDepthRib(i);
      end
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact friction (-)
    function out = contactFrictionAvg( this )
      out = mex_shell( 'contactFrictionAvg', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact friction for the i-th rib (-)
    function out = contactFrictionRib( this, i )
      out = mex_shell( 'contactFrictionRib', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact friction vector (-)
    function out = contactFrictionVec( this )
      out = cell(1,this.size());
      for i = 1:this.size()
        out{i} = this.contactFrictionRib(i);
      end
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact area (m^2)
    function out = contactAreaAvg( this )
      out = mex_shell( 'contactAreaAvg', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact area for the i-th rib (m^2)
    function out = contactAreaRib( this, i )
      out = mex_shell( 'contactAreaRib', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact area vector (m^2)
    function out = contactAreaVec( this )
      out = cell(1,this.size());
      for i = 1:this.size()
        out{i} = this.contactAreaRib(i);
      end
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact volume (m^3)
    function out = contactVolumeAvg( this )
      out = mex_shell( 'contactVolumeAvg', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact volume for the i-th rib (m^3)
    function out = contactVolumeRib( this, i )
      out = mex_shell( 'contactVolumeRib', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact volume vector (m^3)
    function out = contactVolumeVec( this )
      out = cell(1,this.size());
      for i = 1:this.size()
        out{i} = this.contactVolumeRib(i);
      end
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
    function out = relativeAnglesRib( this, i )
      out = mex_shell( 'relativeAnglesRib', this.objectHandle, i );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell relative angles vector (rad) (rotation sequence ZXY)
    function out = relativeAnglesVec( this )
      out = cell(1,this.size());
      for i = 1:this.size()
        out{i} = this.relativeAnglesRib(i);
      end
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact point affine
    function out = contactPointAffineAvg( this )
      out = mex_shell( 'contactPointAffineAvg', this.objectHandle );
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact point affine for the i-th rib
    function out = contactPointAffineRib( this, i )
      out = mex_shell( 'contactPointAffineRib', this.objectHandle, i);
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get shell contact point affine vector
    function out = contactPointAffineVec( this )
      out = cell(1,this.size());
      for i = 1:this.size()
        out{i} = this.contactPointAffineRib(i);
      end
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
      W = this.surfaceWidth();
      y = -W:W/50:W;
      r = y;
      for i = 1:length(y)
        r(i) = this.surfaceRadius(y(i));
      end
      plot(y, r, 'Color', color)
      xlim([-W W]);
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
      W = this.surfaceWidth();
      y = -W:W/50:W;
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
          new = T*[Y(i,j) Z(i,j)*2*W-W X(i,j) 1]';
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
      R = 1.1*this.surfaceMaxRadius();
      xlim([-R R]);
      ylim([-R R]);
      zlim([-R R]);
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
      R = 2.0*this.surfaceMaxRadius();
      C = T(1:3,4);
      axis equal;
      xlim([C(1)-R C(1)+R]);
      ylim([C(2)-R C(2)+R]);
      zlim([C(3)-R C(3)+R]);
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot discretized shell shape with 4x4 affine transformation T
    function TireXTplot( this, T, figure_name, color )
      figure_name;
      hold on;
      N = this.size();
      w = this.ribWidth(1);
      for k = 1:N
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
      R = 1.1*this.surfaceMaxRadius();
      xlim([-R R]);
      ylim([-R R]);
      zlim([-R R]);
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
      R = 2.0*this.surfaceMaxRadius();
      C = T(1:3,4);
      axis equal;
      xlim([C(1)-R C(1)+R]);
      ylim([C(2)-R C(2)+R]);
      zlim([C(3)-R C(3)+R]);
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Plot discretized shell shape as ribs with 4x4 affine transformation T
    function ribsTplot( this, T, figure_name, color )
      figure_name;
      hold on;
      N = this.size();
      for i = 1:N
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
      R = 1.1*this.surfaceMaxRadius();
      xlim([-R R]);
      ylim([-R R]);
      zlim([-R R]);
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
      R = 2.0*this.surfaceMaxRadius();
      C = T(1:3,4);
      xlim([C(1)-R C(1)+R]);
      ylim([C(2)-R C(2)+R]);
      zlim([C(3)-R C(3)+R]);
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
      N = this.size();
      color_map = eval( strcat( 'colormap(', map_name, '(double(N)))' ) );
      for i = 1:N
        T = this.contactPointAffineRib(i);
        plane = acme_plane( [0 0 0]', [0 0 1]' );
        plane.transform(T);
        plane.plot( figure_name, color_map(i,:) );
      end
      R = 2.0*this.surfaceMaxRadius();
      C = T(1:3,4);
      axis equal;
      xlim([C(1)-R C(1)+R]);
      ylim([C(2)-R C(2)+R]);
      zlim([C(3)-R C(3)+R]);
      hold off;
    end
    %
    % - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    %
    %> Get surface object mesh grid
    function out = meshTireX( this )
      W = this.surfaceWidth();
      y = -W:W/50:W;
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
          new = eye(4)*[Y(i,j) Z(i,j)*2*W-W X(i,j) 1]';
          X_new(i,j) = new(1);
          Y_new(i,j) = new(2);
          Z_new(i,j) = new(3);
        end
      end
      out.X = X_new;
      out.Y = Y_new;
      out.Z = Z_new;
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

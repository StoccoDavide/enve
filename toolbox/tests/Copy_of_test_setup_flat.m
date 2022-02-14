
clc;
clear all;
close all;

% Create shape and shell variables

N  = 20;
Rx = 0.3130;
Mx = 9.0;
Ry = 0.11;
My = 6.0;
Ly = 0.1025;

%% Instantiate shape object

out.depth = 6.704569e-05
out.point = [ 2.000000e+00, 4.938393e+00, 0.000000e+00 ]'

out.depth = 6.704569e-05
out.point = [ 2.000000e+00, 4.938393e+00, 0.000000e+00 ]'

obj = enve_shell(N, Rx, Mx, Ry, My, Ly);

T = [ 1, 0, 0, 2.0; ...
      0, 1, 0, 5.0; ...
      0, 0, 1, 0.276; ...
      0, 0, 0, 1 ];

obj.transform( T )
% obj.translate([0 0 0.26]')
obj.rotate(pi/4, [1 0 0]') % Camber
obj.rotate(pi/4, [0 1 0]') % Pitch
obj.rotate(0, [0 0 1]') % Yaw

T = obj.transformation()

% Set Color

rubber_color = [0.4 0.4 0.4];
road_color = [0.863 0.863 0.863];

% Test profile plot

% Test setup

%ground = enve_flat([0 0 0]', [0 0 1]', 1.0);
%obj.setupFlat(ground, T, 'sampling')
ground = enve_mesh('../../files_rdf/sample.rdf');
obj.setupMesh(ground, T, 'sampling')



obj.contactDepthAvg()

out5 = figure;
ground.plot(out5, road_color);
obj.plotSetupVec(out5, 0.1);
obj.plotSetupAvg(out5, 0.5);
obj.plotEnve(out5, rubber_color, 0.5 );

z_vec = linspace(0.300, 0.230, 100);
rho_vec_s = z_vec;
rho_vec_g = z_vec;
for i = 1:length(z_vec)
  T = [ T(1,1), T(1,2), T(1,3), T(1,4); ...
        T(2,1), T(2,2), T(2,3), T(2,4); ...
        T(3,1), T(3,2), T(3,3), z_vec(i); ...
        0, 0, 0, 1 ];
  %obj.setupFlat(ground, T, 'sampling');
  obj.setupMesh(ground, T, 'sampling');
  rho_vec_s(i) = obj.contactDepthAvg();
  %obj.setupFlat(ground, T, 'geometric');
  obj.setupMesh(ground, T, 'geometric');
  rho_vec_g(i) = obj.contactDepthAvg();
end

figure;
hold on;
plot(z_vec, rho_vec_s, 'b-', 'LineWidth', 1.1);
plot(z_vec, rho_vec_g, 'r-.', 'LineWidth', 1.1);
hold off;
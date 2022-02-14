
clc;
clear all;
close all;

% Create shape and shell variables

N  = 1;
Rx = 0.3130;
Mx = 9.0;
Ry = 0.11;
My = 6.0;
Ly = 0.1025;

%% Instantiate shape object

obj = enve_shell(N, Rx, Mx, Ry, My, Ly);

T = [ 1, 0, 0, 0.0; ...
      0, 1, 0, 0.0; ...
      0, 0, 1, 0.301; ...
      0, 0, 0, 1 ];

obj.transform( T )
% obj.translate([0 0 0.26]')
obj.rotate(pi/4, [0 1 0]')
obj.rotate(pi/4, [1 0 0]')

T = obj.transformation()

% Set Color

rubber_color = [0.4 0.4 0.4];
road_color = [0.863 0.863 0.863];

% Test profile plot

% Test setup

flat = enve_flat([0 0 0]', [0 0 1]', 1.0);

obj.setupFlat(flat, T, 'sampling')

obj.contactPointAvg()
obj.contactDepthAvg()

z_vec = linspace(0.300, 0.200, 100);
rho_vec_s = z_vec;
rho_vec_g = z_vec;
for i = 1:length(z_vec)
  T = [ 0.7071    0.5000    0.5000         0; ...
         0    0.7071   -0.7071         0; ...
   -0.7071    0.5000    0.5000, z_vec(i); ...
        0, 0, 0, 1 ];
  obj.setupFlat(flat, T, 'sampling');
  rho_vec_s(i) = obj.contactDepthAvg();
  obj.setupFlat(flat, T, 'geometric');
  rho_vec_g(i) = obj.contactDepthAvg();
end

out5 = figure;
flat.plot(out5, road_color);
obj.plotSetupVec(out5, 0.1);
obj.plotSetupAvg(out5, 0.5);
obj.plotEnve(out5, rubber_color, 0.5 );

figure;
hold on;
plot(z_vec, rho_vec_s, 'b-', 'LineWidth', 1.1);
plot(z_vec, rho_vec_g, 'r-.', 'LineWidth', 1.1);
hold off;
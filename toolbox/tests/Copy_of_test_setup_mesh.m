
clc;
clear all;
close all;

% Create shape and shell variables

N  = 1;
Rx = 0.313;
Mx = 9.0;
Ry = 0.11;
My = 6.0;
Ly = 0.205/2;

%% Instantiate shape object

obj = enve_shell(N, Rx, Mx, Ry, My, Ly);


T = [ 1 0 0 64.0000000000017; ...
      0 0.954946486838598 -0.296778043787980 1.01171480669502; ...
      0 0.296778043787980 0.954946486838598 0.31305117472249; ...
      0 0 0 1 ];

% obj.transform( T )
% obj.translate([0 0 0.26]')
% obj.rotate(pi/6, [1 0 0]')

% Set Color

rubber_color = [0.4 0.4 0.4];
road_color = [0.863 0.863 0.863];


% Test setup

mesh = enve_mesh('../../files_rdf/sample.rdf');

tic
boolean = obj.setupMesh(mesh, T, 'sampling')
toc

out5 = figure;
mesh.plot(out5, road_color)
obj.plotSetupVec(out5, 0.1)
obj.plotSetupAvg(out5, 0.5)
obj.plotEnve(out5, rubber_color, 0.5 )
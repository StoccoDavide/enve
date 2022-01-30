
clc;
clear all;
close all;

% Create shape and shell variables

N  = 5;
Rx = 0.3130;
Mx = 9.0;
Ry = 0.12;
My = 6.0;
Ly = 0.10;

%% Instantiate shape object

obj = enve_shell(N, Rx, Mx, Ry, My, Ly);

% Test getters

obj.surfaceMaxRadius()
obj.surfaceMaxWidth()
obj.size()

% Test delete

obj.resize(8);

obj

T = [ 0, 1, 0, 1.0;   ...
      1, 0, 0, 1.0;   ...
      0, 0, 1, 0.3130-0.006; ...
      0, 0, 0, 1 ];

obj.transform( T )
% obj.translate([0 0 0.26]')
% obj.rotate(pi/6, [1 0 0]')

% Set Color

rubber_color = [0.4 0.4 0.4];
road_color = [0.863 0.863 0.863];

% Test profile plot

out1 = figure;
obj.profile(out1, rubber_color)

%% Test 3D shell shape

out2 = figure;
subplot(1,2,1);
obj.shellShape(out2, rubber_color)
xlabel('x');
ylabel('y');
zlabel('z');

subplot(1,2,2);
obj.plotShape(out2, rubber_color)
xlabel('x');
ylabel('y');
zlabel('z');

% Test 3D shell

out3 = figure;
subplot(1,2,1);
obj.shellEnve(out3, rubber_color)
xlabel('x');
ylabel('y');
zlabel('z');

subplot(1,2,2);
obj.plotEnve(out3, rubber_color)
xlabel('x');
ylabel('y');
zlabel('z');

% Test 3D shell ribs

out4 = figure;
subplot(1,2,1);
obj.shellRibs(out4, rubber_color)
xlabel('x');
ylabel('y');
zlabel('z');

subplot(1,2,2);
obj.plotRibs(out4, rubber_color)
xlabel('x');
ylabel('y');
zlabel('z');

% Test setup

mesh = enve_mesh('../../files_rdf/sample.rdf');

tic
boolean = obj.setupMesh(mesh, T, 'sampling');
toc

out5 = figure;
mesh.plot(out5, road_color)
obj.plotSetup(out5, 'hsv')
obj.plotEnve(out5, rubber_color )
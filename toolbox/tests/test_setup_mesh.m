
clc;
clear all;
close all;

% Create shape and shell variables

N  = 10;       
Rx = 0.327;    
Mx = 4.000;    
Ry = 0.195;    
My = 4.000;    
Ly = 0.188*0.9;

%% Instantiate shape object

obj = enve_shell(N, Rx, Mx, Ry, My, Ly);

% Test getters

obj.surfaceMaxRadius()
obj.surfaceMaxWidth()
obj.size()

% Test delete

obj.resize(8);

obj

T = [ 1, 0, 0, 1.0;  ...
      0, 1, 0, 1.0;  ...
      0, 0, 1, 0.31; ...
      0, 0, 0, 1 ];

obj.transform(T);
obj.rotate(150*pi/180, [0 0 1]'); % Yaw angle (rad)
obj.rotate(150*pi/180, [1 0 0]'); % Camber angle (rad)
obj.rotate(150*pi/180, [0 1 0]'); % Pitch angle (rad)

T = obj.transformation();
obj.transform(T);

% Set Color

rubber_color = [0.4 0.4 0.4];
road_color   = [0.863 0.863 0.863];
scale        = 0.2;

% Test profile plot

out1 = figure;
obj.profile(out1, rubber_color, scale);

%% Test 3D shell shape

out2 = figure;
subplot(1,2,1);
obj.shellShape(out2, rubber_color, scale);
xlabel('x');
ylabel('y');
zlabel('z');

subplot(1,2,2);
obj.plotShape(out2, rubber_color, scale);
xlabel('x');
ylabel('y');
zlabel('z');

% Test 3D shell

out3 = figure;
subplot(1,2,1);
obj.shellEnve(out3, rubber_color, scale);
xlabel('x');
ylabel('y');
zlabel('z');

subplot(1,2,2);
obj.plotEnve(out3, rubber_color, scale);
xlabel('x');
ylabel('y');
zlabel('z');

% Test 3D shell ribs

out4 = figure;
subplot(1,2,1);
obj.shellRibs(out4, rubber_color, scale);
xlabel('x');
ylabel('y');
zlabel('z');

subplot(1,2,2);
obj.plotRibs(out4, rubber_color, scale);
xlabel('x');
ylabel('y');
zlabel('z');

% Test setup

mesh = enve_mesh('../../files_rdf/sample.rdf');

tic
boolean = obj.setupMesh(mesh, T, 'geometric');
toc

out5 = figure; hold on;
xlabel('x');
ylabel('y');
zlabel('z');
mesh.plot(out5, road_color);
obj.shapeTplot(T, out5, rubber_color, scale);
obj.plotSetupAvg(out5, scale);

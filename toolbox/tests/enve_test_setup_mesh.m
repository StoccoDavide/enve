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

% Clean workspace
clc;
clear all;
close all;

% Create shape and shell variables
Nr = 10;
Rx = 0.3130;
Mx = 9.000;
Ry = 0.11;
My = 6.000;
Ly = 0.205/2;

% Instantiate shape object
obj = enve_shell(Nr, Rx, Mx, Ry, My, Ly);

% Test getters
obj.surfaceMaxRadius()
obj.surfaceMaxWidth()
obj.size()

% Test resize
%obj.resize(11);
%obj

% Test transform
T = [ 1, 0, 0, 0.2;  ...
      0, 1, 0, 0.2;  ...
      0, 0, 1, 0.25; ...
      0, 0, 0, 1 ];

obj.transform(T);
obj.rotate(0*pi/180, [0 0 1]'); % Yaw angle (rad)
obj.rotate(0*pi/180, [1 0 0]'); % Camber angle (rad)
obj.rotate(0*pi/180, [0 1 0]'); % Pitch angle (rad)

T = obj.transformation();
obj.transform(T);

% Set Color
rubber_color = [0.4 0.4 0.4];
road_color   = [0.863 0.863 0.863];
scale        = 0.2;

% Test profile plot
out1 = figure;
obj.profile(out1, rubber_color, scale);

% Test 3D shell shape
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
mesh = enve_mesh('../../files_obj/cobblestone.obj', 1.0);

tic
boolean = obj.setupMesh(mesh, T, 'geometric')
toc

out5 = figure; hold on;
xlabel('x');
ylabel('y');
zlabel('z');
mesh.plot(out5, road_color);
obj.shapeTplot(T, out5, rubber_color, scale);
obj.plotSetupVec(out5, 0.5*scale);
obj.plotSetupAvg(out5, scale);
